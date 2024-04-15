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
#include <math.h>

#include "Vector.tpp"
namespace DataStructures {

using MatrixLength_t = unsigned int;

/**
 ********************************************************************************
 * @brief   Matrix Size Struct
 ********************************************************************************
**/
struct MatrixSize_t {
    MatrixLength_t rows;
    MatrixLength_t columns;
};

/**
 ********************************************************************************
 * @brief   Matrix Class
 * @tparam  T
 ******************************************************************************** 
**/
template<typename T>
class Matrix {
    public:
    // Constructors

        /**
         ********************************************************************************
         * @brief   Construct a new Matrix
         ********************************************************************************
         * @param[in]   rows    TYPE: const MatrixLength_t
         * @param[in]   columns TYPE: const MatrixLength_t
         ********************************************************************************
        **/
        Matrix(const MatrixLength_t rows, const MatrixLength_t columns) {
            m_size.rows = rows;
            m_size.columns = columns;
            initialize();
        }

        /**
         ********************************************************************************
         * @brief   Construct a new Matrix
         ********************************************************************************
         * @param[in]   size    TYPE: const MatrixSize_t
         ********************************************************************************
        **/
        Matrix(const MatrixSize_t size) {
            m_size = size;
            initialize();
        }

        /**
         ********************************************************************************
         * @brief   Copy a constant Matrix object
         ********************************************************************************
         * @param[in]   matrix  TYPE: Matrix<T>
         ********************************************************************************
        **/
        Matrix(const Matrix<T> &matrix) {
            m_size = matrix.m_size;
            initialize(false);
            copy(matrix);
        }

        /**
         ********************************************************************************
         * @brief   Copy Vector to a new Matrix
         ********************************************************************************
         * @param[in]   vector    TYPE: const Vector<T>&
         ********************************************************************************
        **/
        Matrix(const Vector<T> &vector) {
            m_size.rows = vector.length();
            m_size.columns = 1;
            initialize(false);
            for (MatrixLength_t i = 0; i < m_size.rows; i++) {
                m_data[i] = vector.get(i);
            }
        }

        /**
         ********************************************************************************
         * @brief   Assign a Matrix object
         ********************************************************************************
         * @param[in]   matrix  TYPE: const Matrix<T>&
         * @return      Matrix<T>& 
         ********************************************************************************
        **/
        Matrix<T>& operator=(const Matrix<T> &matrix) {
            if (this == &matrix) return *this;
            destroy();
            m_size = matrix.m_size;
            initialize(false);
            copy(matrix);
            return *this;
        }
    
    // Deconstructor
        /**
         ********************************************************************************
         * @brief   Deconstruct the Matrix
         ********************************************************************************
        **/
        virtual ~Matrix() {
            destroy();
        }

    // MultiMatrix Operations
        /**
         ********************************************************************************
         * @brief   Add two matrices
         ********************************************************************************
         * @param[in]   matrix  TYPE: const Matrix<T>&
         * @return      Matrix<T>
         ********************************************************************************
        **/
        Matrix<T> operator+(const Matrix<T> &matrix) {
            // Matrices must be the same size
            assert(m_size.rows == matrix.m_size.rows && m_size.columns == matrix.m_size.columns);

            Matrix<T> result(m_size);
            for (MatrixLength_t i = 0; i < m_size.rows * m_size.columns; i++) {
                result.m_data[i] = m_data[i] + matrix.m_data[i];
            }

            return result;
        }

        /**
         ********************************************************************************
         * @brief   Subtract two matrices
         ********************************************************************************
         * @param[in]   matrix  TYPE: const Matrix<T>&
         * @return      Matrix<T>
         ********************************************************************************
        **/
        Matrix<T> operator-(const Matrix<T> &matrix) {
            // Matrices must be the same size
            assert(m_size.rows == matrix.m_size.rows && m_size.columns == matrix.m_size.columns);

            Matrix<T> result(m_size);
            for (MatrixLength_t i = 0; i < m_size.rows * m_size.columns; i++) {
                result.m_data[i] = m_data[i] - matrix.m_data[i];
            }

            return result;
        }

        /**
         ********************************************************************************
         * @brief   Multiply two matrices
         ********************************************************************************
         * @param[in]   matrix  TYPE: const Matrix<T>&
         * @return      Matrix<T>
         ********************************************************************************
        **/
        Matrix<T> operator*(const Matrix<T> &matrix) {
            // Columns of left matrix must equal rows of right matrix
            assert(m_size.columns == matrix.m_size.rows);

            Matrix<T> result(m_size.rows, matrix.m_size.columns);
            for (MatrixLength_t i = 0; i < m_size.rows; i++) {
                for (MatrixLength_t k = 0; k < m_size.columns; k++) {
                    for (MatrixLength_t j = 0; j < matrix.m_size.columns; j++) {
                        result.m_data[i * result.m_size.columns + j] += m_data[i * m_size.columns + k] * matrix.m_data[k * matrix.m_size.columns + j];
                    }
                }
            }

            return result;
        }

        /**
         ********************************************************************************
         * @brief   Multiply a matrix by a vector
         ********************************************************************************
         * @param[in]   vector  TYPE: const Vector<T>&
         * @return      Matrix<T>
         ********************************************************************************
        **/
        Vector<T> operator*(const Vector<T> &vector) {
            // Columns of matrix must equal length of vector
            assert(m_size.columns == vector.length());

            Vector<T> result(m_size.rows);
            for (MatrixLength_t i = 0; i < m_size.rows; i++) {
                T sum = 0;
                for (MatrixLength_t j = 0; j < m_size.columns; j++) {
                    sum += m_data[i * m_size.columns + j] * vector.get(j);
                }
                result.set(i, sum);
            }

            return result;
        }

        /**
         ********************************************************************************
         * @brief   Multiply a vector by a matrix
         ********************************************************************************
         * @param[in]   vector  TYPE: const Vector<T>&
         * @param[in]   matrix  TYPE: const Matrix<T>&
         * @return      Matrix<T>
         ********************************************************************************
        **/
        friend Vector<T> operator*(const Vector<T> &vector, const Matrix<T> &matrix) {
            // Length of vector must equal columns of matrix
            assert(vector.length() == matrix.m_size.rows);

            Vector<T> result(matrix.m_size.columns);
            for (MatrixLength_t i = 0; i < matrix.m_size.columns; i++) {
                T sum = 0;
                for (MatrixLength_t j = 0; j < matrix.m_size.rows; j++) {
                    sum += vector.get(j) * matrix.get(j, i);
                }
                result.set(i, sum);
            }

            return result;
        }

        /**
         ********************************************************************************
         * @brief   Transpose a matrix
         ********************************************************************************
         * @return      Matrix<T>
         ********************************************************************************
        **/
        Matrix<T> operator~() {
            return transpose();
        }

        /**
         ********************************************************************************
         * @brief   Concatenate two matrices horizontally
         ********************************************************************************
         * @param[in]   matrix  TYPE: const Matrix<T>&
         * @return      Matrix<T>
         ********************************************************************************
        **/
        Matrix<T> operator<<(const Matrix<T> &matrix) {
            // Matrices must have the same number of rows
            assert(m_size.rows == matrix.m_size.rows);

            Matrix<T> result(m_size.rows, m_size.columns + matrix.m_size.columns);
            for (MatrixLength_t i = 0; i < m_size.rows * result.m_size.columns; i++) {
                if (i % result.m_size.columns < m_size.columns) {
                    result.m_data[i] = m_data[i];
                } else {
                    result.m_data[i] = matrix.m_data[i - m_size.columns];
                }
            }

            return result;
        }

        /**
         ********************************************************************************
         * @brief   Concatenate a matrix and a vector horizontally
         ********************************************************************************
         * @param[in]   vector  TYPE: const Vector<T>&
         * @return      Matrix<T>
         ********************************************************************************
        **/
        Matrix<T> operator<<(const Vector<T> &vector) {
            // Matrix must have the same number of rows as the vector has elements
            assert(m_size.rows == vector.length());

            Matrix<T> result(m_size.rows, m_size.columns + 1);
            for (MatrixLength_t i = 0; i < m_size.rows * result.m_size.columns; i++) {
                if (i % result.m_size.columns < m_size.columns) {
                    result.m_data[i] = m_data[i];
                } else {
                    result.m_data[i] = vector.get(i - m_size.columns);
                }
            }

            return result;
        }

        /**
         ********************************************************************************
         * @brief   Concatenate two matrices vertically
         ********************************************************************************
         * @param[in]   matrix  TYPE: const Matrix<T>&
         * @return      Matrix<T>
         ********************************************************************************
        **/
        Matrix<T> operator|(const Matrix<T> &matrix) {
            // Matrices must have the same number of columns
            assert(m_size.columns == matrix.m_size.columns);

            Matrix<T> result(m_size.rows + matrix.m_size.rows, m_size.columns);
            MatrixLength_t i = 0;
            const MatrixLength_t size = m_size.rows * m_size.columns;
            for (; i < size; i++) {
                result.m_data[i] = m_data[i];
            }
            const MatrixLength_t matrixSize = matrix.m_size.rows * matrix.m_size.columns;
            for (; i < size + matrixSize; i++) {
                result.m_data[i + size] = matrix.m_data[i];
            }

            return result;
        }

        /**
         ********************************************************************************
         * @brief   Concatenate a matrix and a vector vertically
         ********************************************************************************
         * @param[in]   vector  TYPE: const Vector<T>&
         * @return      Matrix<T>
         ********************************************************************************
        **/
        Matrix<T> operator|(const Vector<T> &vector) {
            // Matrix must have the same number of columns as the vector has elements
            assert(m_size.columns == vector.length());

            Matrix<T> result(m_size.rows + 1, m_size.columns);
            MatrixLength_t i = 0;
            const MatrixLength_t size = m_size.rows * m_size.columns;
            for (; i < size; i++) {
                result.m_data[i] = m_data[i];
            }
            const VectorLength_t vectorSize = vector.length();
            for (; i < size + vectorSize; i++) {
                result.m_data[i + size] = vector.get(i);
            }
        }

    // MultiMatrix Assignment Operations

        /**
         ********************************************************************************
         * @brief   Add a matrix to this matrix
         ********************************************************************************
         * @param[in]   matrix  TYPE: const Matrix<T>&
         ********************************************************************************
        **/
        void operator+=(const Matrix<T> &matrix) {
            // Matrices must be the same size
            assert(m_size.rows == matrix.m_size.rows && m_size.columns == matrix.m_size.columns);

            for (MatrixLength_t i = 0; i < m_size.rows * m_size.columns; i++) {
                m_data[i] += matrix.m_data[i];
            }
        }

        /**
         ********************************************************************************
         * @brief   Subtract a matrix from this matrix
         ********************************************************************************
         * @param[in]   matrix  TYPE: const Matrix<T>&
         ********************************************************************************
        **/
        void operator-=(const Matrix<T> &matrix) {
            // Matrices must be the same size
            assert(m_size.rows == matrix.m_size.rows && m_size.columns == matrix.m_size.columns);

            for (MatrixLength_t i = 0; i < m_size.rows * m_size.columns; i++) {
                m_data[i] -= matrix.m_data[i];
            }
        }

        /**
         ********************************************************************************
         * @brief   Multiply this matrix by another matrix
         ********************************************************************************
         * @param[in]   matrix  TYPE: const Matrix<T>&
         ********************************************************************************
        **/
        void operator*=(Matrix<T> matrix) {
            Matrix<T> result = *this * matrix;
            *this = result;
        }

        /**
         ********************************************************************************
         * @brief   Concatenate a matrix to this matrix horizontally
         ********************************************************************************
         * @param[in]   matrix  TYPE: const Matrix<T>&
         ********************************************************************************
        **/
        void operator<<=(const Matrix<T> &matrix) {
            // Matrices must have the same number of rows
            assert(m_size.rows == matrix.m_size.rows);

            *this = *this << matrix;
        }

        /**
         ********************************************************************************
         * @brief   Concatenate a matrix and a vector to this matrix horizontally
         ********************************************************************************
         * @param[in]   vector  TYPE: const Vector<T>&
         ********************************************************************************
        **/
        void operator<<=(const Vector<T> &vector) {
            // Matrix must have the same number of rows as the vector has elements
            assert(m_size.rows == vector.length());

            *this = *this << vector;
        }
        
        /**
         ********************************************************************************
         * @brief   Concatenate a matrix to this matrix vertically
         ********************************************************************************
         * @param[in]   matrix  TYPE: const Matrix<T>&
         ********************************************************************************
        **/
        void operator|=(Matrix<T> matrix) {
            // Matrices must have the same number of columns
            assert(m_size.columns == matrix.m_size.columns);

            *this = *this | matrix;
        }

        /**
         ********************************************************************************
         * @brief   Concatenate a matrix and a vector to this matrix vertically
         ********************************************************************************
         * @param[in]   vector  TYPE: const Vector<T>&
         ********************************************************************************
        **/
        void operator|=(const Vector<T> &vector) {
            // Matrix must have the same number of columns as the vector has elements
            assert(m_size.columns == vector.length());

            *this = *this | vector;
        }

    // Element Operations
        /**
         ********************************************************************************
         * @brief   Add a value to each element in the matrix
         ********************************************************************************
         * @param[in]   value   TYPE: const T&
         * @return      Matrix<T>
         ********************************************************************************
        **/
        Matrix<T> operator+(const T &value) {
            Matrix<T> result(*this);
            result += value;
            return result;
        }
        /**
         ********************************************************************************
         * @brief   Subtract a value from each element in the matrix
         ********************************************************************************
         * @param[in]   value   TYPE: const T&
         * @return      Matrix<T>
         ********************************************************************************
        **/
        Matrix<T> operator-(const T &value) {
            Matrix<T> result(*this);
            result -= value;
            return result;
        }
        /**
         ********************************************************************************
         * @brief   Multiply each element in the matrix by a value
         ********************************************************************************
         * @param[in]   value   TYPE: const T&
         * @return      Matrix<T>
         ********************************************************************************
        **/
        Matrix<T> operator*(const T &value) {
            Matrix<T> result(*this);
            result *= value;
            return result;
        }
        /**
         ********************************************************************************
         * @brief   Divide each element in the matrix by a value
         ********************************************************************************
         * @param[in]   value   TYPE: const T&
         * @return      Matrix<T>
         ********************************************************************************
        **/
        Matrix<T> operator/(const T &value) {
            Matrix<T> result(*this);
            result /= value;
            return result;
        }
        /**
         ********************************************************************************
         * @brief   Raise each element in the matrix to a power
         ********************************************************************************
         * @param[in]   value   TYPE: const T&
         * @return      Matrix<T>
         ********************************************************************************
        **/
        Matrix<T> operator^(const T &value) {
            Matrix<T> result(*this);
            result ^= value;
            return result;
        }

    // Element Assignment Operations
        void operator+=(const T &value) {
            for (MatrixLength_t i = 0; i < m_size.rows * m_size.columns; i++) {
                m_data[i] += value;
            }
        }
        void operator-=(const T &value) {
            for (MatrixLength_t i = 0; i < m_size.rows * m_size.columns; i++) {
                m_data[i] -= value;
            }
        }
        void operator*=(const T &value) {
            for (MatrixLength_t i = 0; i < m_size.rows * m_size.columns; i++) {
                m_data[i] *= value;
            }
        }
        void operator/=(const T &value) {
            for (MatrixLength_t i = 0; i < m_size.rows * m_size.columns; i++) {
                m_data[i] /= value;
            }
        }
        void operator^=(const T &value) {
            for (MatrixLength_t i = 0; i < m_size.rows * m_size.columns; i++) {
                m_data[i] = pow(m_data[i], value);
            }
        }

    // Matrix Operations
        /**
         ********************************************************************************
         * @brief   Get the determinant of the matrix
         ********************************************************************************
         * @return  T
         ********************************************************************************
        **/
        T determinant() {
            // Matrix must be square
            assert(isSquare());

            // Base Cases
            if (rows() == 1) {
                return get(0, 0);
            }
            if (rows() == 2) {
                return get(0, 0) * get(1, 1) - get(0, 1) * get(1, 0);
            }

            // Higher Order Cases
            Matrix<T> adj(adjugate());
            Matrix<T> determinantIdentity = *this * adj;
            return determinantIdentity.get(0, 0);
        }

        /**
         ********************************************************************************
         * @brief   Get the adjugate of the matrix
         ********************************************************************************
         * @return  Matrix<T>
         ********************************************************************************
        **/
        Matrix<T> adjugate() {
            // Matrix must be square
            assert(isSquare());


            Matrix<T> C(m_size); // Cofactor Matrix
            for (MatrixLength_t i = 0; i < rows(); i++) {
                for (MatrixLength_t j = 0; j < columns(); j++) {
                    C.set(i, j, cofactor(i, j));
                }
            }

            return C.transpose(); // Adjugate is the transpose of the cofactor matrix
        }

        /**
         ********************************************************************************
         * @brief   Get the cofactor of a matrix minor
         ********************************************************************************
         * @param[in]   remove_row      TYPE: int
         * @param[in]   remove_column   TYPE: int
         * @return      T
         ********************************************************************************
        **/
        T cofactor(int remove_row, int remove_column) {
            // Matrix must be square
            assert(isSquare());

            Matrix<T> M(minor(remove_row, remove_column)); // Minor Matrix
            T cofactor_mag = M.determinant();
            T cofactor_sign = (remove_row + remove_column) % 2 == 0 ? 1 : -1;
            return cofactor_sign * cofactor_mag;
        }

        /**
         ********************************************************************************
         * @brief   Get the minor of a matrix
         ********************************************************************************
         * @param[in]   remove_row      TYPE: int
         * @param[in]   remove_column   TYPE: int
         * @return      Matrix<T>
         ********************************************************************************
        **/
        Matrix<T> minor(int remove_row, int remove_column) {
            // Matrix must be square
            assert(isSquare());

            Matrix<T> M(rows() - 1, columns() - 1);
            for (MatrixLength_t i = 0; i < rows(); i++) {
                for (MatrixLength_t j = 0; j < columns(); j++) {
                    if (i != remove_row && j != remove_column) {
                        M.set(i + (i > remove_row), j + (j > remove_column), get(i, j));
                    }
                }
            }

            return M;
        }

        /**
         ********************************************************************************
         * @brief   Get the inverse of the matrix
         ********************************************************************************
         * @return      Matrix<T>
         ********************************************************************************
        **/
        Matrix<T> inverse() {
            // Matrix must be square
            assert(isSquare());

            // Matrix must be invertible
            T det = determinant();
            assert(det != 0);

            Matrix<T> inv = adjugate() / det;
        }

        /**
         ********************************************************************************
         * @brief   Get the trace of the matrix
         ********************************************************************************
         * @return  Matrix<T>
         ********************************************************************************
        **/
        T trace() {
            // Matrix must be square
            assert(isSquare());

            T trace = 0;
            for (MatrixLength_t i = 0; i < rows(); i++) {
                trace += get(i, i);
            }
            return trace;
        }

        /**
         ********************************************************************************
         * @brief   Get the transpose of the matrix
         ********************************************************************************
         * @return  Matrix<T>
         ********************************************************************************
        **/
        Matrix<T> transpose() {
            Matrix<T> transposed(this->columns(), this->rows());
            for (MatrixLength_t i = 0; i < this->rows(); i++) {
                for (MatrixLength_t j = 0; j < this->columns(); j++) {
                    transposed.set(j, i, this->get(i, j));
                }
            }
            return transposed;
        }

    // Matrix Properties
        /**
         ********************************************************************************
         * @brief   Check if the matrix is the identity matrix
         ********************************************************************************
         * @return  bool
         ********************************************************************************
        **/
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

        /**
         ********************************************************************************
         * @brief   Check if the matrix is diagonal
         ********************************************************************************
         * @return  bool
         ********************************************************************************
        **/
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

        /**
         ********************************************************************************
         * @brief   Check if the matrix is symmetric
         ********************************************************************************
         * @return  bool
         ********************************************************************************
        **/
        bool isSymmetric() {
            if (!isSquare()) {
                return false;
            }
            for (MatrixLength_t i = 1; i < this->rows(); i++) {
                for (MatrixLength_t j = i; j < this->columns(); j++) {
                    if (this->get(i, j) != this->get(j, i)) {
                        return false;
                    }
                }
            }
            return true;
        }

        /**
         ********************************************************************************
         * @brief   Check if the matrix is skew-symmetric
         ********************************************************************************
         * @return  bool
         ********************************************************************************
        **/
        bool isSkewSymmetric() {
            if (!isSquare()) {
                return false;
            }
            for (MatrixLength_t i = 1; i < this->rows(); i++) {
                for (MatrixLength_t j = i; j < this->columns(); j++) {
                    if (this->get(i, j) != -this->get(j, i)) {
                        return false;
                    }
                }
            }
        }

        /**
         ********************************************************************************
         * @brief   Check if the matrix is square
         ********************************************************************************
         * @return  bool
         ********************************************************************************
        **/
        bool isSquare() {
            return this->rows() == this->columns();
        }

        /**
         ********************************************************************************
         * @brief   Check if the matrix is zero
         ********************************************************************************
         * @return  bool
         ********************************************************************************
        **/
        bool isZero() {
            for (MatrixLength_t i = 0; i < m_size.rows * m_size.columns; i++) {
                if (m_data[i] != 0) {
                    return false;
                }
            }
            return true;
        }

        /**
         ********************************************************************************
         * @brief   Check if the matrix is one
         ********************************************************************************
         * @return  bool
         ********************************************************************************
        **/
        bool isOne() {
            for (MatrixLength_t i = 0; i < m_size.rows * m_size.columns; i++) {
                if (m_data[i] != 1) {
                    return false;
                }
            }
            return true;
        }
        
        /**
         ********************************************************************************
         * @brief   Get the length of the matrix
         ********************************************************************************
         * @return  MatrixLength_t
         ****************************************************************************** 
        **/
        MatrixLength_t length() {
            return m_size.rows > m_size.columns ? m_size.rows : m_size.columns;
        }

        /**
         ********************************************************************************
         * @brief   Get the size of the matrix
         ********************************************************************************
         * @return  MatrixSize_t
         ******************************************************************************
        **/
        MatrixSize_t size() {
            return m_size;
        }

        /**
         ********************************************************************************
         * @brief   Get the number of rows in the matrix
         ********************************************************************************
         * @return  MatrixLength_t
         ******************************************************************************
        **/
        MatrixLength_t rows() {
            return m_size.rows;
        }

        /**
         ********************************************************************************
         * @brief   Get the number of columns in the matrix
         ********************************************************************************
         * @return  MatrixLength_t
         ******************************************************************************
        **/
        MatrixLength_t columns() {
            return m_size.columns;
        }

    // Element Access
        /**
         ********************************************************************************
         * @brief   Set a value in the matrix
         ********************************************************************************
         * @param[in]   row     TYPE: MatrixLength_t
         * @param[in]   column  TYPE: MatrixLength_t
         * @param[in]   value   TYPE: T
         ********************************************************************************
        **/
        void set(MatrixLength_t row, MatrixLength_t column, T value) {
            m_data[row * m_size.columns + column] = value;
        }

        /**
         ********************************************************************************
         * @brief   Get a value from the matrix
         ********************************************************************************
         * @param[in]   row     TYPE: MatrixLength_t
         * @param[in]   column  TYPE: MatrixLength_t
         * @return      T
         ********************************************************************************
        **/
        T get(MatrixLength_t row, MatrixLength_t column) {
            return m_data[row * m_size.columns + column];
        }

    private:
        MatrixSize_t m_size;
        T *m_data;

    // Helper Functions
        /**
         ********************************************************************************
         * @brief   Initialize the matrix
         ********************************************************************************
         * @param[in]   zeroize TYPE: bool
         ********************************************************************************
         * @note    If zeroize is true, the matrix will be initialized to zero
         ********************************************************************************
        **/
        void initialize(bool zeroize = true) {
            m_data = new T[m_size.rows * m_size.columns];
            if (zeroize) {
                for (MatrixLength_t i = 0; i < m_size.rows * m_size.columns; i++) {
                    m_data[i] = 0;
                }
            }
        }

        /**
         ********************************************************************************
         * @brief   Copy a matrix
         ********************************************************************************
         * @param[in]   matrix  TYPE: const Matrix<T>&
         ********************************************************************************
        **/
        void copy(const Matrix<T> &matrix) {
            // Matrices must be the same size
            assert(m_size.rows == matrix.m_size.rows && m_size.columns == matrix.m_size.columns);

            for (MatrixLength_t i = 0; i < m_size.rows * m_size.columns; i++) {
                m_data[i] = matrix.m_data[i];
            }
        }

        /**
         ********************************************************************************
         * @brief   Destroy the matrix
         ********************************************************************************
        **/
        void destroy() {
            delete[] m_data;
        }
};

} // end namespace DataStructures

#endif // __MATRIX_TPP__