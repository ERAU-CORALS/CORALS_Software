/**
 ********************************************************************************
 * @file    DataStore.cpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   CORALS DataStore Class Implementation
 * @version 1.0
 * @date    2024-03-24
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#include "DataStore.hpp"

#include <string.h>

#include "DS_Configuration.hpp"

namespace DataStore {

using DataStructures::List::ListSize_t;

template <typename KeyType>
DataStore<KeyType>::DataStore () : m_DataStore{} {
    DS_DEBUG_PRINTLN("DataStore Initialized.");
}

template <typename KeyType>
DataStore<KeyType>::~DataStore () {
    DS_DEBUG_PRINTLN("DataStore Deinitialized.");
}

template <typename KeyType>
template <typename T>
void DataStore<KeyType>::Get (const KeyType key, T *const data) {
    DataStore<T> *NDO = nullptr;
    ListSize_t i = 0;
    
    do {
        NDO = (DataStore<T>*)m_DataStore[i++];
    } while (NDO->key() != key && i < m_DataStore.size());
    
    if (i == m_DataStore.size()) {
        DS_DEBUG_PRINTLN("DataStore: Key not found.");
        return;
    }

    NDO->lock(__func__);
    NDO->get(data);
    NDO->unlock(__func__);
}

template <typename KeyType>
template <typename T>
void DataStore<KeyType>::Set (const KeyType key, const T *const data) {
    DataStore<T> *NDO = nullptr;
    ListSize_t i = 0;
    
    do {
        NDO = (DataStore<T>*)m_DataStore[i++];
    } while (NDO->key() != key && i < m_DataStore.size());
    
    if (i == m_DataStore.size()) {
        DS_DEBUG_PRINTLN("DataStore: Key not found.");
        return;
    }

    NDO->lock(__func__);
    NDO->set(data);
    NDO->unlock(__func__);
}

template <typename KeyType>
template <typename T>
void DataStore<KeyType>::Add_NDO (const KeyType key) {
    using DataStructures::List::ListSize_t;
    for (ListSize_t i = m_DataStore.size(); i < (int)key; i++) {
        m_DataStore.push_back(nullptr);
    }

    DataStore<T> *NDO = new DataStore<T>();
    m_DataStore.push_back((void*)NDO);
}

template <typename KeyType>
template <typename T>
void DataStore<KeyType>::Add_NDO (const KeyType key, const T *const value) {
    using DataStructures::List::ListSize_t;
    for (ListSize_t i = m_DataStore.size(); i < (int)key; i++) {
        m_DataStore.push_back(nullptr);
    }
    DataStore<T> *NDO = new DataStore<T>(value);
    m_DataStore.push_back((void*)NDO);
}

template <typename KeyType>
template <typename T>
DataStore<KeyType>::DataObject<T>::DataObject (KeyType key, T *const data) : m_key(key), m_locked(false) {
    DS_DEBUG_PRINTLN("DataObject Initialized.");

    memcpy(&m_value, data, sizeof(T));
    
    DS_DEBUG_PRINTLN("DataObject Initialized.");
}

template <typename KeyType>
template <typename T>
DataStore<KeyType>::DataObject<T>::~DataObject () {
    DS_DEBUG_PRINTLN("DataObject Deinitialized.");
}

template <typename KeyType>
template <typename T>
void DataStore<KeyType>::DataObject<T>::get (T *const data) {
    memcpy(data, &m_value, sizeof(T));
}

template <typename KeyType>
template <typename T>
void DataStore<KeyType>::DataObject<T>::set (const T *const value) {
    memcpy(&m_value, value, sizeof(T));
}

template <typename KeyType>
template <typename T>
void DataStore<KeyType>::DataObject<T>::lock (const char *const caller) {
    if (m_locked) {
        DS_DEBUG_PRINTLN("DataObject: Already locked.");
        return;
    }

    for (uint32_t i = 0; i < strlen(caller); i++) {
        m_checksum += caller[i];
    }

    m_locked = true;

    DS_DEBUG_PRINT("DataObject: Locked by ");
    DS_DEBUG_PRINTLN(caller);
}

template <typename KeyType>
template <typename T>
void DataStore<KeyType>::DataObject<T>::unlock (const char *caller) {
    if (!m_locked) {
        DS_DEBUG_PRINTLN("DataObject: Already unlocked.");
        return;
    }

    uint32_t checksum = 0;
    for (uint32_t i = 0; i < strlen(caller); i++) {
        checksum += caller[i];
    }

    if (checksum != m_checksum) {
        DS_DEBUG_PRINTLN("DataObject: Unlock failed.");
        return;
    }

    m_locked = false;

    DS_DEBUG_PRINT("DataObject: Unlocked by ");
    DS_DEBUG_PRINTLN(caller);
}

template <typename KeyType>
template <typename T>
void DataStore<KeyType>::DataObject<T>::key () {
    return m_key;
}

} // namespace DataStore