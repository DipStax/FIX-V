#include "Common/Message/TagListObject.hpp"

namespace fix::com
{
    template<IsTag ...Tags>
    TagListObject<Tags...>::TagTuple TagListObject<Tags...>::newTags()
    {
        return TagTuple();
    }

    template<IsTag ...Tags>
    void TagListObject<Tags...>::add(TagTuple &_tuple)
    {
        m_data.emplace_back(_tuple);
    }

    template<IsTag ...Tags>
    template<TagType Tag>
        requires IsReqTagInList<Tag, Tags...>
    std::vector<std::string> TagListObject<Tags...>::get() const
    {
        std::vector<std::string> result{};

        result.reserve(m_data.size());
        for (const TagTuple &_data : m_data)
            result.push_back(std::get<TagWrapper<Required<Tag>>>(_data).value());
        return result;
    }

    template<IsTag ...Tags>
    template<TagType Tag>
        requires IsOptTagInList<Tag, Tags...>
    std::vector<std::optional<std::string>> TagListObject<Tags...>::get() const
    {
        std::vector<std::optional<std::string>> result{};

        result.reserve(m_data.size());
        for (const TagTuple &_data : m_data)
            result.push_back(std::get<TagWrapper<Optional<Tag>>>(_data).value());
        return result;
    }

    template<IsTag ...Tags>
    const TagListObject<Tags...>::TagTuple &TagListObject<Tags...>::get(size_t _index) const
    {
        return m_data.at(_index);
    }

    template<IsTag ...Tags>
    std::string TagListObject<Tags...>::serialize() const
    {
        return (serialize<Tags::Tag>(this->get<Tags::Tag>()) + ...);
    }

    template<IsTag ...Tags>
    template<TagType Tag>
    std::string TagListObject<Tags...>::serialize(std::vector<std::string> _data)
    {
        std::string format{};

        for (const std::string &_val : _data)
            format += _val + ",";
        if (_data.size())
            format.pop_back();
        return std::to_string(Tag) + "=" + format;
    }

    template<IsTag ...Tags>
    template<TagType Tag>
    std::string TagListObject<Tags...>::serialize(std::vector<std::optional<std::string>> _data)
    {
        std::string format{};

        for (const std::optional<std::string> &_val : _data) {
            if (_val.has_value())
                format += _val.value();
            format += ",";
        }
        if (_data.size())
            format.pop_back();
        return std::to_string(Tag) + "=" + format;
    }

    template<TagType Tag, IsTagWrapper ...Ts>
        requires IsTagWrapperRequiredInList<Tag, Ts...>
    constexpr TagWrapper<Required<Tag>> &get(std::tuple<Ts...> &_data) noexcept
    {
        return std::get<TagWrapper<Required<Tag>>>(_data);
    }

    template<TagType Tag, IsTagWrapper ...Ts>
        requires IsTagWrapperOptionalInList<Tag, Ts...>
    constexpr TagWrapper<Optional<Tag>> &get(std::tuple<Ts...> &_data) noexcept
    {
        return std::get<TagWrapper<Optional<Tag>>>(_data);
    }
}
