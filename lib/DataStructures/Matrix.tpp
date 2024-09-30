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

#include <unity.h>

#include "Vector.tpp"
namespace DataStructures {
namespace Matrix {
using DataStructures::Vector::Vector;

template<typename T> class Matrix;

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

namespace Matrix_Operations {

template<typename T> Matrix<T> add(const Matrix<T> &matrix1, const Matrix<T> &matrix2);
template<typename T> Matrix<T> subtract(const Matrix<T> &matrix1, const Matrix<T> &matrix2);
template<typename T> Matrix<T> multiply(const Matrix<T> &matrix1, const Matrix<T> &matrix2);
template<typename T> Vector<T> multiply(const Matrix<T> &matrix, const Vector<T> &vector);
template<typename T> Vector<T> multiply(const Vector<T> &vector, const Matrix<T> &matrix);
template<typename T> Matrix<T> hcat(const Matrix<T> &matrix1, const Matrix<T> &matrix2);
template<typename T> Matrix<T> hcat(const Matrix<T> &matrix, const Vector<T> &vector);
template<typename T> Matrix<T> hcat(const Vector<T> &vector, const Matrix<T> &matrix);
template<typename T> Matrix<T> vcat(const Matrix<T> &matrix1, const Matrix<T> &matrix2);
template<typename T> Matrix<T> vcat(const Matrix<T> &matrix, const Vector<T> &vector);
template<typename T> Matrix<T> vcat(const Vector<T> &vector, const Matrix<T> &matrix);
template<typename T> Matrix<T> adjugate(const Matrix<T> &matrix);
template<typename T> T cofactor(const Matrix<T> &matrix, const MatrixLength_t remove_row, const MatrixLength_t remove_column);
template<typename T> T determinant(const Matrix<T> &size);
template<typename T> Matrix<T> inverse(const Matrix<T> &matrix);
template<typename T> Matrix<T> minor(const Matrix<T> &matrix, const MatrixLength_t remove_row, const MatrixLength_t remove_column);
template<typename T> T trace(const Matrix<T> &matrix);
template<typename T> Matrix<T> transpose(const Matrix<T> &matrix);

} // end namespace Matrix_Operations

namespace Matrix_Property {

template<typename T> bool isDiagonal(const Matrix<T> &matrix);
template<typename T> bool isIdentity(const Matrix<T> &matrix);
template<typename T> bool isSquare(const Matrix<T> &matrix);
template<typename T> bool isSymmetric(const Matrix<T> &matrix);
template<typename T> bool isSkewSymmetric(const Matrix<T> &matrix);
template<typename T> bool isZero(const Matrix<T> &matrix);
template<typename T> bool isOne(const Matrix<T> &matrix);

} // end namespace Matrix_Property

namespace Element_Operations {

template<typename T> Matrix<T> add(const Matrix<T> &matrix, const T &value);
template<typename T> Matrix<T> subtract(const Matrix<T> &matrix, const T &value);
template<typename T> Matrix<T> multiply(const Matrix<T> &matrix, const T &value);
template<typename T> Matrix<T> divide(const Matrix<T> &matrix, const T &value);
template<typename T> Matrix<T> power(const Matrix<T> &matrix, const T &value);
        
} // end namespace Element_Operation

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
            m_size.rows = (MatrixLength_t)vector.length();
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
        inline Matrix<T> operator+(const Matrix<T> &matrix) const {
            return Matrix_Operations::add<T>(*this, matrix);
        }

        /**
         ********************************************************************************
         * @brief   Subtract two matrices
         ********************************************************************************
         * @param[in]   matrix  TYPE: const Matrix<T>&
         * @return      Matrix<T>
         ********************************************************************************
        **/
        inline Matrix<T> operator-(const Matrix<T> &matrix) const {
            return Matrix_Operations::subtract<T>(*this, matrix);
        }

        /**
         ********************************************************************************
         * @brief   Multiply two matrices
         ********************************************************************************
         * @param[in]   matrix  TYPE: const Matrix<T>&
         * @return      Matrix<T>
         ********************************************************************************
        **/
        inline Matrix<T> operator*(const Matrix<T> &matrix) const {
            return Matrix_Operations::multiply<T>(*this, matrix);
        }

        /**
         ********************************************************************************
         * @brief   Multiply a matrix by a vector
         ********************************************************************************
         * @param[in]   vector  TYPE: const Vector<T>&
         * @return      Matrix<T>
         ********************************************************************************
        **/
        inline Vector<T> operator*(const Vector<T> &vector) const {
            return Matrix_Operations::multiply<T>(*this, vector);
        }

        /**
         ********************************************************************************
         * @brief   Transpose a matrix
         ********************************************************************************
         * @return      Matrix<T>
         ********************************************************************************
        **/
        inline Matrix<T> operator~() const {
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
        inline Matrix<T> operator<<(const Matrix<T> &matrix) const {
            return Matrix_Operations::hcat<T>(*this, matrix);
        }

        /**
         ********************************************************************************
         * @brief   Concatenate a matrix and a vector horizontally
         ********************************************************************************
         * @param[in]   vector  TYPE: const Vector<T>&
         * @return      Matrix<T>
         ********************************************************************************
        **/
        inline Matrix<T> operator<<(const Vector<T> &vector) const {
            return Matrix_Operations::hcat<T>(*this, vector);
        }

        /**
         ********************************************************************************
         * @brief   Concatenate two matrices vertically
         ********************************************************************************
         * @param[in]   matrix  TYPE: const Matrix<T>&
         * @return      Matrix<T>
         ********************************************************************************
        **/
        inline Matrix<T> operator|(const Matrix<T> &matrix) const {
            return Matrix_Operations::vcat<T>(*this, matrix);
        }

        /**
         ********************************************************************************
         * @brief   Concatenate a matrix and a vector vertically
         ********************************************************************************
         * @param[in]   vector  TYPE: const Vector<T>&
         * @return      Matrix<T>
         ********************************************************************************
        **/
        inline Matrix<T> operator|(const Vector<T> &vector) const {
            return Matrix_Operations::vcat<T>(*this, vector);
        }

    // MultiMatrix Assignment Operations

        /**
         ********************************************************************************
         * @brief   Add a matrix to this matrix
         ********************************************************************************
         * @param[in]   matrix  TYPE: const Matrix<T>&
         ********************************************************************************
        **/
        inline void operator+=(const Matrix<T> &matrix) {
            *this = Matrix_Operations::add<T>(*this, matrix);
        }

        /**
         ********************************************************************************
         * @brief   Subtract a matrix from this matrix
         ********************************************************************************
         * @param[in]   matrix  TYPE: const Matrix<T>&
         ********************************************************************************
        **/
        inline void operator-=(const Matrix<T> &matrix) {
            *this = Matrix_Operations::subtract<T>(*this, matrix);
        }

        /**
         ********************************************************************************
         * @brief   Multiply this matrix by another matrix
         ********************************************************************************
         * @param[in]   matrix  TYPE: const Matrix<T>&
         ********************************************************************************
        **/
        inline void operator*=(Matrix<T> matrix) {
            *this = Matrix_Operations::multiply<T>(*this, matrix);
        }

        /**
         ********************************************************************************
         * @brief   Multiply this matrix by a vector
         ********************************************************************************
         * @param[in]   vector  TYPE: const Vector<T>&
         ********************************************************************************
        **/
        inline void operator*=(const Vector<T> &vector) {
            *this = Matrix_Operations::multiply<T>(*this, vector);
        }

        /**
         ********************************************************************************
         * @brief   Concatenate a matrix to this matrix horizontally
         ********************************************************************************
         * @param[in]   matrix  TYPE: const Matrix<T>&
         ********************************************************************************
        **/
        inline void operator<<=(const Matrix<T> &matrix) {
            *this = Matrix_Operations::hcat<T>(*this, matrix);
        }

        /**
         ********************************************************************************
         * @brief   Concatenate a matrix and a vector to this matrix horizontally
         ********************************************************************************
         * @param[in]   vector  TYPE: const Vector<T>&
         ********************************************************************************
        **/
        inline void operator<<=(const Vector<T> &vector) {
            *this = Matrix_Operations::hcat<T>(*this, vector);
        }
        
        /**
         ********************************************************************************
         * @brief   Concatenate a matrix to this matrix vertically
         ********************************************************************************
         * @param[in]   matrix  TYPE: const Matrix<T>&
         ********************************************************************************
        **/
        inline void operator|=(Matrix<T> matrix) {
            *this = Matrix_Operations::vcat<T>(*this, matrix);
        }

        /**
         ********************************************************************************
         * @brief   Concatenate a matrix and a vector to this matrix vertically
         ********************************************************************************
         * @param[in]   vector  TYPE: const Vector<T>&
         ********************************************************************************
        **/
        inline void operator|=(const Vector<T> &vector) {
            *this = Matrix_Operations::vcat<T>(*this, vector);
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
        inline Matrix<T> operator+(const T &value) const {
            return Element_Operations::add<T>(*this, value);
        }
        /**
         ********************************************************************************
         * @brief   Subtract a value from each element in the matrix
         ********************************************************************************
         * @param[in]   value   TYPE: const T&
         * @return      Matrix<T>
         ********************************************************************************
        **/
        inline Matrix<T> operator-(const T &value) const {
            return Element_Operations::subtract<T>(*this, value);
        }
        /**
         ********************************************************************************
         * @brief   Multiply each element in the matrix by a value
         ********************************************************************************
         * @param[in]   value   TYPE: const T&
         * @return      Matrix<T>
         ********************************************************************************
        **/
        inline Matrix<T> operator*(const T &value) const {
            return Element_Operations::multiply<T>(*this, value);
        }
        /**
         ********************************************************************************
         * @brief   Divide each element in the matrix by a value
         ********************************************************************************
         * @param[in]   value   TYPE: const T&
         * @return      Matrix<T>
         ********************************************************************************
        **/
        inline Matrix<T> operator/(const T &value) const {
            return Element_Operations::divide<T>(*this, value);
        }
        /**
         ********************************************************************************
         * @brief   Raise each element in the matrix to a power
         ********************************************************************************
         * @param[in]   value   TYPE: const T&
         * @return      Matrix<T>
         ********************************************************************************
        **/
        inline Matrix<T> operator^(const T &value) const {
            return Element_Operations::power<T>(*this, value);
        }

    // Element Assignment Operations
        /**
         ********************************************************************************
         * @brief   Add a value to each element in the matrix
         ********************************************************************************
         * @param[in]   value   TYPE: const T&
         ********************************************************************************
        **/
        inline void operator+=(const T &value) {
            *this = Element_Operations::add<T>(*this, value);
        }

        /**
         ********************************************************************************
         * @brief   Subtract a value from each element in the matrix
         ********************************************************************************
         * @param[in]   value   TYPE: const T&
         ********************************************************************************
        **/
        inline void operator-=(const T &value) {
            *this = Element_Operations::subtract<T>(*this, value);
        }

        /**
         ********************************************************************************
         * @brief   Multiply each element in the matrix by a value
         ********************************************************************************
         * @param[in]   value   TYPE: const T&
         ********************************************************************************
        **/
        inline void operator*=(const T &value) {
            *this = Element_Operations::multiply<T>(*this, value);
        }

        /**
         ********************************************************************************
         * @brief   Divide each element in the matrix by a value
         ********************************************************************************
         * @param[in]   value   TYPE: const T&
         ********************************************************************************
        **/
        inline void operator/=(const T &value) {
            *this = Element_Operations::divide<T>(*this, value);
        }

        /**
         ********************************************************************************
         * @brief   Raise each element in the matrix to a power
         ********************************************************************************
         * @param[in]   value   TYPE: const T&
         ********************************************************************************
        **/
        inline void operator^=(const T &value) {
            *this = Element_Operations::power<T>(*this, value);
        }

    // Matrix Operations
        /**
         ********************************************************************************
         * @brief   Get the adjugate of the matrix
         ********************************************************************************
         * @return  Matrix<T>
         ********************************************************************************
        **/
        inline Matrix<T> adjugate() const {
            return Matrix_Operations::adjugate<T>(*this);
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
        inline T cofactor(int remove_row, int remove_column) const {
            return Matrix_Operations::cofactor<T>(*this, remove_row, remove_column);
        }
        /**
         ********************************************************************************
         * @brief   Get the determinant of the matrix
         ********************************************************************************
         * @return  T
         ********************************************************************************
        **/
        inline T determinant() const {
            return Matrix_Operations::determinant<T>(*this);
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
        inline Matrix<T> minor(int remove_row, int remove_column) const {
            return Matrix_Operations::minor<T>(*this, remove_row, remove_column);
        }

        /**
         ********************************************************************************
         * @brief   Get the inverse of the matrix
         ********************************************************************************
         * @return      Matrix<T>
         ********************************************************************************
        **/
        inline Matrix<T> inverse() const {
            return Matrix_Operations::inverse<T>(*this);
        }

        /**
         ********************************************************************************
         * @brief   Get the trace of the matrix
         ********************************************************************************
         * @return  Matrix<T>
         ********************************************************************************
        **/
        inline T trace() const {
            return Matrix_Operations::trace<T>(*this);
        }

        /**
         ********************************************************************************
         * @brief   Get the transpose of the matrix
         ********************************************************************************
         * @return  Matrix<T>
         ********************************************************************************
        **/
        inline Matrix<T> transpose() const {
            return Matrix_Operations::transpose<T>(*this);
        }

    // Matrix Properties
        /**
         ********************************************************************************
         * @brief   Check if the matrix is diagonal
         ********************************************************************************
         * @return  bool
         ********************************************************************************
        **/
        inline bool isDiagonal() const {
            return Matrix_Property::isDiagonal<T>(*this);
        }

        /**
         ********************************************************************************
         * @brief   Check if the matrix is the identity matrix
         ********************************************************************************
         * @return  bool
         ********************************************************************************
        **/
        inline bool isIdentity() const {
            return Matrix_Property::isIdentity<T>(*this);
        }

        /**
         ********************************************************************************
         * @brief   Check if the matrix is symmetric
         ********************************************************************************
         * @return  bool
         ********************************************************************************
        **/
        inline bool isSymmetric() const {
            return Matrix_Property::isSymmetric<T>(*this);
        }

        /**
         ********************************************************************************
         * @brief   Check if the matrix is skew-symmetric
         ********************************************************************************
         * @return  bool
         ********************************************************************************
        **/
        inline bool isSkewSymmetric() const {
            return Matrix_Property::isSkewSymmetric<T>(*this);
        }

        /**
         ********************************************************************************
         * @brief   Check if the matrix is square
         ********************************************************************************
         * @return  bool
         ********************************************************************************
        **/
        inline bool isSquare() const {
            return Matrix_Property::isSquare<T>(*this);
        }

        /**
         ********************************************************************************
         * @brief   Check if the matrix is zero
         ********************************************************************************
         * @return  bool
         ********************************************************************************
        **/
        inline bool isZero() const {
            return Matrix_Property::isZero<T>(*this);
        }

        /**
         ********************************************************************************
         * @brief   Check if the matrix is one
         ********************************************************************************
         * @return  bool
         ********************************************************************************
        **/
        inline bool isOne() const {
            return Matrix_Property::isOne<T>(*this);
        }
        
        /**
         ********************************************************************************
         * @brief   Get the length of the matrix
         ********************************************************************************
         * @return  MatrixLength_t
         ****************************************************************************** 
        **/
        inline MatrixLength_t length() const {
            return m_size.rows > m_size.columns ? m_size.rows : m_size.columns;
        }

        /**
         ********************************************************************************
         * @brief   Get the size of the matrix
         ********************************************************************************
         * @return  MatrixSize_t
         ******************************************************************************
        **/
        inline MatrixSize_t size() const {
            return m_size;
        }

        /**
         ********************************************************************************
         * @brief   Get the number of rows in the matrix
         ********************************************************************************
         * @return  MatrixLength_t
         ******************************************************************************
        **/
        inline MatrixLength_t rows() const {
            return m_size.rows;
        }

        /**
         ********************************************************************************
         * @brief   Get the number of columns in the matrix
         ********************************************************************************
         * @return  MatrixLength_t
         ******************************************************************************
        **/
        inline MatrixLength_t columns() const {
            return m_size.columns;
        }

    // Element Access
        /**
         ********************************************************************************
         * @brief   Get a value from the matrix
         ********************************************************************************
         * @param[in]   row     TYPE: MatrixLength_t
         * @param[in]   column  TYPE: MatrixLength_t
         * @return      T
         ********************************************************************************
        **/
        inline T get(MatrixLength_t row, MatrixLength_t column) const {
            assert(row < m_size.rows && column < m_size.columns);
            return m_data[row * m_size.columns + column];
        }
        
        /**
         ********************************************************************************
         * @brief   Set a value in the matrix
         ********************************************************************************
         * @param[in]   row     TYPE: MatrixLength_t
         * @param[in]   column  TYPE: MatrixLength_t
         * @param[in]   value   TYPE: T
         ********************************************************************************
        **/
        inline void set(MatrixLength_t row, MatrixLength_t column, T value) {
            assert(row < m_size.rows && column < m_size.columns);
            m_data[row * m_size.columns + column] = value;
        }

        
    // Matrix Friend Functions
        template<typename U> friend Matrix<U> Matrix_Operations::add(const Matrix<U> &matrix1, const Matrix<U> &matrix2);
        template<typename U> friend Matrix<U> Matrix_Operations::subtract(const Matrix<U> &matrix1, const Matrix<U> &matrix2);
        template<typename U> friend Matrix<U> Matrix_Operations::multiply(const Matrix<U> &matrix1, const Matrix<U> &matrix2);
        template<typename U> friend Vector<U> Matrix_Operations::multiply(const Matrix<U> &matrix, const Vector<U> &vector);
        template<typename U> friend Vector<U> Matrix_Operations::multiply(const Vector<U> &vector, const Matrix<U> &matrix);
        template<typename U> friend Matrix<U> Matrix_Operations::hcat(const Matrix<U> &matrix1, const Matrix<U> &matrix2);
        template<typename U> friend Matrix<U> Matrix_Operations::hcat(const Matrix<U> &matrix, const Vector<U> &vector);
        template<typename U> friend Matrix<U> Matrix_Operations::hcat(const Vector<U> &vector, const Matrix<U> &matrix);
        template<typename U> friend Matrix<U> Matrix_Operations::vcat(const Matrix<U> &matrix1, const Matrix<U> &matrix2);
        template<typename U> friend Matrix<U> Matrix_Operations::vcat(const Matrix<U> &matrix, const Vector<U> &vector);
        template<typename U> friend Matrix<U> Matrix_Operations::vcat(const Vector<U> &vector, const Matrix<U> &matrix);
        template<typename U> friend Matrix<U> Matrix_Operations::adjugate(const Matrix<U> &matrix);
        template<typename U> friend T Matrix_Operations::cofactor(const Matrix<U> &matrix, const MatrixLength_t remove_row, const MatrixLength_t remove_column);
        template<typename U> friend T Matrix_Operations::determinant(const Matrix<T> &matrix);
        template<typename U> friend Matrix<U> Matrix_Operations::inverse(const Matrix<U> &matrix);
        template<typename U> friend Matrix<U> Matrix_Operations::minor(const Matrix<U> &matrix, const MatrixLength_t remove_row, const MatrixLength_t remove_column);
        template<typename U> friend U Matrix_Operations::trace(const Matrix<U> &matrix);
        template<typename U> friend Matrix<U> Matrix_Operations::transpose(const Matrix<U> &matrix);

        template<typename U> friend bool Matrix_Property::isDiagonal(const Matrix<U> &matrix);
        template<typename U> friend bool Matrix_Property::isIdentity(const Matrix<U> &matrix);
        template<typename U> friend bool Matrix_Property::isSquare(const Matrix<U> &matrix);
        template<typename U> friend bool Matrix_Property::isSymmetric(const Matrix<U> &matrix);
        template<typename U> friend bool Matrix_Property::isSkewSymmetric(const Matrix<U> &matrix);
        template<typename U> friend bool Matrix_Property::isZero(const Matrix<U> &matrix);
        template<typename U> friend bool Matrix_Property::isOne(const Matrix<U> &matrix);

        template<typename U> friend Matrix<U> Element_Operations::add(const Matrix<U> &matrix, const T &value);
        template<typename U> friend Matrix<U> Element_Operations::subtract(const Matrix<U> &matrix, const T &value);
        template<typename U> friend Matrix<U> Element_Operations::multiply(const Matrix<U> &matrix, const T &value);
        template<typename U> friend Matrix<U> Element_Operations::divide(const Matrix<U> &matrix, const T &value);
        template<typename U> friend Matrix<U> Element_Operations::power(const Matrix<U> &matrix, const T &value);

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

namespace Matrix_Operations {

/**
 ********************************************************************************
 * @brief   Add two matrices
 ********************************************************************************
 * @tparam      T
 * @param[in]   matrix1 TYPE: const Matrix<T>&
 * @param[in]   matrix2 TYPE: const Matrix<T>&
 * @return      Matrix<T>
 ********************************************************************************
**/
template<typename T>
Matrix<T> add(const Matrix<T> &matrix1, const Matrix<T> &matrix2) {
    // Matrices must be the same size
    assert(matrix1.rows() == matrix2.rows() && matrix1.columns() == matrix2.columns());

    Matrix<T> result(matrix1.size());
    for (MatrixLength_t i = 0; i < matrix1.rows() * matrix1.columns(); i++) {
        result.m_data[i] = matrix1.m_data[i] + matrix2.m_data[i];
    }

    return result;   
}

/**
 ********************************************************************************
 * @brief   Subtract two matrices
 ********************************************************************************
 * @tparam      T
 * @param[in]   matrix1 TYPE: const Matrix<T>&
 * @param[in]   matrix2 TYPE: const Matrix<T>&
 * @return      Matrix<T>
 ********************************************************************************
**/
template<typename T>
Matrix<T> subtract(const Matrix<T> &matrix1, const Matrix<T> &matrix2) {
    // Matrices must be the same size
    assert(matrix1.rows() == matrix2.rows() && matrix1.columns() == matrix2.columns());

    Matrix<T> result(matrix1.size());
    for (MatrixLength_t i = 0; i < matrix1.rows() * matrix1.columns(); i++) {
        result.m_data[i] = matrix1.m_data[i] - matrix2.m_data[i];
    }

    return result;
}

/**
 ********************************************************************************
 * @brief   Multiply two matrices
 ********************************************************************************
 * @tparam      T
 * @param[in]   matrix1 TYPE: const Matrix<T>&
 * @param[in]   matrix2 TYPE: const Matrix<T>&
 * @return      Matrix<T>
 ********************************************************************************
**/
template<typename T>
Matrix<T> multiply(const Matrix<T> &matrix1, const Matrix<T> &matrix2) {
    // Columns of left matrix must equal rows of right matrix
    assert(matrix1.columns() == matrix2.rows());

    Matrix<T> result(matrix1.rows(), matrix2.columns());
    for (MatrixLength_t i = 0; i < matrix1.rows(); i++) {
        for (MatrixLength_t j = 0; j < matrix2.columns(); j++) {
            for (MatrixLength_t k = 0; k < matrix1.columns(); k++) {
                result.set(i, j, result.get(i, j) + matrix1.get(i, k) * matrix2.get(k, j));
            }
        }
    }

    return result;
}

/**
 ********************************************************************************
 * @brief   Multiply a matrix by a vector
 ********************************************************************************
 * @tparam      T
 * @param[in]   matrix  TYPE: const Matrix<T>&
 * @param[in]   vector  TYPE: const Vector<T>&
 * @return      Vector<T>
 ********************************************************************************
**/
template<typename T>
Vector<T> multiply(const Matrix<T> &matrix, const Vector<T> &vector) {
    // Columns of matrix must equal length of vector
    assert(matrix.columns() == vector.length());

    Vector<T> result(matrix.rows());
    for (MatrixLength_t i = 0; i < result.length(); i++) {
        T sum = 0;
        for (MatrixLength_t j = 0; j < matrix.columns(); j++) {
            sum += matrix.get(i, j) * vector.get(j);
        }
        result.set(i, sum);
    }

    return result;
}

/**
 ********************************************************************************
 * @brief   Multiply a vector by a matrix
 ********************************************************************************
 * @tparam      T
 * @param[in]   vector  TYPE: const Vector<T>&
 * @param[in]   matrix  TYPE: const Matrix<T>&
 * @return      Vector<T>
 ********************************************************************************
**/
template<typename T>
Vector<T> multiply(const Vector<T> &vector, const Matrix<T> &matrix) {
    // Length of vector must equal rows of matrix
    assert(vector.length() == matrix.rows());

    Vector<T> result(matrix.columns());
    for (MatrixLength_t i = 0; i < result.length(); i++) {
        T sum = 0;
        for (MatrixLength_t j = 0; j < matrix.rows(); j++) {
            sum += vector.get(j) * matrix.get(j, i);
        }
        result.set(i, sum);
    }

    return result;
}

/**
 ********************************************************************************
 * @brief   Concatenate two matrices horizontally
 ********************************************************************************
 * @tparam      T
 * @param[in]   matrix1 TYPE: const Matrix<T>&
 * @param[in]   matrix2 TYPE: const Matrix<T>&
 * @return      Matrix<T>
 ********************************************************************************
**/
template<typename T>
Matrix<T> hcat(const Matrix<T> &matrix1, const Matrix<T> &matrix2) {
    // Matrices must have the same number of rows
    assert(matrix1.rows() == matrix2.rows());

    Matrix<T> result(matrix1.rows(), matrix1.columns() + matrix2.columns());
    for (MatrixLength_t i = 0; i < result.rows(); i++) {
        for (MatrixLength_t j = 0; j < result.columns(); j++) {
            if (j < matrix1.columns()) {
                result.set(i, j, matrix1.get(i, j));
            } else {
                result.set(i, j, matrix2.get(i, j - matrix1.columns()));
            }
        }
    }

    return result;
}

/**
 ********************************************************************************
 * @brief   Concatenate a matrix and a vector horizontally
 ********************************************************************************
 * @tparam      T
 * @param[in]   matrix  TYPE: const Matrix<T>&
 * @param[in]   vector  TYPE: const Vector<T>&
 * @return      Matrix<T>
 ********************************************************************************
**/
template<typename T>
Matrix<T> hcat(const Matrix<T> &matrix, const Vector<T> &vector) {
    // Matrix must have the same number of rows as the vector has elements
    assert(matrix.rows() == vector.length());

    Matrix<T> result(matrix.rows(), matrix.columns() + 1);
    for (MatrixLength_t i = 0; i < result.rows(); i++) {
        for (MatrixLength_t j = 0; j < result.columns(); j++) {
            if (j < matrix.columns()) {
                result.set(i, j, matrix.get(i, j));
            } else {
                result.set(i, j, vector.get(i));
            }
        }
    }

    return result;
}

/**
 ********************************************************************************
 * @brief   Concatenate a vector and a matrix horizontally
 ********************************************************************************
 * @tparam      T
 * @param[in]   vector  TYPE: const Vector<T>&
 * @param[in]   matrix  TYPE: const Matrix<T>&
 * @return      Matrix<T>
 ********************************************************************************
**/
template<typename T>
Matrix<T> hcat(const Vector<T> &vector, const Matrix<T> &matrix) {
    // Matrix must have the same number of rows as the vector has elements
    assert(matrix.rows() == vector.length());

    Matrix<T> result(matrix.rows(), matrix.columns() + 1);
    for (MatrixLength_t i = 0; i < result.rows(); i++) {
        for (MatrixLength_t j = 0; j < result.columns(); j++) {
            if (j < 1) {
                result.set(i, j, vector.get(i));
            } else {
                result.set(i, j, matrix.get(i, j - 1));
            }
        }
    }

    return result;
}

/**
 ********************************************************************************
 * @brief   Concatenate two matrices vertically
 ********************************************************************************
 * @tparam      T
 * @param[in]   matrix1 TYPE: const Matrix<T>&
 * @param[in]   matrix2 TYPE: const Matrix<T>&
 * @return      Matrix<T>
 ********************************************************************************
**/
template<typename T>
Matrix<T> vcat(const Matrix<T> &matrix1, const Matrix<T> &matrix2) {
    // Matrices must have the same number of columns
    assert(matrix1.columns() == matrix2.columns());

    Matrix<T> result(matrix1.rows() + matrix2.rows(), matrix1.columns());
    for (MatrixLength_t i = 0; i < result.rows(); i++) {
        for (MatrixLength_t j = 0; j < result.columns(); j++) {
            if (i < matrix1.rows()) {
                result.set(i, j, matrix1.get(i, j));
            } else {
                result.set(i, j, matrix2.get(i - matrix1.rows(), j));
            }
        }
    }

    return result;
}

/**
 ********************************************************************************
 * @brief   Concatenate a matrix and a vector vertically
 ********************************************************************************
 * @tparam      T
 * @param[in]   matrix  TYPE: const Matrix<T>&
 * @param[in]   vector  TYPE: const Vector<T>&
 * @return      Matrix<T>
 ********************************************************************************
**/
template<typename T>
Matrix<T> vcat(const Matrix<T> &matrix, const Vector<T> &vector) {
    // Matrix must have the same number of columns as the vector has elements
    assert(matrix.columns() == vector.length());

    Matrix<T> result(matrix.rows() + 1, matrix.columns());
    for (MatrixLength_t i = 0; i < result.rows(); i++) {
        for (MatrixLength_t j = 0; j < result.columns(); j++) {
            if (i < matrix.rows()) {
                result.set(i, j, matrix.get(i, j));
            } else {
                result.set(i, j, vector.get(j));
            }
        }
    }

    return result;
}

/**
 ********************************************************************************
 * @brief   Concatenate a vector and a matrix vertically
 ********************************************************************************
 * @tparam      T
 * @param[in]   vector  TYPE: const Vector<T>&
 * @param[in]   matrix  TYPE: const Matrix<T>&
 * @return      Matrix<T>
 ********************************************************************************
**/
template<typename T>
Matrix<T> vcat(const Vector<T> &vector, const Matrix<T> &matrix) {
    // Matrix must have the same number of columns as the vector has elements
    assert(matrix.columns() == vector.length());

    Matrix<T> result(matrix.rows() + 1, matrix.columns());
    for (MatrixLength_t i = 0; i < result.rows(); i++) {
        for (MatrixLength_t j = 0; j < result.columns(); j++) {
            if (i < 1) {
                result.set(i, j, vector.get(j));
            } else {
                result.set(i, j, matrix.get(i - 1, j));
            }
        }
    }

    return result;
}

/**
 ********************************************************************************
 * @brief   Get the adjugate of a matrix
 ********************************************************************************
 * @tparam      T
 * @param[in]   matrix  TYPE: const Matrix<T>&
 * @return      Matrix<T>
 ********************************************************************************
**/
template<typename T>
Matrix<T> adjugate(const Matrix<T> &matrix) {
    // Matrix must be square
    assert(matrix.isSquare());

    Matrix<T> C(matrix.size()); // Cofactor Matrix
    for (MatrixLength_t i = 0; i < matrix.rows(); i++) {
        for (MatrixLength_t j = 0; j < matrix.columns(); j++) {
            C.set(i, j, matrix.cofactor(i, j));
        }
    }

    return C.transpose(); // Adjugate is the transpose of the cofactor matrix
}

/**
 ********************************************************************************
 * @brief   Get the cofactor using the determinant of a matrix minor
 ********************************************************************************
 * @tparam      T
 * @param[in]   matrix          TYPE: const Matrix<T>&
 * @param[in]   remove_row      TYPE: MatrixLength_t
 * @param[in]   remove_column   TYPE: MatrixLength_t
 * @return      T
 ********************************************************************************
**/
template<typename T>
T cofactor(const Matrix<T> &matrix, const MatrixLength_t remove_row, const MatrixLength_t remove_column) {
    // Matrix must be square
    assert(matrix.isSquare());

    Matrix<T> M = minor(matrix, remove_row, remove_column); // Minor Matrix
    T cofactor_mag = M.determinant();
    T cofactor_sign = (remove_row + remove_column) % 2 == 0 ? 1 : -1;
    return cofactor_sign * cofactor_mag;
}

/**
 ********************************************************************************
 * @brief   Get the determinant of a matrix
 ********************************************************************************
 * @tparam      T
 * @param[in]   matrix  TYPE: const Matrix<T>&
 * @return      T
 ********************************************************************************
**/
template<typename T>
T determinant(const Matrix<T> &matrix) {
    // Matrix must be square
    assert(matrix.isSquare());

    // Base Cases
    if (matrix.rows() == 1) {
        return matrix.get(0, 0);
    }
    if (matrix.rows() == 2) {
        return matrix.get(0, 0) * matrix.get(1, 1) - matrix.get(0, 1) * matrix.get(1, 0);
    }

    // Higher Order Cases
    Matrix<T> adj(adjugate(matrix));
    Matrix<T> determinantIdentity = matrix * adj;
    return determinantIdentity.get(0, 0);
}

/**
 ********************************************************************************
 * @brief   Get the inverse of a matrix
 ********************************************************************************
 * @tparam      T
 * @param[in]   matrix  TYPE: const Matrix<T>&
 * @return      Matrix<T>
 ********************************************************************************
**/
template<typename T>
Matrix<T> inverse(const Matrix<T> &matrix) {
    // Matrix must be square
    assert(matrix.isSquare());

    // Matrix must be invertible
    T det = determinant(matrix);
    assert(det != 0);

    Matrix<T> adj = adjugate(matrix);
    return adj / det;
}

/**
 ********************************************************************************
 * @brief   Get the minor of a matrix
 ********************************************************************************
 * @tparam      T
 * @param[in]   matrix          TYPE: const Matrix<T>&
 * @param[in]   remove_row      TYPE: MatrixLength_t
 * @param[in]   remove_column   TYPE: MatrixLength_t
 * @return      Matrix<T>
 ********************************************************************************
**/
template<typename T>
Matrix<T> minor(const Matrix<T> &matrix, const MatrixLength_t remove_row, const MatrixLength_t remove_column) {
    Matrix<T> M(matrix.rows() - 1, matrix.columns() - 1);
    for (MatrixLength_t i = 0; i < matrix.rows(); i++) {
        for (MatrixLength_t j = 0; j < matrix.columns(); j++) {
            if (i != remove_row && j != remove_column) {
                M.set(i - (i > remove_row), j - (j > remove_column), matrix.get(i, j));
            }
        }
    }

    return M;
}

/**
 ********************************************************************************
 * @brief   Get the trace of a matrix
 ********************************************************************************
 * @tparam      T
 * @param[in]   matrix  TYPE: const Matrix<T>&
 * @return      T
 ********************************************************************************
**/
template<typename T>
T trace(const Matrix<T> &matrix) {
    // Matrix must be square
    assert(matrix.isSquare());

    T trace = 0;
    for (MatrixLength_t i = 0; i < matrix.rows(); i++) {
        trace += matrix.get(i, i);
    }
    return trace;
}

/**
 ********************************************************************************
 * @brief   Get the transpose of a matrix
 ********************************************************************************
 * @tparam      T
 * @param[in]   matrix  TYPE: const Matrix<T>&
 * @return      Matrix<T>
 ********************************************************************************
**/
template<typename T>
Matrix<T> transpose(const Matrix<T> &matrix) {
    Matrix<T> transposed(matrix.columns(), matrix.rows());
    for (MatrixLength_t i = 0; i < matrix.rows(); i++) {
        for (MatrixLength_t j = 0; j < matrix.columns(); j++) {
            transposed.set(j, i, matrix.get(i, j));
        }
    }
    return transposed;
}

} // end namespace Matrix_Operations

namespace Matrix_Property {

/**
 ********************************************************************************
 * @brief   Check if a matrix is diagonal
 ********************************************************************************
 * @tparam      T
 * @param[in]   matrix  TYPE: const Matrix<T>&
 * @return      bool
 ********************************************************************************
**/
template<typename T>
bool isDiagonal(const Matrix<T> &matrix) {
    if (!matrix.isSquare()) {
        return false;
    }
    for (MatrixLength_t i = 0; i < matrix.rows(); i++) {
        for (MatrixLength_t j = 0; j < matrix.columns(); j++) {
            if (i != j && matrix.get(i, j) != 0) {
                return false;
            }
        }
    }
    return true;
}

/**
 ********************************************************************************
 * @brief   Check if a matrix is the identity matrix
 ********************************************************************************
 * @tparam      T
 * @param[in]   matrix  TYPE: const Matrix<T>&
 * @return      bool
 ********************************************************************************
**/

template<typename T>
bool isIdentity(const Matrix<T> &matrix) {
    if (!matrix.isSquare()) {
        return false;
    }
    if (!isDiagonal(matrix)) {
        return false;
    }
    for (MatrixLength_t i = 0; i < matrix.rows(); i++) {
        if (matrix.get(i, i) != 1) {
            return false;
        }
    }
    return true;
}

/**
 ********************************************************************************
 * @brief   Check if a matrix is square
 ********************************************************************************
 * @tparam      T
 * @param[in]   matrix  TYPE: const Matrix<T>&
 * @return      bool
 ********************************************************************************
**/
template<typename T>
bool isSquare(const Matrix<T> &matrix) {
    return matrix.rows() == matrix.columns();
}

/**
 ********************************************************************************
 * @brief   Check if a matrix is symmetric
 ********************************************************************************
 * @tparam      T
 * @param[in]   matrix  TYPE: const Matrix<T>&
 * @return      bool
 ********************************************************************************
**/

template<typename T>
bool isSymmetric(const Matrix<T> &matrix) {
    if (!matrix.isSquare()) {
        return false;
    }
    for (MatrixLength_t i = 0; i < matrix.rows(); i++) {
        for (MatrixLength_t j = i; j < matrix.columns(); j++) {
            if (i == j) continue;
            if (matrix.get(i, j) != matrix.get(j, i)) {
                return false;
            }
        }
    }
    return true;
}

/**
 ********************************************************************************
 * @brief   Check if a matrix is skew-symmetric
 ********************************************************************************
 * @tparam      T
 * @param[in]   matrix  TYPE: const Matrix<T>&
 * @return      bool
 ********************************************************************************
**/
template<typename T>
bool isSkewSymmetric(const Matrix<T> &matrix) {
    if (!matrix.isSquare()) {
        return false;
    }
    for (MatrixLength_t i = 0; i < matrix.rows(); i++) {
        for (MatrixLength_t j = i; j < matrix.columns(); j++) {
            if (i == j) continue;
            if (matrix.get(i, j) != -matrix.get(j, i)) {
                return false;
            }
        }
    }
    return true;
}

/**
 ********************************************************************************
 * @brief   Check if a matrix is zero
 ********************************************************************************
 * @tparam      T
 * @param[in]   matrix  TYPE: const Matrix<T>&
 * @return      bool
 ********************************************************************************
**/
template<typename T>
bool isZero(const Matrix<T> &matrix) {
    for (MatrixLength_t i = 0; i < matrix.rows(); i++) {
        for (MatrixLength_t j = 0; j < matrix.columns(); j++) {
            if (matrix.get(i, j) != 0) {
                return false;
            }
        }
    }
    return true;
}

/**
 ********************************************************************************
 * @brief   Check if a matrix is one
 ********************************************************************************
 * @tparam      T
 * @param[in]   matrix  TYPE: const Matrix<T>&
 * @return      bool
 ********************************************************************************
**/
template<typename T>
bool isOne(const Matrix<T> &matrix) {
    for (MatrixLength_t i = 0; i < matrix.rows(); i++) {
        for (MatrixLength_t j = 0; j < matrix.columns(); j++) {
            if (matrix.get(i, j) != 1) {
                return false;
            }
        }
    }
    return true;
}

} // end namespace Matrix_Property

namespace Element_Operations {

/**
 ********************************************************************************
 * @brief   Add a value to a matrix
 ********************************************************************************
 * @tparam      T
 * @param[in]   matrix  TYPE: const Matrix<T>&
 * @param[in]   value   TYPE: const T&
 * @return      Matrix<T>
 ********************************************************************************
**/
template<typename T>
Matrix<T> add(const Matrix<T> &matrix, const T &value) {
    Matrix<T> result(matrix);
    for (MatrixLength_t i = 0; i < matrix.rows(); i++) {
        for (MatrixLength_t j = 0; j < matrix.columns(); j++) {
            result.set(i, j, result.get(i, j) + value);
        }
    }
    return result;
}

/**
 ********************************************************************************
 * @brief   Subtract a value from a matrix
 ********************************************************************************
 * @tparam      T
 * @param[in]   matrix  TYPE: const Matrix<T>&
 * @param[in]   value   TYPE: const T&
 * @return      Matrix<T>
 ********************************************************************************
**/
template<typename T>
Matrix<T> subtract(const Matrix<T> &matrix, const T &value) {
    Matrix<T> result(matrix);
    for (MatrixLength_t i = 0; i < matrix.rows(); i++) {
        for (MatrixLength_t j = 0; j < matrix.columns(); j++) {
            result.set(i, j, result.get(i, j) - value);
        }
    }
    return result;
}

/**
 ********************************************************************************
 * @brief   Multiply a matrix by a value
 ********************************************************************************
 * @tparam      T
 * @param[in]   matrix  TYPE: const Matrix<T>&
 * @param[in]   value   TYPE: const T&
 * @return      Matrix<T>
 ********************************************************************************
**/
template<typename T>
Matrix<T> multiply(const Matrix<T> &matrix, const T &value) {
    Matrix<T> result(matrix);
    for (MatrixLength_t i = 0; i < matrix.rows(); i++) {
        for (MatrixLength_t j = 0; j < matrix.columns(); j++) {
            result.set(i, j, result.get(i, j) * value);
        }
    }
    return result;
}

/**
 ********************************************************************************
 * @brief   Divide a matrix by a value
 ********************************************************************************
 * @tparam      T
 * @param[in]   matrix  TYPE: const Matrix<T>&
 * @param[in]   value   TYPE: const T&
 * @return      Matrix<T>
 ********************************************************************************
**/
template<typename T>
Matrix<T> divide(const Matrix<T> &matrix, const T &value) {
    Matrix<T> result(matrix);
    for (MatrixLength_t i = 0; i < matrix.rows(); i++) {
        for (MatrixLength_t j = 0; j < matrix.columns(); j++) {
            result.set(i, j, result.get(i, j) / value);
        }
    }
    return result;
}

/**
 ********************************************************************************
 * @brief   Raise a matrix to a power
 ********************************************************************************
 * @tparam      T
 * @param[in]   matrix  TYPE: const Matrix<T>&
 * @param[in]   value   TYPE: const T&
 * @return      Matrix<T>
 ********************************************************************************
**/
template<typename T>
Matrix<T> power(const Matrix<T> &matrix, const T &value) {
    Matrix<T> result(matrix);
    for (MatrixLength_t i = 0; i < matrix.rows(); i++) {
        for (MatrixLength_t j = 0; j < matrix.columns(); j++) {
            result.set(i, j, pow(result.get(i, j), value));
        }
    }
    return result;
}

} // end namespace Element_Operation

/**
 ********************************************************************************
 * @brief   Multiply a vector by a matrix
 ********************************************************************************
 * @tparam      T
 * @param[in]   vector  TYPE: const Vector<T>&
 * @param[in]   matrix  TYPE: const Matrix<T>&
 * @return      Vector<T>
 * @note    This function is defined outside of the Matrix class
 ********************************************************************************
**/
template<typename T>
inline Vector<T> operator*(const Vector<T> &vector, const Matrix<T> &matrix) {
    return Matrix_Operations::multiply(vector, matrix);
}

} // end namespace Matrix
} // end namespace DataStructure

#endif // __MATRIX_TPP__