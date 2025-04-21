#pragma once

#include <exception>
#include <string>

namespace fix::com
{
    class RejectException : public std::exception
    {
        public:
            explicit RejectException(const std::string &_reason, const std::string &_text)
                : m_reason(_reason), m_text(_text)
            {
            }

            virtual ~RejectException() noexcept {}

            virtual const char* what() const noexcept {
                return m_text.c_str();
            };

            const const char *reason() const noexcept {
                return m_reason.c_str();
            }

        private:
            std::string m_reason{};
            std::string m_text{};
    }
}