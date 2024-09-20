/**
 ********************************************************************************
 * @file    DataStore.hpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   CORALS DataStore Class Implementation
 * @version 1.0
 * @date    2024-03-24
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __DATASTORE_HPP__
#define __DATASTORE_HPP__

#include <stdint.h>

#include "List.tpp"

namespace DataStore {

template <typename KeyType>
class DataStore {

    using SDO_List = DataStructures::List::List<void*>;

    public:
        DataStore();
        ~DataStore();

        template <typename T>
        void Get(const KeyType key, T *const data);
        template <typename T>
        void Set(const KeyType key, const T *const data);

        template <typename T>
        void Add_SDO(const KeyType key);
        template <typename T>
        void Add_SDO(const KeyType key, const T *const value);

    private:

        SDO_List m_DataStore;
};

} // end namespace DataStore

#endif // __DATASTORE_HPP__