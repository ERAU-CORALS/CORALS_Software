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
#include "Matrix.tpp"

namespace Integrators {

class Integrators {

    Matrix<double> eulerIntegrate(const Matrix<double>& x_k, const Matrix<double>& dx, double dt) {
        return x_k + dt*dx
    }

}

} // End Integrators