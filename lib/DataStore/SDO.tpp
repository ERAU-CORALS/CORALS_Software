/**
 ********************************************************************************
 * @file    SDO.tpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   CORALS Software Data Object
 * @version 1.0
 * @date    2024-03-24
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __SDO_TPP__
#define __SDO_TPP__

#include <stdint.h>

#include "DS_Configuration.hpp"
#include "DataStore.tpp"

namespace DataStore {

using Checksum_t = uint32_t;

template <typename T, typename KeyType>
class SoftwareDataObject {

    using Data_t = T *const;

    public:
        SoftwareDataObject(const KeyType key) : m_key(key), m_data(new T), m_locked(false) { /* Do Nothing */ }
        ~SoftwareDataObject() { delete m_data; }

        void get(T *const data) {
            if (m_locked) {
                DS_DEBUG_PRINTLN("SDO: Data is locked.");
                return;
            }

            lock(__func__);
            memcpy(data, m_data, sizeof(T));
            unlock(__func__);
        }

        void set(const T *const value) {
            if (m_locked) {
                DS_DEBUG_PRINTLN("SDO: Data is locked.");
                return;
            }

            lock(__func__);
            memcpy(m_data, value, sizeof(T));
            unlock(__func__);
        }

        KeyType key() const {
            return m_key;
        }

        void lock(const char *const caller) {
            if (m_locked) {
                DS_DEBUG_PRINTLN("SDO: Data is already locked.");
                return;
            }

            m_locked = true;
            m_checksum = checksum(caller);
            DS_DEBUG_PRINT("SDO: Data locked by ");
            DS_DEBUG_PRINTLN(caller);
        }

        void unlock(const char *const caller) {
            if (!m_locked) {
                DS_DEBUG_PRINTLN("SDO: Data is already unlocked.");
                return;
            }

            if (m_checksum != checksum(caller)) {
                DS_DEBUG_PRINTLN("SDO: Data unlock failed.");
                return;
            }

            m_locked = false;
            DS_DEBUG_PRINT("SDO: Data unlocked by ");
            DS_DEBUG_PRINTLN(caller);
        }

        Checksum_t checksum(const char *const data) {
            Checksum_t checksum = 0;
            for (uint8_t i = 0; i < sizeof(T); i++) {
                checksum += data[i];
            }
            return checksum;
        }

    private:
        const KeyType m_key;
        Data_t m_data;
        bool m_locked;

        Checksum_t m_checksum;
};

} // namespace DataStore

#endif // __SDO_TPP__