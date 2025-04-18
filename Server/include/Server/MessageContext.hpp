#pragma once

#include <chrono>

#include "Server/Network/InternalSocket.hpp"

namespace fix::serv
{
    template<class T>
    struct MessageContext
    {
        std::shared_ptr<InternalSocket> socket;
        std::chrono::system_clock::time_point receiveTime;

        T data;

        template<class _T>
        MessageContext<_T> as(const _T _data) const
        {
            return MessageContext<_T>{
                socket,
                receiveTime,
                _data
            };
        }
    };
}