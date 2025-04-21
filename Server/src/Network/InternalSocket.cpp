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

    void InternalSocket::setName(const std::string &_name)
    {
        m_name = _name;
    }

    const std::string &InternalSocket::getName() const
    {
        return m_name;
    }

    void InternalSocket::setSeqNum(size_t _seqnum)
    {
        m_seqnum = _seqnum;
    }

    size_t InternalSocket::getSeqNum()
    {
        return m_seqnum;
    }

    size_t InternalSocket::newSeqNum()
    {
        return ++m_seqnum;
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