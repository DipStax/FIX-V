#include "Server/Network/InternalSocket.hpp"

namespace fix::serv
{
    InternalSocket::InternalSocket(asio::ip::tcp::socket &&_socket, std::shared_ptr<InputQueue> _output)
        : m_socket(std::move(_socket)), m_output(_output)
    {
    }

    void InternalSocket::start()
    {
        m_socket.async_read_some(asio::buffer(m_buffer, NET_BUFFER_SIZE), InternalSocket::received);
    }

    size_t InternalSocket::newSeqNum()
    {
        size_t cpy = m_seqnum;

        m_seqnum++;
        return cpy;
    }

    void InternalSocket::received(std::error_code _ec, size_t _len)
    {
        if (!_ec) {
            MessageContext<ContextData> ctx;

            ctx.socket = shared_from_this();
            ctx.receiveTime = std::chrono::system_clock::now();
            ctx.data = std::string(m_buffer, _len);
            m_output->push(std::move(ctx));
        }
        m_socket.async_read_some(asio::buffer(m_buffer, NET_BUFFER_SIZE), InternalSocket::received);
    }
}