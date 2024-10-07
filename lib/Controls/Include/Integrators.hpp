/**
 ********************************************************************************
 * @file    Quaternion.tpp
 * @author  Vincent Lam (g.vincentlam@gmail.com)
 * @brief   Integrators Headers
 * @version 1.0
 * @date    2024-08-21
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __INTEGRATORS_HPP__
#define __INTEGRATORS_HPP__

#include <math.h>
#include "Matrix.tpp"

namespace Integrators {

template<typename T>
class Integrators {

    public:

    Integrators(T initialValue, T stepSize) : value(initialValue), dt(stepSize) {} // Constructor

    ~Integrators() {} // Deconstructor

    Matrix<T> Euler(const Matrix<T>& derivative) 

}

} // End Integrators