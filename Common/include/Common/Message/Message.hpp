#pragma once

#include "Common/Message/Header.hpp"

namespace fix::com
{
    template<char TMsgType, class ...Tags>
    class Message;

    template<char TMsgType, IsTag ...Tags>
    class Message<TMsgType, Tags...> : public Message<PositionalTag<>, TagLists<>, Tags...>
    {
    };

    template<char TMsgType, IsTagList ...TagsList, IsTag ...Tags>
    class Message<TMsgType, TagLists<TagsList...>, Tags...> : public RawMessage<PositionalTag<>, TagLists<TagsList...>, Tags...>
    {
        public:
            Header<TMsgType> Header;

            std::string to_string() const;

            void from_string(const std::string &_str);

            static constexpr const char MsgType = TMsgType;
    };
}

#include "Common/Message/Message.inl"