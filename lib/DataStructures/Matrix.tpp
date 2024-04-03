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

#include <assert.h>

#include "Tensor.tpp"

namespace DataStructures {

using MatrixLength_t = TensorLength_t;
using MatrixSize_t = TensorSize_t;

template<typename T>
class Matrix : public Tensor<T> {

    public:
        Matrix(MatrixLength_t rows, MatrixLength_t columns) : Tensor<T>(rows, columns) {}
        Matrix(MatrixSize_t size) : Tensor<T>(size) {}
        Matrix(Matrix<T> &matrix) : Tensor<T>(matrix) {}
        ~Matrix() {}

        void operator=(const Matrix<T> &matrix) {
            Tensor<T>::operator=(matrix);
        }

        T determinant() {
            assert(isSquare());
            if (this->rows() == 1) {
                return this->get(0, 0);
            }
            if (this->rows() == 2) {
                return this->get(0, 0) * this->get(1, 1) - this->get(0, 1) * this->get(1, 0);
            }
            Matrix<T> adj(adjoint());
            Matrix<T> determinantIdentity = *this * adj;
            return determinantIdentity.get(0, 0);
        }
        Matrix<T> adjoint() {
            assert(isSquare());
            Matrix<T> adj(this->rows(), this->columns());
            for (MatrixLength_t i = 0; i < this->rows(); i++) {
                for (MatrixLength_t j = 0; j < this->columns(); j++) {
                    adj.set(i, j, cofactor(i, j));
                }
            }
            return adj.transpose();
        }
        Matrix<T> inverse() {
            assert(isSquare());
            T det = determinant();
            assert(det != 0);
            Matrix<T> inv = adjoint() / det;
        }
        T cofactor(int remove_row, int remove_column) {
            Matrix<T> cofactor_matrix(this->rows() - 1, this->columns() - 1);
            for (MatrixLength_t i = 0; i < this->rows(); i++) {
                for (MatrixLength_t j = 0; j < this->columns(); j++) {
                    if (i != remove_row && j != remove_column) {
                        cofactor_matrix.set(i - (i > remove_row), j - (j > remove_column), this->get(i, j));
                    }
                }
            }
            T leader = 1 - ((remove_row + remove_column) % 2) * 2;
            return leader * cofactor_matrix.determinant();
        }
        T trace() {
            assert(isSquare());
            T trace = 0;
            for (MatrixLength_t i = 0; i < this->rows(); i++) {
                trace += this->get(i, i);
            }
            return trace;
        }

        bool isIdentity() {
            if (!isSquare()) {
                return false;
            }
            if (!isDiagonal()) {
                return false;
            }
            for (MatrixLength_t i = 0; i < this->rows(); i++) {
                if (this->get(i, i) != 1) {
                    return false;
                }
            }
            return true;
        }
        bool isDiagonal() {
            if (!isSquare()) {
                return false;
            }
            for (MatrixLength_t i = 0; i < this->rows(); i++) {
                for (MatrixLength_t j = 0; j < this->columns(); j++) {
                    if (i != j && this->get(i, j) != 0) {
                        return false;
                    }
                }
            }
            return true;
        }
        bool isSymmetric() {
            if (!isSquare()) {
                return false;
            }
            for (MatrixLength_t i = 0; i < this->rows(); i++) {
                for (MatrixLength_t j = 0; j < this->columns(); j++) {
                    if (this->get(i, j) != this->get(j, i)) {
                        return false;
                    }
                }
            }
            return true;
        }
        bool isSquare() {
            return this->rows() == this->columns();
        }
};

} // end namespace DataStructures

#endif // __MATRIX_TPP__