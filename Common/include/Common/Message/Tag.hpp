#pragma once

#include <stdint.h>

namespace fix
{
    /// @brief Structure containing all the [Tag](https://www.onixs.biz/fix-dictionary/4.2/fields_by_tag.html) of the FIX protocol.
    namespace Tag
    {
        constexpr const uint16_t AvgPx = 6;                     ///< Tag [6](https://www.onixs.biz/fix-dictionary/4.2/tagNum_6.html).
        constexpr const uint16_t BeginString = 8;               ///< Tag [8](https://www.onixs.biz/fix-dictionary/4.2/tagNum_8.html).
        constexpr const uint16_t BodyLength = 9;                ///< Tag [9](https://www.onixs.biz/fix-dictionary/4.2/tagNum_9.html).
        constexpr const uint16_t CheckSum = 10;                 ///< Tag [10](https://www.onixs.biz/fix-dictionary/4.2/tagNum_10.html).
        constexpr const uint16_t ClOrdID = 11;                  ///< Tag [11](https://www.onixs.biz/fix-dictionary/4.2/tagNum_11.html).
        constexpr const uint16_t CumQty = 14;                   ///< Tag [14](https://www.onixs.biz/fix-dictionary/4.2/tagNum_14.html).
        constexpr const uint16_t ExecId = 17;                   ///< Tag [17](https://www.onixs.biz/fix-dictionary/4.2/tagNum_17.html).
        constexpr const uint16_t ExecTransType = 20;            ///< Tag [20](https://www.onixs.biz/fix-dictionary/4.2/tagNum_20.html).
        constexpr const uint16_t HandlInst = 21;                ///< Tag [21](https://www.onixs.biz/fix-dictionary/4.2/tagNum_21.html).
        constexpr const uint16_t MsgSeqNum = 34;                ///< Tag [34](https://www.onixs.biz/fix-dictionary/4.2/tagNum_34.html).
        constexpr const uint16_t MsgType = 35;                  ///< Tag [35](https://www.onixs.biz/fix-dictionary/4.2/tagNum_35.html).
        constexpr const uint16_t OrderID = 37;                  ///< Tag [37](https://www.onixs.biz/fix-dictionary/4.2/tagNum_37.html).
        constexpr const uint16_t OrderQty = 38;                 ///< Tag [38](https://www.onixs.biz/fix-dictionary/4.2/tagNum_38.html).
        constexpr const uint16_t OrdStatus = 39;                ///< Tag [39](https://www.onixs.biz/fix-dictionary/4.2/tagNum_39.html).
        constexpr const uint16_t OrdType = 40;                  ///< Tag [40](https://www.onixs.biz/fix-dictionary/4.2/tagNum_40.html).
        constexpr const uint16_t OrigClOrdID = 41;              ///< Tag [41](https://www.onixs.biz/fix-dictionary/4.2/tagNum_41.html).
        constexpr const uint16_t Price = 44;                    ///< Tag [44](https://www.onixs.biz/fix-dictionary/4.2/tagNum_44.html).
        constexpr const uint16_t RefSeqNum = 45;                ///< Tag [45](https://www.onixs.biz/fix-dictionary/4.2/tagNum_45.html).
        constexpr const uint16_t SenderCompId = 49;             ///< Tag [49](https://www.onixs.biz/fix-dictionary/4.2/tagNum_49.html).
        constexpr const uint16_t SendingTime = 52;              ///< Tag [52](https://www.onixs.biz/fix-dictionary/4.2/tagNum_52.html).
        constexpr const uint16_t Side = 54;                     ///< Tag [54](https://www.onixs.biz/fix-dictionary/4.2/tagNum_54.html).
        constexpr const uint16_t Symbol = 55;                   ///< Tag [55](https://www.onixs.biz/fix-dictionary/4.2/tagNum_55.html).
        constexpr const uint16_t TargetCompId = 56;             ///< Tag [56](https://www.onixs.biz/fix-dictionary/4.2/tagNum_56.html).
        constexpr const uint16_t Text = 58;                     ///< Tag [58](https://www.onixs.biz/fix-dictionary/4.2/tagNum_58.html).
        constexpr const uint16_t TransactTime = 60;             ///< Tag [60](https://www.onixs.biz/fix-dictionary/4.2/tagNum_60.html).
        constexpr const uint16_t EncryptMethod = 98;            ///< Tag [98](https://www.onixs.biz/fix-dictionary/4.2/tagNum_98.html).
        constexpr const uint16_t HearBtInt = 108;               ///< Tag [108](https://www.onixs.biz/fix-dictionary/4.2/tagNum_108.html).
        constexpr const uint16_t MinQty = 110;                  ///< Tag [110](https://www.onixs.biz/fix-dictionary/4.2/tagNum_110.html).
        constexpr const uint16_t TestReqId = 112;               ///< Tag [112](https://www.onixs.biz/fix-dictionary/4.2/tagNum_112.html).
        constexpr const uint16_t NoRelatedSym = 146;            ///< Tag [146](https://www.onixs.biz/fix-dictionary/4.2/tagNum_146.html).
        constexpr const uint16_t ExecType = 150;                ///< Tag [150](https://www.onixs.biz/fix-dictionary/4.2/tagNum_150.html).
        constexpr const uint16_t LeavesQty = 151;               ///< Tag [151](https://www.onixs.biz/fix-dictionary/4.2/tagNum_151.html).
        constexpr const uint16_t MDReqID = 262;                 ///< Tag [262](https://www.onixs.biz/fix-dictionary/4.2/tagNum_262.html).
        constexpr const uint16_t SubscriptionRequestType = 263; ///< Tag [263](https://www.onixs.biz/fix-dictionary/4.2/tagNum_263.html).
        constexpr const uint16_t MarketDepth = 264;             ///< Tag [264](https://www.onixs.biz/fix-dictionary/4.2/tagNum_264.html).
        constexpr const uint16_t MDUpdateType = 265;            ///< Tag [265](https://www.onixs.biz/fix-dictionary/4.2/tagNum_265.html).
        constexpr const uint16_t NoMDEntryTypes = 267;          ///< Tag [267](https://www.onixs.biz/fix-dictionary/4.2/tagNum_267.html).
        constexpr const uint16_t NoMDEntries = 268;             ///< Tag [268](https://www.onixs.biz/fix-dictionary/4.2/tagNum_268.html).
        constexpr const uint16_t MDEntryType = 269;             ///< Tag [269](https://www.onixs.biz/fix-dictionary/4.2/tagNum_269.html).
        constexpr const uint16_t MDEntryPx = 270;               ///< Tag [270](https://www.onixs.biz/fix-dictionary/4.2/tagNum_270.html).
        constexpr const uint16_t MDEntrySize = 271;             ///< Tag [270](https://www.onixs.biz/fix-dictionary/4.2/tagNum_271.html).
        constexpr const uint16_t MDUpdateAction = 279;          ///< Tag [279](https://www.onixs.biz/fix-dictionary/4.2/tagNum_279.html).
        constexpr const uint16_t MDentryRefID = 280;            ///< Tag [280](https://www.onixs.biz/fix-dictionary/4.2/tagNum_280.html).
        constexpr const uint16_t RefTagId = 371;                ///< Tag [371](https://www.onixs.biz/fix-dictionary/4.2/tagNum_371.html).
        constexpr const uint16_t RefMsgType = 352;              ///< Tag [352](https://www.onixs.biz/fix-dictionary/4.2/tagNum_352.html).
        constexpr const uint16_t SessionRejectReason = 373;     ///< Tag [373](https://www.onixs.biz/fix-dictionary/4.2/tagNum_373.html).
    };
}