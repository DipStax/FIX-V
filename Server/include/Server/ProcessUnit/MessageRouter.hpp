#pragma once

#include <concepts>

#include "Server/ProcessUnit/ProcessInterface.hpp"
#include "Common/Message/MessageType.hpp"

#ifndef SERVER_TARGET_NAME
    #define SERVER_TARGET_NAME "Server"
#endif

namespace fix::serv
{
    class MessageRouter : public IInputProcessUnit, IOutputProcessUnit, BaseProcessUnit
    {
        public:
            using ContextData = std::string;
            using InputQueue = fix::com::TSQueue<MessageContext<ContextData>>;

            enum OutputName : OutputIndexType
            {
                Logon,
                HeartBeat,
                Reject
            };

            void setInput(std::shared_ptr<fix::com::IQueue> _input)
            {
                std::shared_ptr<InputQueue> ptr = std::dynamic_pointer_cast<InputQueue>(_input);

                if (ptr == nullptr)
                    throw "error";
                m_input = ptr;
            }

            std::shared_ptr<fix::com::IQueue> getOutput(OutputIndexType _idx)
            {
                switch (_idx) {
                    case OutputName::Logon:     return std::reinterpret_pointer_cast<fix::com::IQueue>(m_logon_op);
                    case OutputName::HeartBeat: return std::reinterpret_pointer_cast<fix::com::IQueue>(m_heartbeat_op);
                    case OutputName::Reject:    return std::reinterpret_pointer_cast<fix::com::IQueue>(m_reject_op);
                    default:                    return nullptr;
                }
            }

        protected:
            void process()
            {
                while (m_running) {
                    if (!m_input->empty()) {
                        MessageContext<ContextData> ctx = m_input->pop_front();
                        std::map<std::string, std::string> msg = mapMessage(ctx.data);
                        std::pair<bool, fix::msg::Reject> result = messageVerification(msg);
                        char msgtype = 0;

                        if (result.first)
                            m_reject_op->push(std::move(result.second));
                        switch (msg["35"][0]) {
                            case fix::msg::Logon::MsgType:
                                MsgDeserializer::Deserialize<fix::msg::Logon>(msg, [_ctx = std::move(ctx), this] (const fix::msg::Logon &_data) {
                                    deserialized<fix::msg::Logon>(_data, m_logon_op, _ctx);
                                });
                                break;
                            default:
                                m_reject_op->push(notSupportedMessage(ctx, msg));
                        }
                    }
                }
            }

        private:
            std::pair<bool, fix::msg::Reject> messageVerification(const std::map<std::string, std::string> &_msg)
            {
                // todo
                // seq number
                // begin string
                return { false, {} };
            }

            template<class T>
            void deserialized(const T &_data, std::shared_ptr<OutputMessageQueue<T>> _output, const MessageContext<ContextData> &&_ctx)
            {
                std::pair<bool, fix::msg::Reject> result = _data.verify();

                if (result.first)
                    m_reject_op->push(std::move(_ctx.as<fix::msg::Reject>(result.second)));
                else
                    _output->push(std::move(_ctx.as<fix::msg::Logon>(_data)));
            }

            MessageContext<fix::msg::Reject> notSupportedMessage(const MessageContext<ContextData> &_ctx, const std::map<std::string, std::string> &_msg)
            {
                fix::msg::Reject reject{};

                reject.Header.set<Tag::SenderCompId>(SERVER_TARGET_NAME);
                reject.Header.set<Tag::TargetCompId>(_msg["49"]);
                reject.Header.set<Tag::MsgSeqNum>(std::to_string(_ctx.socket->newSeqNum()));
                reject.set<Tag::RefSeqNum>(_msg["45"]);
                return _ctx.as<fix::msg::Reject>()
            }

            std::shared_ptr<OutputMessageQueue<fix::msg::Logon>> m_logon_op = std::make_shared<OutputMessageQueue<fix::msg::Logon>>();
            std::shared_ptr<OutputMessageQueue<fix::msg::HeartBeat>> m_heartbeat_op = std::make_shared<OutputMessageQueue<fix::msg::HeartBeat>>();
            std::shared_ptr<OutputMessageQueue<fix::msg::Reject>> m_reject_op = std::make_shared<OutputMessageQueue<fix::msg::Reject>>();

            std::shared_ptr<InputQueue> m_input = nullptr;
    };
}