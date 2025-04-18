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
}