/**
 ********************************************************************************
 * @file    Matrix.tpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Template implementation for Matrix class
 * @version 1.0
 * @date    2024-04-02
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __MATRIX_TPP__
#define __MATRIX_TPP__

#include "Tensor.tpp"

namespace DataStructures {

using MatrixSize_t = unsigned int;

template<typename T>
class Matrix : protected Tensor<T> {

    public:
        Matrix(int rows, int columns) : Tensor<T>(rows, columns) {
            // Matrix Constructor Here
        }
        ~Matrix() {
            // Matrix Destructor Here
        }
};

} // end namespace DataStructures

#endif // __MATRIX_TPP__