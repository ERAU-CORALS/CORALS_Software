/**
 ********************************************************************************
 * @file    TxMessageBase.tpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Transmit Message Base Class for CORALS Processes
 * @version 1.0
 * @date    2024-03-20
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __TX_MESSAGE_BASE_TPP__
#define __TX_MESSAGE_BASE_TPP__

#include <string.h>

#include "RxMessageBase.tpp"
#include "TxMessageBase.tpp"

namespace Telecommunication {

enum class TxCondition {
    ON_CHANGE,
    ON_INTERVAL,
    ON_CHANGE_OR_INTERVAL
};

template <typename T> // Struct Type
class TxMessageBase : public MessageBase<T>, public MessageHandler {
    
    using Base = MessageBase<T>;
    using MessagePacket = typename Base::MessagePacket;

    public:
        TxMessageBase(const char *UUID, const TxCondition condition, const uint32_t interval_ms = 0) : MessageBase<T>(UUID, BLEWrite), mCondition(condition), mInterval(interval_ms), mLastRun(0) {};
        ~TxMessageBase() {};

        void set(const T *const value) {
            memcpy(&(Base::mValue), value, sizeof(T));
            mUpdated = true;
        };

        void run() {
            if (should_run()) {
                MessagePacket packet;

                memcpy(&packet.packet.data, &(Base::mValue), sizeof(T));
                packet.packet.crc = Base::crc32(packet.raw, sizeof(T));

                Base::mCharacteristic.writeValue(packet.raw, sizeof(T) + sizeof(uint32_t));

                mUpdated = false;
            }
        };

    private:
        const TxCondition mCondition;

        bool mUpdated;

        const uint32_t mInterval;
        uint32_t mLastRun;

        bool should_run() {
            const bool timeframe_reset = ((millis() - mLastRun) >= mInterval);
            if (timeframe_reset) mLastRun = millis();

            switch (mCondition) {
                case TxCondition::ON_CHANGE:
                    return mUpdated;
                case TxCondition::ON_INTERVAL:
                    return timeframe_reset;
                case TxCondition::ON_CHANGE_OR_INTERVAL:
                    return mUpdated || timeframe_reset;
                default:
                    return false;
            }
        }
};

} // namespace Telecommunication

#endif // __TX_MESSAGE_BASE_TPP__