/**
 ********************************************************************************
 * @file    CORALS_DataStore.hpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   CORALS DataStore Implementation
 * @version 1.0
 * @date    2024-03-24
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __CORALS_DATASTORE_HPP__
#define __CORALS_DATASTORE_HPP__

#include "DataStore.tpp"

#include "CORALS_DataStructures.hpp"

namespace CORALS {

enum DataStore_Keys{
// Settings - TBD

// Gains
    GAIN_MATRIX,

// Targets
    TARGET_LIST,

// Attitude
    ATTITUDE_QUATERNION,

// Errors -TBD

// States
    PRIMARY_VOLTAGE,
    SECONDARY_VOLTAGE,
    SINGULARITY_PARAMETER,

// Commands
    GIMBAL_RATES,
};

using CORALS_DataStore = ::DataStore::DataStore<DataStore_Keys>;
extern CORALS_DataStore DataStore;

void DS_Init();

} // end namespace CORALS

#endif // __CORALS_DATASTORE_HPP__