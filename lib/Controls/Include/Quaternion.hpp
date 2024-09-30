/**
 ********************************************************************************
 * @file    Quaternion.tpp
 * @author  Vincent Lam (g.vincentlam@gmail.com)
 * @brief   Quaternion Function Headers
 * @version 1.0
 * @date    2024-08-17
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __QUATERNION_HPP__
#define __QUATERNION_HPP__

#include <math.h>
#include "Matrix.tpp"

namespace DataStructures { // Begin DataStructures

namespace __Quaternion { // Begin Quaternion

class Quaternion {

public:

    T x,y,z,r; // Quaternion components

    Quaternion(T x, T y, T z, T r) : x(x), y(y), z(z), r(r) {} // Constructor w/ params

    ~Quaternion() {} // Destructor

    Quaternion<T> operator+(const Quaternion<T>& other)
    Quaternion<T> operator-(const Quaternion<T>& other)
    Quaternion<T> operator*(const Quaternion<T>& other)
    Matrix<T> q2YPR()
    Quaternion<T> qPropogation(const Quaternion<T>& Beta)
    T magnitude()
    Quaternion<T> normalize()

}

} // End Quaternion

} // End Math

#endif // __QUATERNION_TPP__