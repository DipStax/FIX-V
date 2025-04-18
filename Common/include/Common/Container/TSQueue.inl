#include "Common/Container/TSQueue.hpp"

namespace fix::com
{
    template<class T>
    bool TSQueue<T>::empty() const
    {
        return m_queue.empty();
    }

    template<class T>
    size_t TSQueue<T>::size() const
    {
        return m_queue.size();
    }

    template<class T>
    void TSQueue<T>::push(const T &_data)
    {
        std::lock_guard<std::mutex> guard(m_mutex);

        m_queue.push(_data);
    }

    template<class T>
    void TSQueue<T>::push(T &&_data)
    {
        std::lock_guard<std::mutex> guard(m_mutex);

        m_queue.push(std::move(_data));
    }

    template<class T>
    template<class ...Ts>
    void TSQueue<T>::append(Ts &&..._args)
    {
        std::lock_guard<std::mutex> guard(m_mutex);

        m_queue.emplace(std::forward<Ts>(_args)...);
    }

    template<class T>
    void TSQueue<T>::pop()
    {
        std::lock_guard<std::mutex> guard(m_mutex);

        m_queue.pop();
    }

    template<class T>
    T TSQueue<T>::pop_front()
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        T data = std::move(m_queue.front());

        m_queue.pop();
        return data;
    }

}