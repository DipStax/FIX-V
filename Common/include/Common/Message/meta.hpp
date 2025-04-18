#pragma once

#include <concepts>
#include <type_traits>

namespace fix::com
{
    using TagType = uint16_t;

    template<TagType TTag>
    struct Required;

    template<TagType TTag>
    struct Optional;
}

namespace meta
{
    template<class T>
    struct Is_Tag : std::false_type
    {
    };

    template<fix::com::TagType Tag>
    struct Is_Tag<fix::com::Required<Tag>> : std::true_type
    {
    };

    template<fix::com::TagType Tag>
    struct Is_Tag<fix::com::Optional<Tag>> : std::true_type
    {
    };

    template<class T>
    using is_tag = Is_Tag<T>;

    template<class T>
    constexpr const bool is_tag_v = is_tag<T>::value;
}

template<class T>
concept IsTag = meta::is_tag_v<T> && requires {
    { T::Tag } -> std::same_as<const fix::com::TagType &>;
};

namespace meta
{
    template<template<auto> class T, class _T>
    struct Is_Base_Of_NTTP
    {
        template<auto __T>
        static constexpr std::true_type  test(const T<__T>*);
        static constexpr std::false_type test(...);
        using type = decltype(test(std::declval<_T*>()));
    };

    template<template<auto> class T, class _T>
    using is_base_of_template_nttp = typename Is_Base_Of_NTTP<T, _T>::type;

    template<template<auto> class T, class _T>
    constexpr bool is_base_of_template_nttp_v = is_base_of_template_nttp<T, _T>::value;
}

template<class T>
concept IsOptTag = IsTag<T> && meta::is_base_of_template_nttp_v<fix::com::Optional, T>;

template<class T>
concept IsReqTag = IsTag<T> && meta::is_base_of_template_nttp_v<fix::com::Required, T>;

namespace meta
{
    template<fix::com::TagType Tag, IsTag ...Ts>
    struct In_Tag;

    template<fix::com::TagType T, fix::com::TagType _T, IsTag ...Ts>
    struct In_Tag<T, fix::com::Optional<_T>, Ts...> : In_Tag<T, Ts...>
    {
    };

    template<fix::com::TagType T, fix::com::TagType _T, IsTag ...Ts>
    struct In_Tag<T, fix::com::Required<_T>, Ts...> : In_Tag<T, Ts...>
    {
    };

    template<fix::com::TagType T, IsTag ...Ts>
    struct In_Tag<T, fix::com::Required<T>, Ts...> : std::true_type
    {
    };

    template<fix::com::TagType T, IsTag ...Ts>
    struct In_Tag<T, fix::com::Optional<T>, Ts...> : std::true_type
    {
    };

    template<fix::com::TagType T>
    struct In_Tag<T> : std::false_type
    {
    };

    template<fix::com::TagType T, IsTag ...Ts>
    using in_tag = In_Tag<T, Ts...>;

    template<fix::com::TagType T, IsTag ...Ts>
    constexpr const bool in_tag_v = in_tag<T, Ts...>::value;
}

template<fix::com::TagType T, class ...Ts>
concept InTag = meta::in_tag_v<T, Ts...>;

namespace meta
{
    template<fix::com::TagType Tag, template<fix::com::TagType> class TagImp, class ...Ts>
    struct IsTagInList;

    template<fix::com::TagType T, template<fix::com::TagType> class TagImp, IsTag _T, IsTag ...Ts>
    struct IsTagInList<T, TagImp, _T, Ts...> : IsTagInList<T, TagImp, Ts...>
    {
    };

    template<fix::com::TagType T, template<fix::com::TagType> class TagImp, class ...Ts>
    struct IsTagInList<T, TagImp, TagImp<T>, Ts...> : std::true_type
    {
    };

    template<fix::com::TagType T, template<fix::com::TagType> class TagImp>
    struct IsTagInList<T, TagImp> : std::false_type
    {
    };

    template<fix::com::TagType T, template<fix::com::TagType> class TagImp, class ...Ts>
    using is_tag_in_list = IsTagInList<T, TagImp, Ts...>;

    template<fix::com::TagType T, template<fix::com::TagType> class TagImp, class ...Ts>
    constexpr const bool is_tag_in_list_v = is_tag_in_list<T, TagImp, Ts...>::value;
}

template<fix::com::TagType T, class ...Ts>
concept IsOptTagInList = meta::is_tag_in_list_v<T, fix::com::Optional, Ts...>;

template<fix::com::TagType T, class ...Ts>
concept IsReqTagInList = meta::is_tag_in_list_v<T, fix::com::Required, Ts...>;

namespace fix::com
{
    template<TagType TTag, IsTag ...Tags>
    struct RequiredTagList;

    template<TagType TTag, IsTag ...Tags>
    struct OptionalTagList;
}

namespace meta
{
    template<class T>
    struct Is_Tag_List : std::false_type
    {
    };

    template<fix::com::TagType Tag, IsTag ...Tags>
    struct Is_Tag_List<fix::com::RequiredTagList<Tag, Tags...>> : std::true_type
    {
    };

    template<fix::com::TagType Tag, IsTag ...Tags>
    struct Is_Tag_List<fix::com::OptionalTagList<Tag, Tags...>> : std::true_type
    {
    };

    template<class T>
    using is_tag_list = Is_Tag_List<T>;

    template<class T>
    constexpr const bool is_tag_list_v = is_tag_list<T>::value;
}

template<class T>
concept IsTagList = meta::is_tag_list_v<T> && requires () {
    { T::index } -> std::same_as<const fix::com::TagType &>;
};

namespace meta
{
    template<fix::com::TagType Tag, IsTagList ...TagsList>
    struct Is_Tag_List_Index;

    template<fix::com::TagType Tag, IsTag ...Tags, IsTagList ...TagsList>
    struct Is_Tag_List_Index<Tag, fix::com::RequiredTagList<Tag, Tags...>, TagsList...> : std::true_type
    {
    };

    template<fix::com::TagType Tag, IsTag ...Tags, IsTagList ...TagsList>
    struct Is_Tag_List_Index<Tag, fix::com::OptionalTagList<Tag, Tags...>, TagsList...> : std::true_type
    {
    };

    template<fix::com::TagType Tag>
    struct Is_Tag_List_Index<Tag> : std::false_type
    {
    };

    template<fix::com::TagType Tag, IsTagList ...TagsList>
    using in_tag_list_index = Is_Tag_List_Index<Tag, TagsList...>;

    template<fix::com::TagType Tag, IsTagList ...TagsList>
    constexpr const bool in_tag_list_index_v = in_tag_list_index<Tag, TagsList...>::value;
}

template<fix::com::TagType Tag, class ...TagsList>
concept InTagListIndex = (IsTagList<TagsList> && ...) && meta::in_tag_list_index_v<Tag, TagsList...>;

namespace fix::com
{
    template<IsTag ...Tags>
    class TagListObject;
}

namespace meta
{
    template<IsTagList T>
        requires IsTagList<T>
    struct Make_Tag_List_Object;

    template<template<fix::com::TagType, IsTag ...> class Container, fix::com::TagType Tag, IsTag ...Tags>
        requires IsTagList<Container<Tag, Tags...>>
    struct Make_Tag_List_Object<Container<Tag, Tags...>>
    {
        using type = fix::com::TagListObject<Tags...>;
    };

    template<IsTagList T>
    using make_tag_list_object = Make_Tag_List_Object<T>;

    template<IsTagList T>
    using make_tag_list_object_t = typename make_tag_list_object<T>::type;

    template<fix::com::TagType Tag, IsTagList ...Ts>
    struct Select_Tag_List;

    template<fix::com::TagType Tag, IsTagList TagList, IsTagList ...TagLists>
    struct Select_Tag_List<Tag, TagList, TagLists...>
    {
        static constexpr const fix::com::TagType tag_index = TagList::index;

        using type = typename lazy_conditional_t<tag_index == Tag,
            std::type_identity<TagList>,
            Select_Tag_List<Tag, TagLists...>
        >::type;
    };

    template<fix::com::TagType Tag>
    struct Select_Tag_List<Tag>
    {
        static_assert(std::same_as<void,int>, "Tag not found, see template build stack");
    };

    template<fix::com::TagType Tag, IsTagList ...Ts>
    using select_tag_list = Select_Tag_List<Tag, Ts...>;

    template<fix::com::TagType Tag, IsTagList ...Ts>
    using select_tag_list_t = typename Select_Tag_List<Tag, Ts...>::type;
}

namespace fix::com
{
    template<IsTag Tag>
    class TagWrapper;
}

namespace meta
{
    template<class T>
    struct Is_Tag_Wrapper : std::false_type
    {
    };

    template<fix::com::TagType Tag>
    struct Is_Tag_Wrapper<fix::com::TagWrapper<fix::com::Required<Tag>>> : std::true_type
    {
    };

    template<fix::com::TagType Tag>
    struct Is_Tag_Wrapper<fix::com::TagWrapper<fix::com::Optional<Tag>>> : std::true_type
    {
    };

    template<class T>
    using is_tag_wrapper = Is_Tag_Wrapper<T>;

    template<class T>
    constexpr const bool is_tag_wrapper_v = is_tag_wrapper<T>::value;
}

template<class T>
concept IsTagWrapper = meta::is_tag_wrapper_v<T> && requires () {
    { T::Tag } -> std::same_as<const fix::com::TagType &>;
};

namespace meta
{
    template<fix::com::TagType Tag, template<fix::com::TagType> class TagImp, IsTagWrapper ...Ts>
    struct Is_TagWrapper_In_List;

    template<fix::com::TagType Tag, template<fix::com::TagType> class TagImp, IsTagWrapper Wrapper, IsTagWrapper ...TagWrappers>
    struct Is_TagWrapper_In_List<Tag, TagImp, Wrapper, TagWrappers...> : Is_TagWrapper_In_List<Tag, TagImp, TagWrappers...>
    {
    };

    template<fix::com::TagType Tag, template<fix::com::TagType> class TagImp, IsTagWrapper ...TagWrappers>
    struct Is_TagWrapper_In_List<Tag, TagImp, fix::TagWrapper<TagImp<Tag>>, TagWrappers...> : std::true_type
    {
    };

    template<fix::com::TagType Tag, template<fix::com::TagType> class TagImp>
    struct Is_TagWrapper_In_List<Tag, TagImp> : std::false_type
    {
    };

    template<fix::com::TagType Tag, template<fix::com::TagType> class TagImp, IsTagWrapper ...TagWrappers>
    using is_tagwrapper_in_list = Is_TagWrapper_In_List<Tag, TagImp, TagWrappers...>;

    template<fix::com::TagType Tag, template<fix::com::TagType> class TagImp, IsTagWrapper ...TagWrappers>
    constexpr const bool is_tagwrapper_in_list_v = is_tagwrapper_in_list<Tag, TagImp, TagWrappers...>::value;

}

template<fix::com::TagType T, class ...Ts>
concept IsTagWrapperRequiredInList = meta::is_tagwrapper_in_list_v<T, fix::com::Required, Ts...>;

template<fix::com::TagType T, class ...Ts>
concept IsTagWrapperOptionalInList = meta::is_tagwrapper_in_list_v<T, fix::com::Optional, Ts...>;