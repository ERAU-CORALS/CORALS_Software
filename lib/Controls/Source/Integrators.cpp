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

    public:

    Integrators(T initialValue, T stepSize) : value(initialValue), dt(stepSize) {} // Constructor

    ~Integrators() {} // Deconstructor

    Matrix<T> Euler(const Matrix<T>& derivative) { // Euler Method for integrating [nx1]
        for (int i = 0; i < value.rows(); ++i) {
            value(i, 0) += derivative(i, 0) * dt;
        }
        return value;
    }

}

} // End Integrators