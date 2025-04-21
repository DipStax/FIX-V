#include "Common/Message/RawMessage.hpp"

namespace fix::com
{
    template<IsTag ...PTags, IsTagList ...TagsList, IsTag ...Tags>
    template<TagType Tag>
        requires InTag<Tag, PTags...> || InTag<Tag, Tags...>
    void RawMessage<PositionalTag<PTags...>, TagLists<TagsList...>, Tags...>::set(const std::string &_value)
    {
        m_data[Tag] = _value;
    }

    template<IsTag ...PTags, IsTagList ...TagsList, IsTag ...Tags>
    template<TagType Tag>
        requires IsReqTagInList<Tag, PTags...> || IsReqTagInList<Tag, Tags...>
    std::string RawMessage<PositionalTag<PTags...>, TagLists<TagsList...>, Tags...>::get() const
    {
        if (!m_data.contains(Tag))
            throw std::runtime_error("Required tag not found");
        return m_data.at(Tag);
    }

    template<IsTag ...PTags, IsTagList ...TagsList, IsTag ...Tags>
    template<TagType Tag>
        requires IsOptTagInList<Tag, PTags...> || IsOptTagInList<Tag, Tags...>
    std::optional<std::string> RawMessage<PositionalTag<PTags...>, TagLists<TagsList...>, Tags...>::get() const
    {
        if (!m_data.contains(Tag))
            return std::nullopt;
        return m_data.at(Tag);
    }

    template<IsTag ...PTags, IsTagList ...TagsList, IsTag ...Tags>
    template<TagType Tag>
        requires InTagListIndex<Tag, TagsList...>
    constexpr meta::make_tag_list_object_t<meta::select_tag_list_t<Tag, TagsList...>> &RawMessage<PositionalTag<PTags...>, TagLists<TagsList...>, Tags...>::list() noexcept
    {
        return std::get<meta::make_tag_list_object_t<meta::select_tag_list_t<Tag, TagsList...>>>(m_list);
    }

    template<IsTag ...PTags, IsTagList ...TagsList, IsTag ...Tags>
    std::string RawMessage<PositionalTag<PTags...>, TagLists<TagsList...>, Tags...>::serialize() const
    {
        std::string format = MsgSerializer::Serialize<PTags...>(m_data);

        if constexpr (sizeof...(TagsList) != 0)
            format += MsgSerializer::Serialize<TagsList...>(m_list);
        return format + MsgSerializer::Serialize<Tags...>(m_data);
    }

    template<IsTag ...PTags, IsTagList ...TagsList, IsTag ...Tags>
    void RawMessage<PositionalTag<PTags...>, TagLists<TagsList...>, Tags...>::deserialize(const std::string &_msg)
    {
        // if (((size_t == PTags::Tag) || ...) || ((size_t == Tags::Tag) || ...))
        //     try_emplace();
    }

    template<IsTag ...Tags>
    std::string MsgSerializer::Serialize(const std::unordered_map<uint16_t, std::string> &_data)
    {
        return MsgSerializer::SerializeImp<Tags...>(_data);
    }

    template<>
    std::string MsgSerializer::Serialize(const std::unordered_map<uint16_t, std::string> &_data)
    {
        return "";
    }

    template<IsTagList ...TagsList>
    std::string MsgSerializer::Serialize(const TupleHelper<TagsList...> &_data)
    {
        return SerializeImp<std::tuple_size<TupleHelper<TagsList...>>::value, 0, TagsList...>(_data);
    }

    template<IsOptTag Tag, IsTag ...Tags>
    std::string MsgSerializer::SerializeImp(const std::unordered_map<uint16_t, std::string> &_data)
    {
        std::string format{};

        if (_data.contains(Tag::Tag))
            format = std::to_string(Tag::Tag) + "=" + _data.at(Tag::Tag) + sep;
        if constexpr (sizeof...(Tags) != 0)
            return format + MsgSerializer::SerializeImp<Tags...>(_data);
        else
            return format;
    }

    template<IsReqTag Tag, IsTag ...Tags>
    std::string MsgSerializer::SerializeImp(const std::unordered_map<uint16_t, std::string> &_data)
    {
        if (!_data.contains(Tag::Tag))
            throw std::runtime_error("Missing required tag: " + std::to_string(Tag::Tag));
        std::string format = std::to_string(Tag::Tag) + "=" + _data.at(Tag::Tag) + sep;

        if constexpr (sizeof...(Tags) != 0)
            return format + MsgSerializer::SerializeImp<Tags...>(_data);
        else
            return format;
    }

    template<size_t Count, size_t It, IsTagList ...TagsList>
    std::string MsgSerializer::SerializeImp(const TupleHelper<TagsList...> &_data)
    {
        if constexpr (Count - 2 == It)
            return std::get<It>(_data).serialize();
        else
            return std::get<It>(_data).serialize() + SerializeImp<Count, It + 1, TagsList...>(_data);
    }
}