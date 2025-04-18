#include "Common/Message/Header.hpp"

namespace fix::com
{
    template<char TMsgType>
    Header<TMsgType>::Header()
    {
        set<Tag::MsgType>(std::string{MsgType});
    }
}