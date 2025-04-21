#pragma once

#include <concepts>

#include "Server/ProcessUnit/ProcessInterface.hpp"
#include "Server/ErrorHelper.hpp"

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

                        try {
                            char msgtype = getMessageType(ctx.data);

                            switch (msgtype) {
                                case msg::Logon::MsgType:
                                    // todo
                                    // MsgDeserializer::Deserialize<msg::Logon>(ctx.data, [this, ctx] (const msg::Logon &_data) {
                                    //     this->deserialized(_data, m_logon_op, ctx);
                                    // });
                                    break;
                                default:
                                    throw com::RejectException(err::InvalidMsgType, msgtype + " is not supported");
                            }
                        } catch (com::RejectException &_excp) {
                            m_reject_op->push(ctx.as<msg::Reject>(ErrorHelper::RejectException(ctx, _excp)));
                        } catch (std::exception &_excp) {
                            m_reject_op->push(ctx.as<msg::Reject>(ErrorHelper::internalError(ctx, _excp)))
                        }
                    }
                }
            }

        private:
            char getMessageType(const std::string &_msg)
            {
                std::istringstream ss(_str);
                std::string token;

                for (uint8_t it; it < 2; it++)
                    std::getline(ss, token, '<' );
                std::vector<std::string> kvpair = utils::split<'='>(token);
                if (kvpair != 2)
                    throw; // todo
                if (kvpair[0] != "35")
                    throw; // todo
                if (kvpair[1].size() != 1)
                    throw; // todo
                return kvpair[1][0];
            }

            template<class T>
            void deserialized(const T &_data, std::shared_ptr<OutputMessageQueue<T>> _output, const MessageContext<ContextData> &&_ctx)
            {
                // _data.Header.verify(...);
                _output->push(std::move(_ctx.as<msg::Logon>(_data)));
            }

            std::shared_ptr<OutputMessageQueue<msg::Logon>> m_logon_op = std::make_shared<OutputMessageQueue<msg::Logon>>();
            std::shared_ptr<OutputMessageQueue<msg::HeartBeat>> m_heartbeat_op = std::make_shared<OutputMessageQueue<msg::HeartBeat>>();
            std::shared_ptr<OutputMessageQueue<msg::Reject>> m_reject_op = std::make_shared<OutputMessageQueue<msg::Reject>>();

            std::shared_ptr<InputQueue> m_input = nullptr;
    };
}