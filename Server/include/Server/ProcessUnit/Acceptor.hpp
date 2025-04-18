#pragma once

#include <asio.hpp>

#include "Server/ProcessUnit/ProcessInterface.hpp"
#include "Server/Network/InternalSocket.hpp"

namespace fix::serv::pu
{
    class Acceptor : public IOutputProcessUnit
    {
        public:
            using ContextData = std::string;
            using InputQueue = fix::com::TSQueue<MessageContext<ContextData>>;

            enum OutputName : OutputIndexType
            {
                Message
            };

            Acceptor(asio::io_context &_ctx, uint32_t _port);
            ~Acceptor();

            void stop();

            std::shared_ptr<fix::com::IQueue> getOutput(OutputIndexType _idx);

        protected:
            void runAcceptor();

        private:
            void accept(std::error_code _ec, asio::ip::tcp::socket socket);

            std::shared_ptr<InputQueue> &m_output;

            asio::ip::tcp::endpoint m_endpoint;
            asio::ip::tcp::acceptor m_acceptor;
    };
}