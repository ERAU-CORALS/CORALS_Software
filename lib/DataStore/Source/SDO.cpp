/**
 ********************************************************************************
 * @file    SDO.cpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   CORALS Software Data Object
 * @version 1.0
 * @date    2024-03-24
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#include "SDO.hpp"

#include "DS_Configuration.hpp"

namespace DataStore {

template <typename T, typename KeyType>
SoftwareDataObject<T, KeyType>::SoftwareDataObject(const KeyType key) : m_key(key), m_data(new T), m_locked(false) {}

template <typename T, typename KeyType>
SoftwareDataObject<T, KeyType>::~SoftwareDataObject() { delete m_data; }

template <typename T, typename KeyType>
void SoftwareDataObject<T, KeyType>::get(T *const data) {
    if (m_locked) {
        DS_DEBUG_PRINTLN("SDO: Data is locked.");
        return;
    }

        lock(__func__);
        memcpy(data, m_data, sizeof(T));
        unlock(__func__);
    }

template <typename T, typename KeyType>
void SoftwareDataObject<T, KeyType>::set(const T *const value) {
    if (m_locked) {
        DS_DEBUG_PRINTLN("SDO: Data is locked.");
        return;
    }

    lock(__func__);
    memcpy(m_data, value, sizeof(T));
    unlock(__func__);
}

template <typename T, typename KeyType> 
KeyType SoftwareDataObject<T, KeyType>::key() const { 
    return m_key;
}

template <typename T, typename KeyType>
void SoftwareDataObject<T, KeyType>::lock(const char *const caller) {
    if (m_locked) {
        DS_DEBUG_PRINTLN("SDO: Data is already locked.");
        return;
    }

    m_locked = true;
    m_checksum = checksum(m_data);
    DS_DEBUG_PRINT("SDO: Data locked by ");
    DS_DEBUG_PRINTLN(caller);
}

template <typename T, typename KeyType>
void SoftwareDataObject<T, KeyType>::unlock(const char *const caller) {
    if (!m_locked) {
        DS_DEBUG_PRINTLN("SDO: Data is already unlocked.");
        return;
    }

    if (m_checksum != checksum(m_data)) {
        DS_DEBUG_PRINTLN("SDO: Data unlock failed.");
        return;
    }

    m_locked = false;
    DS_DEBUG_PRINT("SDO: Data unlocked by ");
    DS_DEBUG_PRINTLN(caller);
}

template <typename T, typename KeyType>
Checksum_t SoftwareDataObject<T, KeyType>::checksum(const char *const data) {
    Checksum_t checksum = 0;
    for (uint32_t i = 0; i < sizeof(data); i++) {
        checksum += data[i];
    }
    return checksum;
}

} // end namespace DataStore