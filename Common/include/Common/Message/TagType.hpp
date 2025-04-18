#pragma once

#include "Common/Message/meta.hpp"

namespace fix::com
{
    template<TagType TTag>
    struct Required
    {
        static constexpr const TagType Tag = TTag;
    };

    template<TagType TTag>
    struct Optional
    {
        static constexpr const TagType Tag = TTag;
    };

    template<TagType TTag, IsTag ...Tags>
    struct RequiredTagList
    {
        static constexpr const TagType index = TTag;
    };

    template<TagType TTag, IsTag ...Tags>
    struct OptionalTagList
    {
        static constexpr const TagType index = TTag;
    };
}