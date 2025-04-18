#pragma once

#include <memory>

#include "Common/Container/TSQueue.hpp"
#include "Server/MessageContext.hpp"

namespace fix::serv
{
    using OutputIndexType = uint32_t;
    template<class T>
    using OutputMessageQueue = fix::com::TSQueue<MessageContext<T>>;

    class IInputProcessUnit
    {
        public:
            virtual void setInput(std::shared_ptr<fix::com::IQueue> _input) = 0;
    };

    class IOutputProcessUnit
    {
        public:
            virtual std::shared_ptr<fix::com::IQueue> getOutput(OutputIndexType _idx) = 0;
    };

    class BaseProcessUnit
    {
        protected:
            bool m_running;
    };

    template<class T>
    class ProcessUnit : public T
    {
        public:
            template<class ...Ts>
            ProcessUnit(const Ts &&..._args)
                : T(std::forward<Ts>(_args)...)
            {
            }

            std::futur_status stop()
            {
                std::future_status ret = std::future_status::ready;

                m_running = false;
                for (; ret == std::future_status::ready; ret = m_futur.wait_for(std::chrono::milliseconds(500))) {}
                return ret;
            }

            bool status();

        private:
            std::futur<void> m_futur;
    }
}