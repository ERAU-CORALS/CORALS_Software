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
    public:
        RxMessageBase(const char *UUID, T default_value = { 0 }) : MessageBase<T>(UUID, BLECharacteristic::PROPERTY_READ, default_value) {};
        virtual ~RxMessageBase() {};

        void get(T *const value) {
            memcpy(value, &mValue, sizeof(T));
        };

        void run() {
            if (mCharacteristic.written()) {
                MessagePacket packet;

                mCharacteristic.readValue(packet.raw, buffer_size);
                
                uint32_t calculated_crc = crc32(0, packet.packet.data, sizeof(T));

                if (packet.packet.crc == calculated_crc) {
                    memcpy(&mValue, &packet.packet.data, sizeof(T));
                }
            }
        };
};

} // namespace Telecommunication

#endif // __RX_MESSAGE_BASE_TPP__