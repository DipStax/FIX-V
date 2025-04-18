#pragma once

#include "Common/Message/RawMessage.hpp"

namespace fix::com
{
    template<char TMsgType>
    class Header : public RawMessage<
            PositionalTag<
                Required<Tag::BeginString>,
                Required<Tag::BodyLength>,
                Required<Tag::MsgType>
            >,
            TagLists<>,
            Required<Tag::SenderCompId>,
            Required<Tag::TargetCompId>,
            Required<Tag::MsgSeqNum>,
            Required<Tag::SendingTime>
        >
    {
        public:
            Header();
            ~Header() = default;

            static constexpr const char MsgType = TMsgType;
    };
}

#include "Common/Message/Header.inl"