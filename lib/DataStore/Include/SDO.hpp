/**
 ********************************************************************************
 * @file    SDO.hpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   CORALS Software Data Object
 * @version 1.0
 * @date    2024-03-24
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __SDO_HPP__
#define __SDO_HPP__

#include <stdint.h>

#include "DS_Configuration.hpp"
#include "DataStore.hpp"

namespace DataStore {

using Checksum_t = uint32_t;

template <typename T, typename KeyType>
class SoftwareDataObject {

    using Data_t = T *const;

    public:
        SoftwareDataObject(const KeyType key);
        ~SoftwareDataObject();

        void get(T *const data);
        void set(const T *const value);
        KeyType key() const;
    private:
        const KeyType m_key;
        Data_t m_data;
        bool m_locked;

        Checksum_t m_checksum;

        friend class DataStore<KeyType>;

        void lock(const char *const caller);
        void unlock(const char *const caller);

        Checksum_t checksum(const char *const data);
};

} // namespace DataStore

#endif // __SDO_HPP__