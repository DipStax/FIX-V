#pragma once

#include <unordered_map>
#include <string>
#include <optional>
#include <tuple>

#include "Common/Message/Tag.hpp"
#include "Common/Message/TagType.hpp"
#include "Common/Message/TagListObject.hpp"

namespace fix::com
{
    struct MsgDeserializer;

    template<IsTag ...Tag>
    class PositionalTag
    {
    };

    template<class ...Tags>
    struct TagLists
    {
    };

    template <class T, class _T, IsTag... Tags>
    class RawMessage;

    template<IsTag ...PTags, IsTagList ...TagsList, IsTag ...Tags >
    class RawMessage<PositionalTag<PTags...>, TagLists<TagsList...>, Tags...>
    {
        public:
            RawMessage() = default;
            ~RawMessage() = default;

            template<TagType Tag>
                requires InTag<Tag, PTags...> || InTag<Tag, Tags...>
            void set(const std::string& _value);

            template<TagType Tag>
                requires IsReqTagInList<Tag, PTags...> || IsReqTagInList<Tag, Tags...>
            std::string get() const;

            template<TagType Tag>
                requires IsOptTagInList<Tag, PTags...> || IsOptTagInList<Tag, Tags...>
            std::optional<std::string> get() const;

            template<TagType Tag>
            requires InTagListIndex<Tag, TagsList...>
            constexpr meta::make_tag_list_object_t<meta::select_tag_list_t<Tag, TagsList...>> &list() noexcept;

        protected:
            [[nodiscard]] std::string serialize() const;
            void deserialize(const std::string &_str);

        private:
            using TupleHelper = std::tuple<meta::make_tag_list_object_t<TagsList>..., uint8_t>;

            std::unordered_map<TagType, std::string> m_data{};
            TupleHelper m_list;
    };

    struct MsgSerializer
    {
        template<IsTagList ...TagsList>
        using TupleHelper = std::tuple<meta::make_tag_list_object_t<TagsList>..., uint8_t>;

        template<IsTag ...Tags>
        static std::string Serialize(const std::unordered_map<TagType, std::string> &_data);
        template<>
        static std::string Serialize(const std::unordered_map<TagType, std::string> &_data);

        template<IsTagList ...TagsList>
        static std::string Serialize(const TupleHelper<TagsList...> &_data);

        private:
            static constexpr const char sep = '\01';

            template<IsOptTag Tag, IsTag ...Tags>
            static std::string SerializeImp(const std::unordered_map<TagType, std::string> &_data);
            template<IsReqTag Tag, IsTag ...Tags>
            static std::string SerializeImp(const std::unordered_map<TagType, std::string> &_data);

            template<size_t Count, size_t It, IsTagList ...TagsList>
            static std::string SerializeImp(const TupleHelper<TagsList...> &_data);
    };
}

#include "Common/Message/RawMessage.inl"