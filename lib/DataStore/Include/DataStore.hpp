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

    using NDO_List = DataStructures::List::List<void*>;

    public:
        DataStore();
        ~DataStore();

        template <typename T>
        void Get(const KeyType key, T *const data);
        template <typename T>
        void Set(const KeyType key, const T *const data);

        template <typename T>
        void Add_NDO(const KeyType key);
        template <typename T>
        void Add_NDO(const KeyType key, const T *const value);

    private:

        template <typename T>
        class DataObject {
            public:
                DataObject(KeyType key, T *data = nullptr);
                ~DataObject();

                void get(T *const data);
                void set(const T *const value);

                void lock(const char *const caller);
                void unlock(const char *const caller);

                void key();

            private:
                KeyType m_key;
                T m_value;
                bool m_locked;
                uint32_t m_checksum;
        };

        NDO_List m_DataStore;
};

} // end namespace DataStore

#endif // __DATASTORE_HPP__