#pragma once

#include "Common/Message/Message.hpp"

namespace fix
{
    namespace msg
    {
        using Logon = Message<'A',
            TagLists<
                RequiredTagList<Tag::NoMDEntries,
                    Required<Tag::MDEntryType>,
                    Required<Tag::MDEntryPx>,
                    Optional<Tag::MDEntrySize>
                >
            >,
            Optional<Tag::EncryptMethod>,
            Optional<Tag::HearBtInt>
        >;

        using HeartBeat = Message<'0',
            Optional<Tag::TestReqID>
        >;

        using Reject = Message<'3',
            Required<Tag::RefSeqNum>,
            Optional<Tag::RefTagId>,
            Optional<Tag::RefMsgType>,
            Optional<Tag::SessionRejectReason>,
            Optional<Tag::Text>,
        >;

        using Logout = Message<'5'>;
    }

    namespace err
    {
        constexpr const char InvalidTag[] = "0";
        constexpr const char ReqTagMissing[] = "1";
        constexpr const char NotSupporTag[] = "2";
        constexpr const char UndefineTag[] = "3";
        constexpr const char EmptyValue[] = "4";
        constexpr const char ValueOORange[] = "5";
        constexpr const char IncorrectFormat[] = "6";
        constexpr const char DecryptionIssue[] = "7";
        constexpr const char InvalidMsgType[] = "11";
    }
}