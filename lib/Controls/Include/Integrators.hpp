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
#include "Vector.tpp"

namespace Integrators {

class Integrators {

    public:

    Integrators(double initialValue, double stepSize) : value(initialValue), dt(stepSize) {} // Constructor

    ~Integrators() {} // Deconstructor

    Vector<double> Vector(const Vector<double>& derivative) 

}

} // End Integrators