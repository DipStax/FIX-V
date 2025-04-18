#include "FT.App/ProcessUnit/Acceptor.hpp"

namespace fix::pu
{
    Acceptor::Acceptor(asio::io_context &_ctx, uint32_t _port)
        : m_endpoint(asio::ip::tcp::v4(), _port),
        m_acceptor(_ctx, m_endpoint)
    {
    }

    Acceptor::~Acceptor()
    {
        stop();
    }

    void Acceptor::stop()
    {
        m_stop = true;
        m_acceptor.close();
    }

    void Acceptor::run()
    {
        m_acceptor.async_accept(Acceptor::accept);
    }

    std::shared_ptr<fix::com::IQueue> getOutput(OutputIndexType _idx)
    {
        switch (_idx) {
            case OutputName::Message:   return std::reinterpret_pointer_cast<fix::com::IQueue>(m_output);
            default:                    return nullptr;
        }
    }

    void Acceptor::accept(std::error_code _ec, asio::ip::tcp::socket _socket)
    {
        if (!_ec) {
            std::shared_ptr<InternalSocket> internal = std::make_shared<InternalSocket>(std::move(_socket), m_output);

            SocketStore::Instance().newClient(internal);
        } else {
            // error handling
        }
        if (!m_stop)
            run();
    }
}