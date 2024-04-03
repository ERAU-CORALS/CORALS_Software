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

namespace DataStructures {

using MatrixLength_t = unsigned int;

struct MatrixSize_t {
    MatrixLength_t rows;
    MatrixLength_t columns;
};

template<typename T>
class Matrix {
    template<typename U>
    friend Matrix<U> matrix_add(Matrix<U> &matrix1, Matrix<U> &matrix2);
    template<typename U>
    friend Matrix<U> matrix_subtract(Matrix<U> &matrix1, Matrix<U> &matrix2);
    template<typename U>
    friend Matrix<U> matrix_multiply(Matrix<U> &matrix1, Matrix<U> &matrix2);
    template<typename U>
    friend Matrix<U> matrix_hcat(Matrix<U> &left, Matrix<U> &right);
    template<typename U>
    friend Matrix<U> matrix_vcat(Matrix<U> &top, Matrix<U> &bottom);

    public:
    // Constructors
        Matrix(MatrixLength_t rows, MatrixLength_t columns) {
            m_size.rows = rows;
            m_size.columns = columns;
            initialize();
        }
        Matrix(MatrixSize_t size) {
            m_size = size;
            initialize();
        }
        Matrix(Matrix<T> &matrix) {
            m_size = matrix.m_size;
            initialize(false);
            copy(matrix);
        }
        Matrix<T> operator=(Matrix<T> matrix) {
            destroy();
            m_size = matrix.m_size;
            initialize(false);
            copy(matrix);
        }
        Matrix<T>& operator=(Matrix<T> &matrix) {
            destroy();
            m_size = matrix.m_size;
            initialize(false);
            copy(matrix);
        }
    
    // Deconstructor
        virtual ~Matrix() {
            destroy();
        }

    // MultiMatrix Operations
        Matrix<T> operator+(Matrix<T> &matrix) {
            return matrix_add(*this, matrix);
        }
        Matrix<T> operator-(Matrix<T> &matrix) {
            return matrix_subtract(*this, matrix);
        }
        Matrix<T> operator*(Matrix<T> &matrix) {
            return matrix_multiply(*this, matrix);
        }
        Matrix<T> operator~() {
            return transpose();
        }
        Matrix<T> operator<<(Matrix<T> &matrix) {
            return matrix_hcat(*this, matrix);
        }
        Matrix<T> operator||(Matrix<T> &matrix) {
            return matrix_vcat(*this, matrix);
        }

    // MultiMatrix Assignment Operations
        void operator+=(Matrix<T> &matrix) {
            *this = *this + matrix;
        } 
        void operator-=(Matrix<T> &matrix) {
            *this = *this - matrix;
        }
        void operator*=(Matrix<T> &matrix) {
            *this = *this * matrix;
        }
        void operator<<=(Matrix<T> &matrix) {
            *this = *this << matrix;
        }
        void operator|=(Matrix<T> &matrix) {
            *this = *this || matrix;
        }

    // Element Operations
        template<typename U>
        Matrix<T> operator+(const U &value) {
            Matrix<T> result(m_size);
            result += value;
            return result;
        }
        template<typename U>
        Matrix<T> operator-(const U &value) {
            Matrix<T> result(m_size);
            result -= value;
            return result;
        }
        template<typename U>
        Matrix<T> operator*(const U &value) {
            Matrix<T> result(m_size);
            result *= value;
            return result;
        }
        template<typename U>
        Matrix<T> operator/(const U &value) {
            Matrix<T> result(m_size);
            result /= value;
            return result;
        }
        template<typename U>
        Matrix<T> operator^(const U &value) {
            Matrix<T> result(m_size);
            result += value;
            return result;
        }

    // Element Assignment Operations
        template<typename U>
        void operator+=(const U &value) {
            for (MatrixLength_t i = 0; i < m_size.rows * m_size.columns; i++) {
                m_data[i] += value;
            }
        }
        template<typename U>
        void operator-=(const U &value) {
            for (MatrixLength_t i = 0; i < m_size.rows * m_size.columns; i++) {
                m_data[i] -= value;
            }
        }
        template<typename U>
        void operator*=(const U &value) {
            for (MatrixLength_t i = 0; i < m_size.rows * m_size.columns; i++) {
                m_data[i] *= value;
            }
        }
        template<typename U>
        void operator/=(const U &value) {
            for (MatrixLength_t i = 0; i < m_size.rows * m_size.columns; i++) {
                m_data[i] /= value;
            }
        }
        template<typename U>
        void operator^=(const U &value) {
            for (MatrixLength_t i = 0; i < m_size.rows * m_size.columns; i++) {
                m_data[i] = pow(m_data[i], value);
            }
        }

    // Matrix Operations
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

        Matrix<T> transpose() {
            Matrix<T> transposed(this->columns(), this->rows());
            for (MatrixLength_t i = 0; i < this->rows(); i++) {
                for (MatrixLength_t j = 0; j < this->columns(); j++) {
                    transposed.set(j, i, this->get(i, j));
                }
            }
            return transposed;
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

        bool isSkewSymmetric() {
            if (!isSquare()) {
                return false;
            }
            for (MatrixLength_t i = 0; i < this->rows(); i++) {
                for (MatrixLength_t j = 0; j < this->columns(); j++) {
                    if (this->get(i, j) != -this->get(j, i)) {
                        return false;
                    }
                }
            }
        }

        bool isSquare() {
            return this->rows() == this->columns();
        }

        bool isZero() {
            for (MatrixLength_t i = 0; i < m_size.rows * m_size.columns; i++) {
                if (m_data[i] != 0) {
                    return false;
                }
            }
            return true;
        }

        bool isOne() {
            for (MatrixLength_t i = 0; i < m_size.rows * m_size.columns; i++) {
                if (m_data[i] != 1) {
                    return false;
                }
            }
            return true;
        }

        virtual MatrixLength_t length() {
            return m_size.rows > m_size.columns ? m_size.rows : m_size.columns;
        }
        MatrixSize_t size() {
            return m_size;
        }
        MatrixLength_t rows() {
            return m_size.rows;
        }
        MatrixLength_t columns() {
            return m_size.columns;
        }

        void set(MatrixLength_t row, MatrixLength_t column, T value) {
            m_data[row * m_size.columns + column] = value;
        }

        T get(MatrixLength_t row, MatrixLength_t column) {
            return m_data[row * m_size.columns + column];
        }

    private:
        MatrixSize_t m_size;
        T *m_data;

        void initialize(bool zeroize = true) {
            m_data = new T[m_size.rows * m_size.columns];
            if (zeroize) {
                for (MatrixLength_t i = 0; i < m_size.rows * m_size.columns; i++) {
                    m_data[i] = 0;
                }
            }
        }

        void copy(Matrix<T> &matrix) {
            for (MatrixLength_t i = 0; i < m_size.rows * m_size.columns; i++) {
                m_data[i] = matrix.m_data[i];
            }
        }

        void destroy() {
            delete[] m_data;
        }
};

// Matrix Friend Function Definitions
template<typename U> 
Matrix<U> matrix_add(Matrix<U> &matrix1, Matrix<U> &matrix2) {
    assert(matrix1.m_size.rows == matrix2.m_size.rows && matrix1.m_size.columns == matrix2.m_size.columns);
    Matrix<U> result(matrix1.m_size);
    for (MatrixLength_t i = 0; i < matrix1.m_size.rows * matrix1.m_size.columns; i++) {
        result.m_data[i] = matrix1.m_data[i] + matrix2.m_data[i];
    }
    return result;
}

template<typename U>
Matrix<U> matrix_subtract(Matrix<U> &matrix1, Matrix<U> &matrix2) {
    assert(matrix1.m_size.rows == matrix2.m_size.rows && matrix1.m_size.columns == matrix2.m_size.columns);
    Matrix<U> result(matrix1.m_size);
    for (MatrixLength_t i = 0; i < matrix1.m_size.rows * matrix1.m_size.columns; i++) {
        result.m_data[i] = matrix1.m_data[i] - matrix2.m_data[i];
    }
    return result;
}

template<typename U>
Matrix<U> matrix_multiply(Matrix<U> &matrix1, Matrix<U> &matrix2) {
    assert(matrix1.m_size.columns == matrix2.m_size.rows);
    Matrix<U> result(matrix1.m_size.rows, matrix2.m_size.columns);
    for (MatrixLength_t i = 0; i < matrix1.m_size.rows; i++) {
        for (MatrixLength_t j = 0; j < matrix2.m_size.columns; j++) {
            for (MatrixLength_t k = 0; k < matrix1.m_size.columns; k++) {
                result.m_data[i * result.m_size.columns + j] += matrix1.m_data[i * matrix1.m_size.columns + k] * matrix2.m_data[k * matrix2.m_size.columns + j];
            }
        }
    }
    return result;
}

template<typename U>
Matrix<U> matrix_hcat(Matrix<U> &left, Matrix<U> &right) {
    assert(left.m_size.rows == right.m_size.rows);
    Matrix<U> result(left.m_size.rows, left.m_size.columns + right.m_size.columns);
    for (MatrixLength_t i = 0; i < left.m_size.rows * result.m_size.columns; i++) {
        if (i % result.m_size.columns < left.m_size.columns) {
            result.m_data[i] = left.m_data[i];
        } else {
            result.m_data[i] = right.m_data[i - left.m_size.columns];
        }
    }
    return result;
}

template<typename U>
Matrix<U> matrix_vcat(Matrix<U> &top, Matrix<U> &bottom) {
    assert(top.m_size.columns == bottom.m_size.columns);
    Matrix<U> result({top.m_size.rows + bottom.m_size.rows, top.m_size.columns});
    MatrixLength_t i = 0;
    const MatrixLength_t topSize = top.m_size.rows * top.m_size.columns;
    for (; i < topSize; i++) {
        result.m_data[i] = top.m_data[i];
    }
    const MatrixLength_t bottomSize = bottom.m_size.rows * bottom.m_size.columns;
    for (; i < topSize + bottomSize; i++) {
        result.m_data[i + topSize] = bottom.m_data[i];
    }
    return result;
}

} // end namespace DataStructures

#endif // __MATRIX_TPP__