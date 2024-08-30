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

#include "DataStore.hpp"
#include "List.tpp"
#include "Matrix.tpp"
#include "Vector.tpp"


namespace CORALS {

// TODO: REDEFINE THESE ELSEWHERE
using GainMatrix = DataStructures::Matrix::Matrix<double>;
using Quaternion = DataStructures::Vector::Vector<double>;
using TargetList = DataStructures::List::List<Quaternion*>;

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
};

class DataStore : public ::DataStore::DataStore<DataStore_Keys> {
    public:
        DataStore();
        ~DataStore();
};

} // end namespace CORALS

#endif // __CORALS_DATASTORE_HPP__