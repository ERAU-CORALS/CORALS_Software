/**
 ********************************************************************************
 * @file    MessageBase.tpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Message Base Class for CORALS Processes
 * @version 1.0
 * @date    2024-03-20
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __MESSAGE_BASE_TPP__
#define __MESSAGE_BASE_TPP__

#include <ArduinoBLE.h>
#include <stdint.h>

#include "TC_Configuration.hpp"

namespace Telecommunication {

template <typename T> // Struct Type
class MessageBase {
    public:
        MessageBase(const char *UUID, uint16_t properties, T default_value = { 0 }) : mCharacteristic(UUID, properties, default_value, sizeof(T) + sizeof(uint32_t)), mPacketSize(sizeof(T) + sizeof(uint32_t)) {};
        virtual ~MessageBase();

        void AddService(BLEService &service) {
            service.addCharacteristic(mCharacteristic);
        };

    protected:
        BLECharacteristic mCharacteristic;
        const size_t mPacketSize;

        using MessagePacket = union {
            struct {
                T data;
                uint32_t crc;
            } packed packet;
            uint8_t raw[sizeof(T) + sizeof(uint32_t)];
        };

        T mValue;

        uint32_t crc32(const uint8_t *buffer, const uint32_t size) {
            uint32_t crc = 0xFFFFFFFF;
            for (uint32_t i = 0; i < size; i++) {
                crc ^= buffer[i];
                for (uint8_t j = 0; j < 8; j++) crc = (crc >> 1) ^ (0xEDB88320 & (-(crc & 1)));
            }
            return ~crc;
        }
};

class MessageHandler {
    public:
        virtual void run() = 0;
};

} // namespace Telecommunication









#endif // __MESSAGE_BASE_TPP__