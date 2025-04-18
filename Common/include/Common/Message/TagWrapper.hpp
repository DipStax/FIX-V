#pragma once

#include <string>
#include <optional>

#include "Common/Message/TagType.hpp"

namespace fix::com
{
    template<IsTag Tag>
    class TagWrapper;

    template<TagType Tag>
    class TagWrapper<Required<Tag>> : public Required<Tag>, public std::string
    {
        public:
            TagWrapper() = default;
            TagWrapper(const std::string &_str);
            TagWrapper(const char *_str);
            ~TagWrapper() = default;

            std::string value() const;

            TagWrapper &operator=(const std::string &_str);
            TagWrapper &operator=(const char *_str);

        private:
            std::string m_str;
    };

    template<TagType Tag>
    class TagWrapper<Optional<Tag>> : public Optional<Tag>
    {
        public:
            TagWrapper() = default;
            TagWrapper(const std::optional<std::string> _str);
            TagWrapper(const char *_str);
            ~TagWrapper() = default;

            std::optional<std::string> value() const;

            TagWrapper &operator=(const std::optional<std::string> _str);
            TagWrapper &operator=(const char *_str);

        private:
            std::optional<std::string> m_str = std::nullopt;
    };
}

#include "Common/Message/TagWrapper.inl"