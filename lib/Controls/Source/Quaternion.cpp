/**
 ********************************************************************************
 * @file    Quaternion.tpp
 * @author  Vincent Lam (g.vincentlam@gmail.com)
 * @brief   Quaternion Template Implementation
 * @version 1.0
 * @date    2024-08-17
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __QUATERNION_CPP__
#define __QUATERNION_CPP__

#include <math.h>
#include "Vector.tpp"

namespace Maths { // Begin DataStructures

namespace __Quaternion { // Begin Quaternion

class Quaternion {

public:

    double x,y,z,r; // Quaternion components

    Quaternion(double x, double y, double z, double r) : x(x), y(y), z(z), r(r) {} // Constructor w/ params

    ~Quaternion() {} // Destructor

    Quaternion<double> oTimes(const Quaternion<double>& other) { // O times
        return Quaternion<double>( 
            -r * other.x - z * other.y + y * other.z + x * other.r,
            z * other.x - r * other.y - x * other.z + y * other.r,
            -y * other.x + x * other.y - r * other.z + z * other.r,
            -x * other.x - y * other.y - z * other.z + r * other.r
            );
    } // Can relocate this?

/*     Vector<double> q2YPR() {
        Matrix<T> YPR(3,1);
        YPR(0,0) = atan2(2 * (x * y + z * r), x * x - y * y - z * z + r * r); // Yaw
        YPR(1,0) = asin(-2 * (x * z - y * r)); // Pitch
        YPR(2,0) = atan2(2 * (y * z + x * r), -x * x - y * y + z * z + r * r); // Roll
        return YPR;
    } */ // Covered by DARTS

}

} // End Quaternion

} // End Math

#endif // __QUATERNION_TPP__