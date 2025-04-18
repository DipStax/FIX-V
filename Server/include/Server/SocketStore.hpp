#pragma once

#include <memory>
#include <mutex>
#include <vector>

#include "Server/Network/InternalSocket.hpp"

namespace fix::serv
{
    class SocketStore
    {
        public:
            ~SocketStore() = default;

            static SocketStore &Instance();

            void newClient(std::shared_ptr<InternalSocket> _socket);

        private:
            SocketStore() = default;

            std::mutex m_mutex;
            std::vector<std::shared_ptr<InternalSocket>> m_client;
    };
}