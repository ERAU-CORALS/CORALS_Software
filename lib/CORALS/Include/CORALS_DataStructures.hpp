/**
 ********************************************************************************
 * @file    CORALS_DataStructures.hpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   CORALS DataStructures Implementation
 * @version 1.0
 * @date    2024-03-24
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __CORALS_DATASTRUCTURES_HPP__
#define __CORALS_DATASTRUCTURES_HPP__

#include "List.tpp"
#include "Matrix.tpp"
#include "Vector.tpp"

#include "CORALS_Configuration.hpp"

namespace CORALS {

using DMatrix = DataStructures::Matrix::Matrix<double>;
using DVector = DataStructures::Vector::Vector<double>;

class GainMatrix : public ::DataStructures::Matrix::Matrix<double> { 
    public: GainMatrix() : Matrix(3, 3) {}
};
class Quaternion : public ::DataStructures::Vector::Vector<double> { 
    public: Quaternion() : Vector(4) {} 
};
class GimbalRates : public ::DataStructures::Vector::Vector<double> {
    public: GimbalRates() : Vector(CORALS_CMG_COUNT) {}
};

using TargetList = ::DataStructures::List::List<Quaternion*>;

} // namespace CORALS

#endif // __CORALS_DATASTRUCTURES_HPP__