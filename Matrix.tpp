/**
 ********************************************************************************
 * @file    Matrix.tpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Template implementation for Matrix class
 * @version 1.0 -> 1.1
 * @date    2024-04-02
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/ 

#ifndef __MATRIX_TPP__
#define __MATRIX_TPP__

#include <assert.h>

namespace DataStructures {

using MatrixLength_t = unsigned int; // Define alias

struct MatrixSize_t { // Matrix size struct
    MatrixLength_t rows;
    MatrixLength_t columns;
};

// Define matrix class //
template<typename T>
class Matrix { 
    template<typename U> // Create template for friend functions
    friend Matrix<U> matrix_add(Matrix<U> matrix1, Matrix<U> matrix2); // Assign friend for given function
    template<typename U>
    friend Matrix<U> matrix_subtract(Matrix<U> matrix1, Matrix<U> matrix2);
    template<typename U>
    friend Matrix<U> matrix_multiply(Matrix<U> matrix1, Matrix<U> matrix2);
    template<typename U>
    friend Matrix<U> matrix_hcat(Matrix<U> &left, Matrix<U> &right);
    template<typename U>
    friend Matrix<U> matrix_vcat(Matrix<U> &top, Matrix<U> &bottom);

    public:
    // Constructors
        Matrix(MatrixLength_t rows, MatrixLength_t columns) { // Initialize matrix with specified rows and columns
            m_size.rows = rows; 
            m_size.columns = columns;
            initialize(); 
        }
        Matrix(MatrixSize_t size) { // Initialize matrix with specified size (row,column)
            m_size = size;
            initialize();
        }
        Matrix(Matrix<T> matrix) { // Copy constructor that initializes and copies data from another matrix
            m_size = matrix.m_size; // NOTE: matrix is an object of type MatrixSize_t, i.e. m_size contains (rows, columns)
            initialize(false);
            copy(matrix);
        }
        Matrix(Matrix<T> &matrix) { // Copy constructor that initializes and copies data from another matrix passed by reference
            m_size = matrix.m_size;
            initialize(false); 
            copy(matrix);
        }
        Matrix<T> operator=(Matrix<T> matrix) { // Assign operator to copy matrix data
            destroy();
            m_size = matrix.m_size;
            initialize(false);
            copy(matrix);
        }
        Matrix<T>& operator=(Matrix<T> &matrix) { // Assign operator to copy matrix data passed by reference
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
        Matrix<T> operator+(const Matrix<T> matrix) { // Define operator (+) for matrix addition
            return matrix_add(*this, matrix);
        } 
        Matrix<T> operator-(Matrix<T> matrix) { // Define operator (-) for matrix subtraction
            return matrix_subtract(*this, matrix);
        }
        Matrix<T> operator*(Matrix<T> matrix) { // Define operator (*) for matrix multiplication
            return matrix_multiply(*this, matrix);
        }
        Matrix<T> operator~() { // Define operator (~) for matrix transpose
            return transpose();
        }
        Matrix<T> operator<<(Matrix<T> matrix) { // Define operator (<<) for matrix horizontal concatenation
            return matrix_hcat(*this, matrix);
        }
        Matrix<T> operator||(Matrix<T> matrix) { // Define operator (||) for matrix vertical concatenation
            return matrix_vcat(*this, matrix);
        }

    // MultiMatrix Assignment Operations
        void operator+=(Matrix<T> matrix) { // Matrix addition operator
            *this = *this + matrix;
        } 
        void operator-=(Matrix<T> matrix) { // Subtraction operator
            *this = *this - matrix;
        }
        void operator*=(Matrix<T> matrix) { // Multiplication operator
            *this = *this * matrix;
        }
        void operator<<=(Matrix<T> matrix) { // Horizontal concatenation operator
            *this = *this << matrix;
        }
        void operator|=(Matrix<T> matrix) { // Vertical concatenation operator
            *this = *this || matrix;
        }

    // Element Operations
        template<typename U>
        Matrix<T> operator+(const U &value) { // Element addition operator
            Matrix<T> result(m_size);
            result += value; // Use element assignment operator to add value to each element
            return result;
        }
        template<typename U>
        Matrix<T> operator-(const U &value) { // Subtraction operator
            Matrix<T> result(m_size);
            result -= value;
            return result;
        }
        template<typename U>
        Matrix<T> operator*(const U &value) { // Multiplication operator
            Matrix<T> result(m_size);
            result *= value;
            return result;
        }
        template<typename U>
        Matrix<T> operator/(const U &value) { // Division operator
            Matrix<T> result(m_size);
            result /= value;
            return result;
        }
        template<typename U>
        Matrix<T> operator^(const U &value) { // Exponentiation operator
            Matrix<T> result(m_size);
            result ^= value;
            return result;
        }

    // Element Assignment Operations
        template<typename U>
        void operator+=(const U &value) { // Addition assignment
            for (MatrixLength_t i = 0; i < m_size.rows * m_size.columns; i++) {
                m_data[i] += value; // Add value to each element
            }
        }
        template<typename U>
        void operator-=(const U &value) { // Subtraction assignment
            for (MatrixLength_t i = 0; i < m_size.rows * m_size.columns; i++) {
                m_data[i] -= value; // Subtract value from each element
            }
        }
        template<typename U>
        void operator*=(const U &value) { // Multiplication assignment
            for (MatrixLength_t i = 0; i < m_size.rows * m_size.columns; i++) {
                m_data[i] *= value; // Multiply each element by value
            }
        }
        template<typename U>
        void operator/=(const U &value) { // Division assignment
            for (MatrixLength_t i = 0; i < m_size.rows * m_size.columns; i++) {
                m_data[i] /= value; // Divide each element by value
            }
        }
        template<typename U>
        void operator^=(const U &value) { // Exponentiation assignment
            for (MatrixLength_t i = 0; i < m_size.rows * m_size.columns; i++) {
                m_data[i] = pow(m_data[i], value); // Raise each element to the power of value
            }
        }

    // Matrix Operations
        T determinant() { // Matrix determinant
            assert(isSquare());
            if (this->rows() == 1) { // 1x1 Matrix Case
                return this->get(0, 0);
            }
            if (this->rows() == 2) { // 2x2 Matrix Case
                return this->get(0, 0) * this->get(1, 1) - this->get(0, 1) * this->get(1, 0); // a*d - b*c
            }
            Matrix<T> adj(adjoint());
            Matrix<T> determinantIdentity = *this * adj; // Det using cofactor expansion (dot multiplication)
            return determinantIdentity.get(0, 0); // Return first element of det matrix
        }

        Matrix<T> adjoint() { // Matrix adjugate
            assert(isSquare());
            Matrix<T> adj(this->rows(), this->columns()); // Create cofactor matrix, named adj
            for (MatrixLength_t i = 0; i < this->rows(); i++) {
                for (MatrixLength_t j = 0; j < this->columns(); j++) {
                    adj.set(i, j, cofactor(i, j)); // Set cofactor matrix
                }
            }
            return adj.transpose(); // Return adjugate matrix
        }

        Matrix<T> inverse() { // Matrix inverse
            assert(isSquare());
            T det = determinant();
            assert(det != 0); 
            Matrix<T> inv = adjoint() / det; // Inverse formula using adjoint
        }

        T cofactor(int remove_row, int remove_column) { // Matrix cofactor
            Matrix<T> cofactor_matrix(this->rows() - 1, this->columns() - 1); // Reduced matrix for cofactor
            for (MatrixLength_t i = 0; i < this->rows(); i++) {
                for (MatrixLength_t j = 0; j < this->columns(); j++) {
                    if (i != remove_row && j != remove_column) {
                        cofactor_matrix.set(i - (i > remove_row), j - (j > remove_column), this->get(i, j)); // Set new cofactor matrix values
                    }
                }
            }
            T leader = 1 - ((remove_row + remove_column) % 2) * 2; // Leader value for cofactor (1 or -1)
            return leader * cofactor_matrix.determinant(); // Return adjusted cofactor matrix determinant
        }

        T trace() { // Trace of matrix
            assert(isSquare()); // If true, will continue, if false, will error
            T trace = 0; 
            for (MatrixLength_t i = 0; i < this->rows(); i++) {
                trace += this->get(i, i); // Add diagonal values
            }
            return trace;
        }

        Matrix<T> transpose() { // Define transpose function
            Matrix<T> transposed(this->columns(), this->rows()); // Define new matrix with swapped row and col count, named transposed
            for (MatrixLength_t i = 0; i < this->rows(); i++) {
                for (MatrixLength_t j = 0; j < this->columns(); j++) {
                    transposed.set(j, i, this->get(i, j)); // Use set to transpose values
                }
            }
            return transposed;
        }

        Matrix<T> subMatrix(int startRow, int endRow, int startCol, int endCol) { // Create new submatrix
            assert(startRow < endRow && row_end <= this->rows); // Ensure within bounds
            assert(startCol < endCol && col_end <= this->columns); 

            Matrix<T> newMatrix(endRow - startRow + 1, endCol - startCol + 1); 
            for (int i = startRow; i < endRow; ++i) {
                for (int j = startCol; j < endCol; ++j) {
                    newMatrix.set(i - startRow, j - startCol, this->get(i, j)); 
                }
            }
            return newMatrix;
        }

        int dot(const Matrix<T>& other) const {
            assert(this->rows() == 3 && this->columns() == 1 && other.rows() == 3 && other.columns() == 1);
            Matrix<T> result(3, 1);
            result.set(0, 0, this->get(0, 0) * other.get(2, 0));
            result.set(1, 0, this->get(2, 0) * other.get(0, 0) - this->get(0, 0) * other.get(2, 0));
            result.set(2, 0, this->get(0, 0) * other.get(1, 0) - this->get(1, 0) * other.get(0, 0));
            return this->get(0, 0) * other.get(0, 0) + this->get(1, 0) * other.get(1, 0) + this->get(2, 0) * other.get(2, 0);
        }

        Matrix<T> cross(const Matrix<T>& other) const {
            assert(this->rows() == 3 && this->columns() == 1 && other.rows() == 3 && other.columns() == 1);
            Matrix<T> result(3, 1);
            result.set(0, 0, this->get(1, 0) * other.get(2, 0) - this->get(2, 0) * other.get(1, 0));
            result.set(1, 0, this->get(2, 0) * other.get(0, 0) - this->get(0, 0) * other.get(2, 0));
            result.set(2, 0, this->get(0, 0) * other.get(1, 0) - this->get(1, 0) * other.get(0, 0));
            return result;
        }

        static Matrix<T> zeros(int rows, int columns) { // Create zero matrix
            Matrix<T> zeroMatrix(rows, columns);
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < columns; ++j) {
                    zeroMatrix.set(i, j, static_cast<T>(0));
                }
            }
            return zeroMatrix;
        }
        }

        bool isIdentity() { // Check for ID matrix
            if (!isSquare()) { 
                return false;
            }
            if (!isDiagonal()) {
                return false;
            }
            for (MatrixLength_t i = 0; i < this->rows(); i++) { 
                if (this->get(i, i) != 1) { // Evaluate diagonals
                    return false;
                }
            }
            return true;
        }

        bool isDiagonal() { // Check for diagonal matrix
            if (!isSquare()) {
                return false;
            }
            for (MatrixLength_t i = 0; i < this->rows(); i++) {
                for (MatrixLength_t j = 0; j < this->columns(); j++) {
                    if (i != j && this->get(i, j) != 0) { // If row != col and value != 0
                        return false;
                    }
                }
            }
            return true;
        }

        bool isSymmetric() { // Check matrix symmetry
            if (!isSquare()) { 
                return false;
            }
            for (MatrixLength_t i = 0; i < this->rows(); i++) {
                for (MatrixLength_t j = 0; j < this->columns(); j++) {
                    if (this->get(i, j) != this->get(j, i)) { // Compare transpose to input
                        return false;
                    }
                }
            }
            return true;
        }

        bool isSkewSymmetric() { // Check skew symmetric
            if (!isSquare()) { 
                return false;
            }
            for (MatrixLength_t i = 0; i < this->rows(); i++) { 
                for (MatrixLength_t j = 0; j < this->columns(); j++) { 
                    if (this->get(i, j) != -this->get(j, i)) { // Compare negative transpose to input
                        return false;
                    }
                }
            }
        }

        bool isSquare() {
            return this->rows() == this->columns(); // This refers to the class in which these fn are defined
        }

        bool isZero() { // Check if matrix is all zeros
            for (MatrixLength_t i = 0; i < m_size.rows * m_size.columns; i++) {
                if (m_data[i] != 0) {
                    return false;
                }
            }
            return true;
        }

        bool isOne() { // Check if matrix is all ones
            for (MatrixLength_t i = 0; i < m_size.rows * m_size.columns; i++) {
                if (m_data[i] != 1) {
                    return false;
                }
            }
            return true;
        }

        virtual MatrixLength_t length() { // Return greatest length of matrix
            return m_size.rows > m_size.columns ? m_size.rows : m_size.columns; // (condition ? expression1 : expression2) is a ternary operator
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

        void set(MatrixLength_t row, MatrixLength_t column, T value) { // Set value at specified row and column
            m_data[row * m_size.columns + column] = value; // Set value at linear index NOTE: indexing begins at 0 for rows and col's
        }

        T get(MatrixLength_t row, MatrixLength_t column) { // Get value at specified row and column
            return m_data[row * m_size.columns + column];
        }

    private:
        MatrixSize_t m_size;
        T *m_data;

        void initialize(bool zeroize = true) { // Allocate memory for matrix data, assumed to be true unless stated
            m_data = new T[m_size.rows * m_size.columns]; // Allocate memory for 1D matrix data
            if (zeroize) { // If zeroize is true...
                for (MatrixLength_t i = 0; i < m_size.rows * m_size.columns; i++) { 
                    m_data[i] = 0; // Fill matrix with zeros
                }
            }
        }

        void copy(Matrix<T> matrix) {
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
Matrix<U> matrix_add(Matrix<U> matrix1, Matrix<U> matrix2) { // Matrix addition
    assert(matrix1.m_size.rows == matrix2.m_size.rows && matrix1.m_size.columns == matrix2.m_size.columns);
    Matrix<U> result(matrix1.m_size);
    for (MatrixLength_t i = 0; i < matrix1.m_size.rows * matrix1.m_size.columns; i++) {
        result.m_data[i] = matrix1.m_data[i] + matrix2.m_data[i]; // Add at index
    }
    return result;
}

template<typename U>
Matrix<U> matrix_subtract(Matrix<U> matrix1, Matrix<U> matrix2) { // Matrix subtraction
    assert(matrix1.m_size.rows == matrix2.m_size.rows && matrix1.m_size.columns == matrix2.m_size.columns); // Assume matrices are same size
    Matrix<U> result(matrix1.m_size);
    for (MatrixLength_t i = 0; i < matrix1.m_size.rows * matrix1.m_size.columns; i++) {
        result.m_data[i] = matrix1.m_data[i] - matrix2.m_data[i]; // Subtract at index
    }
    return result;
}

template<typename U>
Matrix<U> matrix_multiply(Matrix<U> matrix1, Matrix<U> matrix2) { // Matrix multiplication
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
Matrix<U> matrix_hcat(Matrix<U> &left, Matrix<U> &right) { // Concatenate matrices horizontally
    assert(left.m_size.rows == right.m_size.rows);
    Matrix<U> result(left.m_size.rows, left.m_size.columns + right.m_size.columns);
    for (MatrixLength_t i = 0; i < left.m_size.rows * result.m_size.columns; i++) {
        if (i % result.m_size.columns < left.m_size.columns) { // If column index is in bounds of the left's columns
            result.m_data[i] = left.m_data[i]; // Copy left
        } else {
            result.m_data[i] = right.m_data[i - left.m_size.columns]; // Copy right
        }
    }
    return result;
}

template<typename U>
Matrix<U> matrix_vcat(Matrix<U> &top, Matrix<U> &bottom) { // Concatenate matrices vertically
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