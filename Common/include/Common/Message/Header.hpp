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

            [[nodiscard]] std::string to_string() const;

            void from_string(const std::string &_str);

            static constexpr const char MsgType = TMsgType;

        private:
            size_t getBodyLength();
    };
}

#include "Common/Message/Header.inl"