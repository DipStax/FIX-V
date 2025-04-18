#pragma once

#include <tuple>

#include "Common/Message/TagWrapper.hpp"

namespace fix::com
{
    template<IsTag ...Tags>
    class TagListObject
    {
        public:
            using TagTuple = std::tuple<TagWrapper<Tags>...>;

            static TagTuple newTags();

            void add(TagTuple &_tuple);

            template<TagType Tag>
                requires IsReqTagInList<Tag, Tags...>
            std::vector<std::string> get() const;

            template<TagType Tag>
                requires IsOptTagInList<Tag, Tags...>
            std::vector<std::optional<std::string>> get() const;

            const TagTuple &get(size_t _index) const;

            std::string serialize() const;

        private:
            template<TagType Tag>
            static std::string serialize(std::vector<std::string> _data);
            template<TagType Tag>
            static std::string serialize(std::vector<std::optional<std::string>> _data);

            std::vector<TagTuple> m_data;
    };

    template<TagType Tag, IsTagWrapper ...TagWrappers>
        requires IsTagWrapperRequiredInList<Tag, TagWrappers...>
    constexpr TagWrapper<Required<Tag>> &get(std::tuple<TagWrappers...> &_data) noexcept;

    template<TagType Tag, IsTagWrapper ...TagWrappers>
        requires IsTagWrapperOptionalInList<Tag, TagWrappers...>
    constexpr TagWrapper<Optional<Tag>> &get(std::tuple<TagWrappers...> &_data) noexcept;
}

#include "Common/Message/TagListObject.inl"