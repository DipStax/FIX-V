#pragma once

#include "Common/Message/MessageType.hpp"
#include "Server/MessageContext.hpp"

namespace fix::serv
{
    class ErrorHelper
    {
        public:
            template<class T>
            inline msg::Reject RejectException(const MessageContext<T> &_ctx, com::RejectException _excp)
            {
                fix::msg::Reject reject{};

                reject.set<Tag::RefSeqNum>(std::to_string(_ctx.socket->getSeqNum() - 1));
                reject.set<Tag::SessionRejectReason>(_excp.reason());
                reject.set<Tag::Text>(_excp.what());

                reject.Header.set<Tag::SenderCompId>(SERVER_TARGET_NAME);
                reject.Header.set<Tag::TargetCompId>(_ctx.socket->getName());
                reject.Header.set<Tag::MsgSeqNum>(std::to_string(_ctx.socket->newSeqNum()));

                return reject;
            }

            template<class T>
            inline msg::Reject internalError(const MessageContext<T> &_ctx, std::exception _excp)
            {
                fix::msg::Reject reject{};

                reject.set<Tag::RefSeqNum>(std::to_string(_ctx.socket->getSeqNum() - 1));
                reject.set<Tag::Text>(_excp.what());

                reject.Header.set<Tag::SenderCompId>(SERVER_TARGET_NAME);
                reject.Header.set<Tag::TargetCompId>(_ctx.socket->getName());
                reject.Header.set<Tag::MsgSeqNum>(std::to_string(_ctx.socket->newSeqNum()));

                return reject;
            }

    }
}