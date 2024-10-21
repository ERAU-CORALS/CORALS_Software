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

    double x,y,z,r; // Quaternion components

    Quaternion(double x, double y, double z, double r) : x(x), y(y), z(z), r(r) {} // Constructor w/ params

    ~Quaternion() {} // Destructor

    Quaternion<double> oTimes(const Quaternion<double>& other);
    //Matrix<T> q2YPR()
    //Quaternion<T> qPropogation(const Quaternion<T>& Beta)

}

} // End Quaternion

} // End Math

#endif // __QUATERNION_TPP__