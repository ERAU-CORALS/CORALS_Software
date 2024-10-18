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

#include <math.h>
#include "Vector.tpp"

namespace Integrators {

class Integrators {

    Vector<double> eulerIntegrate(const Matrix<Vector>& x_k, const Vector<double>& dx, double dt) {
        return x_k + dt*dx
    }

}

} // End Integrators