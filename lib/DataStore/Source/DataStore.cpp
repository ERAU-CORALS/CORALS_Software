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
#include "SDO.hpp"

namespace DataStore {

using DataStructures::List::ListSize_t;

template <typename KeyType>
DataStore<KeyType>::DataStore() : m_DataStore{} {
    DS_DEBUG_PRINTLN("DataStore Initialized.");
}

template <typename KeyType>
DataStore<KeyType>::~DataStore() {
    DS_DEBUG_PRINTLN("DataStore Deinitialized.");
}

template <typename KeyType>
template <typename T>
void DataStore<KeyType>::Get(const KeyType key, T **const data) {
    SoftwareDataObject<T, KeyType> *SDO = nullptr;
    ListSize_t i = 0;
    
    do {
        SDO = (SoftwareDataObject<T, KeyType>*)m_DataStore[i];
    } while (SDO->key() != key && i++ < m_DataStore.size());
    
    if (i == m_DataStore.size()) {
        DS_DEBUG_PRINTLN("DataStore: Key not found.");
        return;
    }

    SDO->lock(__func__);
    SDO->get(data);
    SDO->unlock(__func__);
}

template <typename KeyType>
template <typename T>
void DataStore<KeyType>::Set (const KeyType key, const T *const data) {
    SoftwareDataObject<T, KeyType> *SDO = nullptr;
    ListSize_t i = 0;
    
    do {
        SDO = (SoftwareDataObject<T, KeyType>*)m_DataStore[i++];
    } while (SDO->key() != key && i < m_DataStore.size());
    
    if (i == m_DataStore.size()) {
        DS_DEBUG_PRINTLN("DataStore: Key not found.");
        return;
    }

    SDO->lock(__func__);
    SDO->set(data);
    SDO->unlock(__func__);
}

template <typename KeyType>
template <typename T>
void DataStore<KeyType>::Add_SDO (const KeyType key) {
    DS_DEBUG_PRINTLN("DataStore: Adding SDO.");

    SoftwareDataObject<T, KeyType> *SDO = new SoftwareDataObject<T, KeyType>(key);
    m_DataStore.push_back((void*)SDO);

    DS_DEBUG_PRINTLN("DataStore: SDO added.");
}

template <typename KeyType>
template <typename T>
void DataStore<KeyType>::Add_SDO (const KeyType key, const T *const value) {
    DS_DEBUG_PRINTLN("DataStore: Adding SDO with value.");

    SoftwareDataObject<T, KeyType> *SDO = SoftwareDataObject<T, KeyType>(key);
    SDO->set(value);
    m_DataStore.push_back((void*)SDO);

    DS_DEBUG_PRINTLN("DataStore: SDO added.");
}

} // namespace DataStore