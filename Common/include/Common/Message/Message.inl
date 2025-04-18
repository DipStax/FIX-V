#include "Common/Message/Message.hpp"

namespace fix::com
{
    template<char MsgType, IsTagList ...TagsList, IsTag ...Tags>
    std::string Message<MsgType, TagLists<TagsList...>, Tags...>::to_string() const
    {
        std::string body =  + this->serialize();

        this->Header.set<Tag::BodyLength>(std::to_string(body.size()));
        std::string msg = this->Header.serialize() + body;
        size_t sum = 0;

        for (char _c : msg)
            sum += static_cast<size_t>(_c);
        msg += std::to_string(Tag::CheckSum) + "=" + std::to_string(sum % 256);
        return msg;
    }
}