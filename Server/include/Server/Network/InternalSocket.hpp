#pragma once

#include <memory>

#include <asio.hpp>

#include "Common/Container/TSQueue.hpp"
#include "Server/MessageContext.hpp"

#ifndef NET_BUFFER_SIZE
    #define NET_BUFFER_SIZE 1024
#endif

namespace fix::serv
{

    class InternalSocket : public std::enable_shared_from_this<InternalSocket>
    {
        public:
            using ContextData = std::string;
            using InputQueue = fix::com::TSQueue<MessageContext<ContextData>>;

            InternalSocket(asio::ip::tcp::socket &&_socket, std::shared_ptr<InputQueue> _output);
            ~InternalSocket();

            void start();

            [[nodiscard]] size_t newSeqNum();

        private:
            void received(std::error_code _ec, size_t _len);

            asio::ip::tcp::socket m_socket;

            size_t m_seqnum = 0;
            char m_buffer[NET_BUFFER_SIZE];
            std::shared_ptr<InputQueue> m_output;
    };
}