#include "Common/Message/TagWrapper.hpp"

namespace fix::com
{
    template<TagType Tag>
    TagWrapper<Required<Tag>>::TagWrapper(const std::string &_str)
        : m_str(_str)
    {
    }

    template<TagType Tag>
    TagWrapper<Required<Tag>>::TagWrapper(const char* _str)
        : m_str(_str)
    {
    }

    template<TagType Tag>
    std::string TagWrapper<Required<Tag>>::value() const
    {
        return m_str;
    }

    template<TagType Tag>
    TagWrapper<Required<Tag>> &TagWrapper<Required<Tag>>::operator=(const std::string &_str)
    {
        m_str = _str;
        return *this;
    }

    template<TagType Tag>
    TagWrapper<Required<Tag>> &TagWrapper<Required<Tag>>::operator=(const char* _str)
    {
        m_str = std::string(_str);
        return *this;
    }

    template<TagType Tag>
    TagWrapper<Optional<Tag>>::TagWrapper(const std::optional<std::string> _str)
        : m_str(_str)
    {
    }

    template<TagType Tag>
    TagWrapper<Optional<Tag>>::TagWrapper(const char* _str)
        : m_str(std::string(_str))
    {
    }

    template<TagType Tag>
    std::optional<std::string> TagWrapper<Optional<Tag>>::value() const
    {
        return m_str;
    }

    template<TagType Tag>
    TagWrapper<Optional<Tag>> &TagWrapper<Optional<Tag>>::operator=(const std::optional<std::string> _str)
    {
        m_str = _str;
        return *this;
    }

    template<TagType Tag>
    TagWrapper<Optional<Tag>> &TagWrapper<Optional<Tag>>::operator=(const char* _str)
    {
        m_str = std::string(_str);
        return *this;
    }
}