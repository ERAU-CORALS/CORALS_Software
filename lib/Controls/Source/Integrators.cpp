/**
 ********************************************************************************
 * @file    Quaternion.tpp
 * @author  Vincent Lam (g.vincentlam@gmail.com)
 * @brief   Integrators Implementation
 * @version 1.0
 * @date    2024-08-21
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __INTEGRATORS_CPP__
#define __INTEGRATORS_CPP__

#include <math.h>
#include "Vector.tpp"

namespace Maths{

namespace Integrators {

class Integrators {

    Vector<double> eulerIntegrate(const Vector<double>& x_k, const Vector<double>& dx, double dt) {
        return x_k + dt*dx
    }

}

} // End Integrators
} // End Maths

#endif // __INTEGRATORS_CPP__