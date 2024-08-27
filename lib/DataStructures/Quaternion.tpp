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

#ifndef __QUATERNION_TPP__
#define __QUATERNION_TPP__

#include <math.h>
#include "Matrix.tpp"

namespace DataStructures { // Begin DataStructures

namespace __Quaternion { // Begin Quaternion

template<typename T> 
class Quaternion {

public:

    T x,y,z,r; // Quaternion components

    Quaternion(T x, T y, T z, T r) : x(x), y(y), z(z), r(r) {} // Constructor w/ params

    ~Quaternion() {} // Destructor

    // Member Functions
    Quaternion<T> operator+(const Quaternion<T>& other) {
        return Quaternion<T>(x + other.x, y + other.y, z + other.z, r + other.r);
    }

    Quaternion<T> operator-(const Quaternion<T>& other) {
        return Quaternion<T>(x - other.x, y - other.y, z - other.z, r - other.r);
    }

    Quaternion<T> operator*(const Quaternion<T>& other) { // O times
        return Quaternion<T>( 
            -r * other.x - z * other.y + y * other.z + x * other.r,
            z * other.x - r * other.y - x * other.z + y * other.r,
            -y * other.x + x * other.y - r * other.z + z * other.r,
            -x * other.x - y * other.y - z * other.z + r * other.r
            );
    }

    Matrix<T> q2YPR() {
        Matrix<T> YPR(3,1);
        YPR(0,0) = atan2(2 * (x * y + z * r), x * x - y * y - z * z + r * r); // Yaw
        YPR(1,0) = asin(-2 * (x * z - y * r)); // Pitch
        YPR(2,0) = atan2(2 * (y * z + x * r), -x * x - y * y + z * z + r * r); // Roll
        return YPR;
    }

    Quaternion<T> qPropogation(const Quaternion<T>& Beta) {
        T BetaMag = Beta.magnitude();
        Quaternion<T> normBeta = Beta.normalize();
        Quaternion<T> qDot(qDot(0,0) = sin(0.5 * BetaMag) * normBeta.x,
        qDot(1,0) = sin(0.5 * BetaMag) * normBeta.y,
        qDot(2,0) = sin(0.5 * BetaMag) * normBeta.z,
        qDot(3,0) = cos(0.5 * BetaMag));
        
        return qDot * *this
    }

    T magnitude() {
        return sqrt(x*x + y*y + z*z + r*r);
    }

    Quaternion<T> normalize() {
        T mag  = magnitude(q);
        return Quaternion<T>(x / mag, y / mag, z / mag, r / mag);
    }

}

} // End Quaternion

} // End Math

#endif // __QUATERNION_TPP__