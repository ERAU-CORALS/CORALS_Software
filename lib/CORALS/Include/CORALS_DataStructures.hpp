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
    Quaternion otimes(const Quaternion &q) const {
        Quaternion result;

        result.set(0, get(0)*q.get(0) - get(1)*q.get(1) - get(2)*q.get(2) - get(3)*q.get(3));
        result.set(1, get(0)*q.get(1) + get(1)*q.get(0) + get(2)*q.get(3) - get(3)*q.get(2));
        result.set(2, get(0)*q.get(2) - get(1)*q.get(3) + get(2)*q.get(0) + get(3)*q.get(1));
        result.set(3, get(0)*q.get(3) + get(1)*q.get(2) - get(2)*q.get(1) + get(3)*q.get(0));

        return result;
    }
    Quaternion otimes2(const Quaternion &q) const {
        return q.otimes(*this);
    }
};

using TargetList = ::DataStructures::List::List<Quaternion*>;

} // namespace CORALS

#endif // __CORALS_DATASTRUCTURES_HPP__