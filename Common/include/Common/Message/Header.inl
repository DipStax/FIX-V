#include "Common/Message/Header.hpp"

namespace fix::com
{
    template<char TMsgType>
    Header<TMsgType>::Header()
    {
        set<Tag::MsgType>(std::string{MsgType});
    }

    template<char TMsgType>
    std::string Header<TMsgType>::to_string() const
    {
        return serialize();
    }

    template<char TMsgType>
    void Header<TMsgType>::from_string(const std::string &_str)
    {
        deserialize(_str.substr(0, _str.size() - getBodyLength() - 7));
    }

    template<char TMsgType>
    size_t Header<TMsgType>::getBodyLength()
    {
        std::istringstream ss(_str);
        std::string token;

        for (uint8_t it; it < 3; it++)
            std::getline(ss, token, '<' );
        std::vector<std::string> kvpair = utils::split<'='>(token);
        if (kvpair != 2)
            throw; // todo
        if (kvpair[0] != "9")
            throw; // todo
        if (!std::all_of(kvpair[1].begin(), kvpair[1].end(), std::isdigit))
            throw; // todo
        return static_cast<size_t>(std::atoll(kvpair[1]));
    }
}