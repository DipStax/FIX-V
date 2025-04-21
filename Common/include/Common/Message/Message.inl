#include "Common/Message/Message.hpp"

namespace fix::com
{
    template<char MsgType, IsTagList ...TagsList, IsTag ...Tags>
    std::string Message<MsgType, TagLists<TagsList...>, Tags...>::to_string() const
    {
        std::string body = this->serialize();

        this->Header.set<Tag::BodyLength>(std::to_string(body.size()));
        body = this->Header.to_string() + body;
        size_t sum = 0;

        for (char _c : msg)
            sum += static_cast<size_t>(_c);
        body += std::to_string(Tag::CheckSum) + "=" + std::to_string(sum % 256);
        return body;
    }

    template<char MsgType, IsTagList ...TagsList, IsTag ...Tags>
    void Message<MsgType, TagLists<TagsList...>, Tags...>::from_string(const std::string &_str)
    {
        size_t bodylen = 0;
        size_t sum = 0;

        for (char _c : msg)
            sum += static_cast<size_t>(_c);
        Header->from_string(_str);
        bodylen = static_cast<size_t>(std::atoll(Header.get<Tag::BodyLength>()));
        deserialize(_str.substr(_str.size() - bodylen - 7, _str.size() - 7));
        // get checksum
    }
}