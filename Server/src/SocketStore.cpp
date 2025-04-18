#include "Server/SocketStore.hpp"

namespace fix::serv
{
    SocketStore &SocketStore::Instance()
    {
        static SocketStore store{};

        return store;
    }

    void SocketStore::newClient(std::shared_ptr<InternalSocket> _socket)
    {
        {
            std::lock_guard lock(m_mutex);

            m_client.push_back(_socket);
        }
    }
}