/**
 ********************************************************************************
 * @file    RxMessageBase.tpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Receive Message Base Class for CORALS Processes
 * @version 1.0
 * @date    2024-03-20
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __RX_MESSAGE_BASE_TPP__
#define __RX_MESSAGE_BASE_TPP__

#include <string.h>

#include "MessageBase.tpp"

namespace Telecommunication {

template <typename T> // Struct Type
class RxMessageBase : public MessageBase<T>, public MessageHandler {
    
    using Base = MessageBase<T>;
    using MessagePacket = typename Base::MessagePacket;

    public:
        RxMessageBase(const char *UUID, T default_value = { 0 }) : MessageBase<T>(UUID, BLERead, default_value) {};
        virtual ~RxMessageBase() {};

        void get(T *const value) {
            memcpy(value, &Base::mValue, sizeof(T));
        };

        inline bool updated() {
            return Base::mCharacteristic.valueUpdated();
        };

        void run() {
            if (Base::mCharacteristic.written()) {
                MessagePacket packet;

                Base::mCharacteristic.readValue(packet.raw, Base::mPacketSize);
                
                uint32_t calculated_crc = Base::crc32(0, packet.packet.data, sizeof(T));

                if (packet.packet.crc == calculated_crc) {
                    memcpy(&Base::mValue, &packet.packet.data, sizeof(T));
                }
            }
        };
};

} // namespace Telecommunication

#endif // __RX_MESSAGE_BASE_TPP__