#pragma once

#include <queue>
#include <mutex>

namespace fix::com
{
    class IQueue
    {
        public:
            virtual size_t size() const = 0;
            virtual bool empty() const = 0;
    };

    template<class T>
    class TSQueue : public IQueue
    {
        public:
            Queue() = default;
            ~Queue() = default;

            [[nodiscard]] bool empty() const;
            [[nodiscard]] size_t size() const;

            void push(const T &_data);
            void push(T &&_data);

            template<class ...Ts>
            void append(Ts &&..._args);

            void pop();
            [[nodiscard]] T pop_front();

        private:
            std::mutex m_mutex;
            std::queue<T> m_queue;
    };
}

#include "Common/Container/TSQueue.inl"