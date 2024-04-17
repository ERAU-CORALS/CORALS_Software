/**
 ********************************************************************************
 * @file    matrix.ino
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Unit Tests of Matrix Class
 * @version 1.0
 * @date    2024-03-18
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#include <math.h>
#include <stdlib.h>
#include <unity.h>

#include "Matrix.tpp"
#include "Vector.tpp"
using namespace DataStructures::Matrix;
using namespace DataStructures::Vector;

void Matrix_Constructor() {
    // Size for all Constructors
    MatrixLength_t rows = 3;
    MatrixLength_t columns = 4;
    MatrixSize_t size = {rows, columns};

    TEST_MESSAGE("Matrix Row/Column Constructor");
    {
        Matrix<int> matrix(rows, columns);
        TEST_ASSERT_EQUAL_UINT_MESSAGE(rows, matrix.rows(), "Matrix Rows not equivalent to Constructor Argument");
        TEST_ASSERT_EQUAL_UINT_MESSAGE(columns, matrix.columns(), "Matrix Columns not equivalent to Constructor Argument");
        for (MatrixLength_t i = 0; i < rows; i++) {
            for (MatrixLength_t j = 0; j < columns; j++) {
                TEST_ASSERT_EQUAL_INT_MESSAGE(0, matrix.get(i, j), "Matrix Element not initialized to Zero");
            }
        }
    }

    TEST_MESSAGE("Matrix Size Constructor");
    {
        Matrix<int> matrix(size);
        TEST_ASSERT_EQUAL_UINT_MESSAGE(rows, matrix.rows(), "Matrix Rows not equivalent to Constructor Argument");
        TEST_ASSERT_EQUAL_UINT_MESSAGE(columns, matrix.columns(), "Matrix Columns not equivalent to Constructor Argument");
        for (MatrixLength_t i = 0; i < rows; i++) {
            for (MatrixLength_t j = 0; j < columns; j++) {
                TEST_ASSERT_EQUAL_INT_MESSAGE(0, matrix.get(i, j), "Matrix Element not initialized to Zero");
            }
        }
    }

    TEST_MESSAGE("Matrix Copy Constructor");
    {
        // Create Matrix to Copy
        Matrix<int> matrix(size);
        for (MatrixLength_t i = 0; i < rows; i++) {
            for (MatrixLength_t j = 0; j < columns; j++) {
                matrix.set(i, j, i + j);
            }
        }

        // Copy Matrix
        Matrix<int> copy(matrix);
        TEST_ASSERT_EQUAL_UINT_MESSAGE(matrix.rows(), copy.rows(), "Copied Matrix Rows not equivalent to Source Matrix Rows");
        TEST_ASSERT_EQUAL_UINT_MESSAGE(matrix.columns(), copy.columns(), "Copied Matrix Columns not equivalent to Source Matrix Columns");
        for (MatrixLength_t i = 0; i < rows; i++) {
            for (MatrixLength_t j = 0; j < columns; j++) {
                TEST_ASSERT_EQUAL_INT_MESSAGE(matrix.get(i, j), copy.get(i, j), "Copied Matrix Element not equivalent to Source Matrix Element");
            }
        }
    }

    TEST_MESSAGE("Matrix Assignment Operator");
    {
        // Create Matrix to Assign
        Matrix<int> matrix(size);
        for (MatrixLength_t i = 0; i < rows; i++) {
            for (MatrixLength_t j = 0; j < columns; j++) {
                matrix.set(i, j, i + j);
            }
        }

        // Assign Matrix
        Matrix<int> assign = matrix;
        TEST_ASSERT_EQUAL_UINT_MESSAGE(matrix.rows(), assign.rows(), "Assigned Matrix Rows not equivalent to Source Matrix Rows");
        TEST_ASSERT_EQUAL_UINT_MESSAGE(matrix.columns(), assign.columns(), "Assigned Matrix Columns not equivalent to Source Matrix Columns");
        for (MatrixLength_t i = 0; i < rows; i++) {
            for (MatrixLength_t j = 0; j < columns; j++) {
                TEST_ASSERT_EQUAL_INT_MESSAGE(matrix.get(i, j), assign.get(i, j), "Assigned Matrix Element not equivalent to Source Matrix Element");
            }
        }
    }

    TEST_MESSAGE("Matrix Vector Constructor");
    {
        // Create Vector to Construct Matrix
        Vector<int> vector(rows * columns);
        for (MatrixLength_t i = 0; i < rows * columns; i++) {
            vector.set(i, i);
        }

        // Construct Matrix from Vector
        Matrix<int> matrix(vector);
        TEST_ASSERT_EQUAL_UINT_MESSAGE(vector.length(), matrix.rows(), "Matrix Rows not equivalent to Constructor Argument");
        TEST_ASSERT_EQUAL_UINT_MESSAGE(1, matrix.columns(), "Matrix Columns not equivalent to 1");
        for (MatrixLength_t i = 0; i < matrix.rows(); i++) {
            for (MatrixLength_t j = 0; j < matrix.columns(); j++) {
                TEST_ASSERT_EQUAL_INT_MESSAGE(vector.get(i), matrix.get(i, j), "Matrix Element not equivalent to Vector Element");
            }
        }
    }
    
}

void Matrix_MultiMatrix_Operators() {
    // Size for all Matrices
    MatrixLength_t rows = 3;
    MatrixLength_t columns = 4;
    MatrixSize_t size = {rows, columns};

    // Create Matrices
    Matrix<int> matrix1(size);
    Matrix<int> matrix2(size);

    for (MatrixLength_t i = 0; i < rows; i++) {
        for (MatrixLength_t j = 0; j < columns; j++) {
            matrix1.set(i, j, i + j);
            matrix2.set(i, j, i - j);
        }
    }

    TEST_MESSAGE("Matrix Addition");
    {
        Matrix<int> result = matrix1 + matrix2;
        TEST_ASSERT_EQUAL_UINT_MESSAGE(rows, result.rows(), "Result Matrix Rows not equivalent to Source Matrix Rows");
        TEST_ASSERT_EQUAL_UINT_MESSAGE(columns, result.columns(), "Result Matrix Columns not equivalent to Source Matrix Columns");
        for (MatrixLength_t i = 0; i < rows; i++) {
            for (MatrixLength_t j = 0; j < columns; j++) {
                TEST_ASSERT_EQUAL_INT_MESSAGE(matrix1.get(i, j) + matrix2.get(i, j), result.get(i, j), "Result Matrix Element not equivalent to Sum of Source Matrix Elements");
            }
        }
    }

    TEST_MESSAGE("Matrix Subtraction");
    {
        Matrix<int> result = matrix1 - matrix2;
        TEST_ASSERT_EQUAL_UINT_MESSAGE(rows, result.rows(), "Result Matrix Rows not equivalent to Source Matrix Rows");
        TEST_ASSERT_EQUAL_UINT_MESSAGE(columns, result.columns(), "Result Matrix Columns not equivalent to Source Matrix Columns");
        for (MatrixLength_t i = 0; i < rows; i++) {
            for (MatrixLength_t j = 0; j < columns; j++) {
                TEST_ASSERT_EQUAL_INT_MESSAGE(matrix1.get(i, j) - matrix2.get(i, j), result.get(i, j), "Result Matrix Element not equivalent to Difference of Source Matrix Elements");
            }
        }
    }

    TEST_MESSAGE("Matrix Multiplication");
    {
        Matrix<int> result = matrix1 * ~matrix2;
        TEST_ASSERT_EQUAL_UINT_MESSAGE(matrix1.rows(), result.rows(), "Result Matrix Rows not equivalent to Source Matrix Rows");
        TEST_ASSERT_EQUAL_UINT_MESSAGE(matrix2.rows(), result.columns(), "Result Matrix Columns not equivalent to Source Matrix Transposed Columns");
        for (MatrixLength_t i = 0; i < matrix1.rows(); i++) {
            for (MatrixLength_t j = 0; j < matrix2.rows(); j++) {
                int sum = 0;
                for (MatrixLength_t k = 0; k < matrix1.columns(); k++) {
                    sum += matrix1.get(i, k) * matrix2.get(j, k);
                }
                TEST_ASSERT_EQUAL_INT_MESSAGE(sum, result.get(i, j), "Result Matrix Element not equivalent to Product of Source Matrix Elements");
            }
        }
    }

    TEST_MESSAGE("Matrix Multiplication by Vector");
    {
        // Create Vector to Multiply
        Vector<int> vector(columns);
        for (MatrixLength_t i = 0; i < columns; i++) {
            vector.set(i, i+2);
        }

        // Multiply Matrix by Vector
        Vector<int> result = matrix1 * vector;
        TEST_ASSERT_EQUAL_UINT_MESSAGE(matrix1.rows(), result.length(), "Result Vector Length not equivalent to Source Matrix Rows");
        for (MatrixLength_t i = 0; i < matrix1.rows(); i++) {
            int sum = 0;
            for (MatrixLength_t j = 0; j < matrix1.columns(); j++) {
                sum += matrix1.get(i, j) * vector.get(j);
            }
            TEST_ASSERT_EQUAL_INT_MESSAGE(sum, result.get(i), "Result Vector Element not equivalent to Product of Source Matrix Elements");
        }
    }

    TEST_MESSAGE("Vector Multiplication by Matrix");
    {
        // Create Vector to Multiply
        Vector<int> vector(rows);
        for (MatrixLength_t i = 0; i < rows; i++) {
            vector.set(i, i+2);
        }

        // Multiply Vector by Matrix
        Vector<int> result = vector * matrix1;
        TEST_ASSERT_EQUAL_UINT_MESSAGE(matrix1.columns(), result.length(), "Result Vector Length not equivalent to Source Matrix Columns");
        for (MatrixLength_t i = 0; i < matrix1.columns(); i++) {
            int sum = 0;
            for (MatrixLength_t j = 0; j < matrix1.rows(); j++) {
                sum += vector.get(j) * matrix1.get(j, i);
            }
            TEST_ASSERT_EQUAL_INT_MESSAGE(sum, result.get(i), "Result Vector Element not equivalent to Product of Source Matrix Elements");
        }
    }

    TEST_MESSAGE("Matrix Horizontal Concatenation");
    {
        Matrix<int> result = matrix1 << matrix2;
        TEST_ASSERT_EQUAL_UINT_MESSAGE(matrix1.rows(), result.rows(), "Result Matrix Rows not equivalent to Source Matrix Rows");
        TEST_ASSERT_EQUAL_UINT_MESSAGE(matrix1.columns() + matrix2.columns(), result.columns(), "Result Matrix Columns not equivalent to Sum of Source Matrix Columns");
        for (MatrixLength_t i = 0; i < rows; i++) {
            for (MatrixLength_t j = 0; j < result.columns(); j++) {
                if (j < columns) {
                    TEST_ASSERT_EQUAL_INT_MESSAGE(matrix1.get(i, j), result.get(i, j), "Result Matrix Element not equivalent to Source Matrix Element");
                } else {
                    TEST_ASSERT_EQUAL_INT_MESSAGE(matrix2.get(i, j - columns), result.get(i, j), "Result Matrix Element not equivalent to Source Matrix Element");
                }
            }
        }
    }

    TEST_MESSAGE("Matrix Horizontal Concatenation with Vector");
    {
        // Create Vector to Concatenate
        Vector<int> vector(rows);
        for (MatrixLength_t i = 0; i < rows; i++) {
            vector.set(i, i+2);
        }

        // Concatenate Matrix with Vector
        Matrix<int> result = matrix1 << vector;
        TEST_ASSERT_EQUAL_UINT_MESSAGE(matrix1.rows(), result.rows(), "Result Matrix Rows not equivalent to Source Matrix Rows");
        TEST_ASSERT_EQUAL_UINT_MESSAGE(matrix1.columns() + 1, result.columns(), "Result Matrix Columns not equivalent to Sum of Source Matrix Columns and Vector Length");
        for (MatrixLength_t i = 0; i < rows; i++) {
            for (MatrixLength_t j = 0; j < columns; j++) {
                TEST_ASSERT_EQUAL_INT_MESSAGE(matrix1.get(i, j), result.get(i, j), "Result Matrix Element not equivalent to Source Matrix Element");
            }
            TEST_ASSERT_EQUAL_INT_MESSAGE(vector.get(i), result.get(i, columns), "Result Matrix Element not equivalent to Vector Element");
        }
    }

    TEST_MESSAGE("Matrix Vertical Concatenation");
    {
        Matrix<int> result = matrix1 | matrix2;
        TEST_ASSERT_EQUAL_UINT_MESSAGE(matrix1.rows() + matrix2.rows(), result.rows(), "Result Matrix Rows not equivalent to Sum of Source Matrix Rows");
        TEST_ASSERT_EQUAL_UINT_MESSAGE(matrix1.columns(), result.columns(), "Result Matrix Columns not equivalent to Source Matrix Columns");
        for (MatrixLength_t i = 0; i < rows; i++) {
            for (MatrixLength_t j = 0; j < columns; j++) {
                TEST_ASSERT_EQUAL_INT_MESSAGE(matrix1.get(i, j), result.get(i, j), "Result Matrix Element not equivalent to Source Matrix Element");
            }
        }
        for (MatrixLength_t i = 0; i < rows; i++) {
            for (MatrixLength_t j = 0; j < columns; j++) {
                TEST_ASSERT_EQUAL_INT_MESSAGE(matrix2.get(i, j), result.get(i + rows, j), "Result Matrix Element not equivalent to Source Matrix Element");
            }
        }
    }
}

void Matrix_MultiMatrix_Assignment_Operators() {
    // Size for all Matrices
    MatrixLength_t rows = 3;
    MatrixLength_t columns = 4;
    MatrixSize_t size = {rows, columns};

    // Create Matrices
    Matrix<int> matrix1(size);
    Matrix<int> matrix2(size);

    for (MatrixLength_t i = 0; i < rows; i++) {
        for (MatrixLength_t j = 0; j < columns; j++) {
            matrix1.set(i, j, i + j);
            matrix2.set(i, j, i - j);
        }
    }

    TEST_MESSAGE("Matrix Addition Assignment");
    {
        Matrix<int> result = matrix1;
        result += matrix2;
        for (MatrixLength_t i = 0; i < rows; i++) {
            for (MatrixLength_t j = 0; j < columns; j++) {
                TEST_ASSERT_EQUAL_INT_MESSAGE(matrix1.get(i, j) + matrix2.get(i, j), result.get(i, j), "Result Matrix Element not equivalent to Sum of Source Matrix Elements");
            }
        }
    }

    TEST_MESSAGE("Matrix Subtraction Assignment");
    {
        Matrix<int> result = matrix1;
        result -= matrix2;
        for (MatrixLength_t i = 0; i < rows; i++) {
            for (MatrixLength_t j = 0; j < columns; j++) {
                TEST_ASSERT_EQUAL_INT_MESSAGE(matrix1.get(i, j) - matrix2.get(i, j), result.get(i, j), "Result Matrix Element not equivalent to Difference of Source Matrix Elements");
            }
        }
    }

    TEST_MESSAGE("Matrix Multiplication Assignment");
    {
        Matrix<int> result = matrix1;
        result *= ~matrix2;
        TEST_ASSERT_EQUAL_UINT_MESSAGE(matrix1.rows(), result.rows(), "Result Matrix Rows not equivalent to Source Matrix Rows");
        TEST_ASSERT_EQUAL_UINT_MESSAGE(matrix2.rows(), result.columns(), "Result Matrix Columns not equivalent to Source Matrix Transposed Columns");
        for (MatrixLength_t i = 0; i < matrix1.rows(); i++) {
            for (MatrixLength_t j = 0; j < matrix2.rows(); j++) {
                int sum = 0;
                for (MatrixLength_t k = 0; k < matrix1.columns(); k++) {
                    sum += matrix1.get(i, k) * matrix2.get(j, k);
                }
                TEST_ASSERT_EQUAL_INT_MESSAGE(sum, result.get(i, j), "Result Matrix Element not equivalent to Product of Source Matrix Elements");
            }
        }
    }

    TEST_MESSAGE("Matrix Horizontal Concatenation Assignment");
    {
        Matrix<int> result = matrix1;
        result <<= matrix2;
        TEST_ASSERT_EQUAL_UINT_MESSAGE(matrix1.rows(), result.rows(), "Result Matrix Rows not equivalent to Source Matrix Rows");
        TEST_ASSERT_EQUAL_UINT_MESSAGE(matrix1.columns() + matrix2.columns(), result.columns(), "Result Matrix Columns not equivalent to Sum of Source Matrix Columns");
        for (MatrixLength_t i = 0; i < rows; i++) {
            for (MatrixLength_t j = 0; j < result.columns(); j++) {
                if (j < columns) {
                    TEST_ASSERT_EQUAL_INT_MESSAGE(matrix1.get(i, j), result.get(i, j), "Result Matrix Element not equivalent to Source Matrix Element");
                } else {
                    TEST_ASSERT_EQUAL_INT_MESSAGE(matrix2.get(i, j - columns), result.get(i, j), "Result Matrix Element not equivalent to Source Matrix Element");
                }
            }
        }
    }

    TEST_MESSAGE("Matrix Horizontal Concatenation with Vector Assignment");
    {
        // Create Vector to Concatenate
        Vector<int> vector(rows);
        for (MatrixLength_t i = 0; i < rows; i++) {
            vector.set(i, i+2);
        }

        // Concatenate Matrix with Vector
        Matrix<int> result = matrix1;
        result <<= vector;
        TEST_ASSERT_EQUAL_UINT_MESSAGE(matrix1.rows(), result.rows(), "Result Matrix Rows not equivalent to Source Matrix Rows");
        TEST_ASSERT_EQUAL_UINT_MESSAGE(matrix1.columns() + 1, result.columns(), "Result Matrix Columns not equivalent to Sum of Source Matrix Columns and Vector Length");
        for (MatrixLength_t i = 0; i < rows; i++) {
            for (MatrixLength_t j = 0; j < columns; j++) {
                TEST_ASSERT_EQUAL_INT_MESSAGE(matrix1.get(i, j), result.get(i, j), "Result Matrix Element not equivalent to Source Matrix Element");
            }
            TEST_ASSERT_EQUAL_INT_MESSAGE(vector.get(i), result.get(i, columns), "Result Matrix Element not equivalent to Vector Element");
        }
    }

    TEST_MESSAGE("Matrix Vertical Concatenation Assignment");
    {
        Matrix<int> result = matrix1;
        result |= matrix2;
        TEST_ASSERT_EQUAL_UINT_MESSAGE(matrix1.rows() + matrix2.rows(), result.rows(), "Result Matrix Rows not equivalent to Sum of Source Matrix Rows");
        TEST_ASSERT_EQUAL_UINT_MESSAGE(matrix1.columns(), result.columns(), "Result Matrix Columns not equivalent to Source Matrix Columns");
        for (MatrixLength_t i = 0; i < rows; i++) {
            for (MatrixLength_t j = 0; j < columns; j++) {
                TEST_ASSERT_EQUAL_INT_MESSAGE(matrix1.get(i, j), result.get(i, j), "Result Matrix Element not equivalent to Source Matrix Element");
            }
        }
        for (MatrixLength_t i = 0; i < rows; i++) {
            for (MatrixLength_t j = 0; j < columns; j++) {
                TEST_ASSERT_EQUAL_INT_MESSAGE(matrix2.get(i, j), result.get(i + rows, j), "Result Matrix Element not equivalent to Source Matrix Element");
            }
        }
    }

    TEST_MESSAGE("Matrix Vertical Concatenation with Vector Assignment");
    {
        // Create Vector to Concatenate
        Vector<int> vector(columns);
        for (MatrixLength_t i = 0; i < columns; i++) {
            vector.set(i, i+2);
        }

        // Concatenate Matrix with Vector
        Matrix<int> result = matrix1;
        result |= vector;
        TEST_ASSERT_EQUAL_UINT_MESSAGE(matrix1.rows() + 1, result.rows(), "Result Matrix Rows not equivalent to Sum of Source Matrix Rows and Vector Length");
        TEST_ASSERT_EQUAL_UINT_MESSAGE(matrix1.columns(), result.columns(), "Result Matrix Columns not equivalent to Source Matrix Columns");
        for (MatrixLength_t i = 0; i < rows; i++) {
            for (MatrixLength_t j = 0; j < columns; j++) {
                TEST_ASSERT_EQUAL_INT_MESSAGE(matrix1.get(i, j), result.get(i, j), "Result Matrix Element not equivalent to Source Matrix Element");
            }
        }
        for (MatrixLength_t i = 0; i < columns; i++) {
            TEST_ASSERT_EQUAL_INT_MESSAGE(vector.get(i), result.get(rows, i), "Result Matrix Element not equivalent to Vector Element");
        }
    }
}

void Matrix_Element_Operators() {
    // Size for all Matrices
    MatrixLength_t rows = 3;
    MatrixLength_t columns = 4;
    MatrixSize_t size = {rows, columns};

    // Create Matrices
    Matrix<double> matrix(size);

    for (MatrixLength_t i = 0; i < rows; i++) {
        for (MatrixLength_t j = 0; j < columns; j++) {
            matrix.set(i, j, i + 2.5*j);
        }
    }

    TEST_MESSAGE("Element Addition");
    {
        Matrix<double> result = matrix + 2.5;
        for (MatrixLength_t i = 0; i < rows; i++) {
            for (MatrixLength_t j = 0; j < columns; j++) {
                const double expected = matrix.get(i, j) + 2.5;
                TEST_ASSERT_FLOAT_WITHIN_MESSAGE(fabs(0.001 * expected), expected, result.get(i, j), "Result Matrix Element not equivalent to Source Matrix Element plus Scalar");
            }
        }
    }

    TEST_MESSAGE("Element Subtraction");
    {
        Matrix<double> result = matrix - 2.5;
        for (MatrixLength_t i = 0; i < rows; i++) {
            for (MatrixLength_t j = 0; j < columns; j++) {
                const double expected = matrix.get(i, j) - 2.5;
                TEST_ASSERT_FLOAT_WITHIN_MESSAGE(fabs(0.001 * expected), expected, result.get(i, j), "Result Matrix Element not equivalent to Source Matrix Element minus Scalar");
            }
        }
    }

    TEST_MESSAGE("Element Multiplication");
    {
        Matrix<double> result = matrix * 2.5;
        for (MatrixLength_t i = 0; i < rows; i++) {
            for (MatrixLength_t j = 0; j < columns; j++) {
                const double expected = matrix.get(i, j) * 2.5;
                TEST_ASSERT_FLOAT_WITHIN_MESSAGE(fabs(0.001 * expected), expected, result.get(i, j), "Result Matrix Element not equivalent to Source Matrix Element times Scalar");
            }
        }
    }

    TEST_MESSAGE("Element Division");
    {
        Matrix<double> result = matrix / 2.5;
        for (MatrixLength_t i = 0; i < rows; i++) {
            for (MatrixLength_t j = 0; j < columns; j++) {
                const double expected = matrix.get(i, j) / 2.5;
                TEST_ASSERT_FLOAT_WITHIN_MESSAGE(fabs(0.001 * expected), expected, result.get(i, j), "Result Matrix Element not equivalent to Source Matrix Element divided by Scalar");
            }
        }
    }

    TEST_MESSAGE("Element Exponentiation");
    {
        Matrix<double> result = matrix ^ 2.5;
        for (MatrixLength_t i = 0; i < rows; i++) {
            for (MatrixLength_t j = 0; j < columns; j++) {
                const double expected = pow(matrix.get(i, j), 2.5);
                TEST_ASSERT_FLOAT_WITHIN_MESSAGE(fabs(0.001 * expected), expected, result.get(i, j), "Result Matrix Element not equivalent to Source Matrix Element raised to Scalar Power");
            }
        }
    }
}

void Matrix_Element_Assignment_Operators() {
    // Size for all Matrices
    MatrixLength_t rows = 3;
    MatrixLength_t columns = 4;
    MatrixSize_t size = {rows, columns};

    // Create Matrices
    Matrix<double> matrix(size);

    for (MatrixLength_t i = 0; i < rows; i++) {
        for (MatrixLength_t j = 0; j < columns; j++) {
            matrix.set(i, j, i + 2.5*j);
        }
    }

    TEST_MESSAGE("Element Addition Assignment");
    {
        Matrix<double> result = matrix;
        result += 2.5;
        for (MatrixLength_t i = 0; i < rows; i++) {
            for (MatrixLength_t j = 0; j < columns; j++) {
                const double expected = matrix.get(i, j) + 2.5;
                TEST_ASSERT_FLOAT_WITHIN_MESSAGE(fabs(0.001 * expected), expected, result.get(i, j), "Result Matrix Element not equivalent to Source Matrix Element plus Scalar");
            }
        }
    }

    TEST_MESSAGE("Element Subtraction Assignment");
    {
        Matrix<double> result = matrix;
        result -= 2.5;
        for (MatrixLength_t i = 0; i < rows; i++) {
            for (MatrixLength_t j = 0; j < columns; j++) {
                const double expected = matrix.get(i, j) - 2.5;
                TEST_ASSERT_FLOAT_WITHIN_MESSAGE(fabs(0.001 * expected), expected, result.get(i, j), "Result Matrix Element not equivalent to Source Matrix Element minus Scalar");
            }
        }
    }

    TEST_MESSAGE("Element Multiplication Assignment");
    {
        Matrix<double> result = matrix;
        result *= 2.5;
        for (MatrixLength_t i = 0; i < rows; i++) {
            for (MatrixLength_t j = 0; j < columns; j++) {
                const double expected = matrix.get(i, j) * 2.5;
                TEST_ASSERT_FLOAT_WITHIN_MESSAGE(fabs(0.001 * expected), expected, result.get(i, j), "Result Matrix Element not equivalent to Source Matrix Element times Scalar");
            }
        }
    }

    TEST_MESSAGE("Element Division Assignment");
    {
        Matrix<double> result = matrix;
        result /= 2.5;
        for (MatrixLength_t i = 0; i < rows; i++) {
            for (MatrixLength_t j = 0; j < columns; j++) {
                const double expected = matrix.get(i, j) / 2.5;
                TEST_ASSERT_FLOAT_WITHIN_MESSAGE(fabs(0.001 * expected), expected, result.get(i, j), "Result Matrix Element not equivalent to Source Matrix Element divided by Scalar");
            }
        }
    }

    TEST_MESSAGE("Element Exponentiation Assignment");
    {
        Matrix<double> result = matrix;
        result ^= 2.5;
        for (MatrixLength_t i = 0; i < rows; i++) {
            for (MatrixLength_t j = 0; j < columns; j++) {
                const double expected = pow(matrix.get(i, j), 2.5);
                TEST_ASSERT_FLOAT_WITHIN_MESSAGE(fabs(0.001 * expected), expected, result.get(i, j), "Result Matrix Element not equivalent to Source Matrix Element raised to Scalar Power");
            }
        }
    }
}

void Matrix_Operators() {
    // Size for all Matrices
    MatrixLength_t rows = 4;
    MatrixLength_t columns = 4;
    MatrixSize_t size = {rows, columns};

    // Create Matrices
    Matrix<int> matrix(size);
    
    do {
        for (MatrixLength_t i = 0; i < rows; i++) {
            for (MatrixLength_t j = 0; j < columns; j++) {
                matrix.set(i, j, rand() % (rows * columns));
            }
        }
    } while (matrix.determinant() == 0);

    TEST_MESSAGE("Matrix Adjugate");
    {
        Matrix<int> result = matrix.adjugate();
        TEST_ASSERT_EQUAL_UINT_MESSAGE(matrix.columns(), result.rows(), "Result Matrix Rows not equivalent to Source Matrix Columns");
        TEST_ASSERT_EQUAL_UINT_MESSAGE(matrix.rows(), result.columns(), "Result Matrix Columns not equivalent to Source Matrix Rows");
        for (MatrixLength_t i = 0; i < matrix.columns(); i++) {
            for (MatrixLength_t j = 0; j < matrix.rows(); j++) {
                TEST_ASSERT_EQUAL_INT_MESSAGE(matrix.cofactor(j, i), result.get(i, j), "Result Matrix Element not equivalent to Transposed Cofactor Matrix Element");
            }
        }
    }

    TEST_MESSAGE("Matrix Cofactor");
    {
        for (MatrixLength_t i = 0; i < matrix.rows(); i++) {
            for (MatrixLength_t j = 0; j < matrix.columns(); j++) {
                const int cofactor = matrix.cofactor(i, j);
                const int determinant = matrix.minor(i, j).determinant();
                const int sign = (i + j) % 2 == 0 ? 1 : -1;
                TEST_ASSERT_EQUAL_INT_MESSAGE(sign * determinant, cofactor, "Cofactor not equivalent to Sign * Minor");
            }
        }
    }

    TEST_MESSAGE("Matrix Determinant");
    {
        const int determinant = matrix.determinant();
        Matrix<int> determinantIdentity = matrix * matrix.adjugate();
        const int expected = determinantIdentity.get(0, 0);
        TEST_ASSERT_EQUAL_INT_MESSAGE(expected, determinant, "Determinant not equivalent to Sum of First Row Elements times Cofactors");
    }

    TEST_MESSAGE("Matrix Inverse");
    {
        Matrix<int> result = matrix.inverse();
        Matrix<int> expected = matrix.adjugate() / matrix.determinant();
        TEST_ASSERT_EQUAL_UINT_MESSAGE(expected.rows(), result.rows(), "Result Matrix Rows not equivalent to Source Matrix Rows");
        TEST_ASSERT_EQUAL_UINT_MESSAGE(expected.columns(), result.columns(), "Result Matrix Columns not equivalent to Source Matrix Columns");
        for (MatrixLength_t i = 0; i < result.rows(); i++) {
            for (MatrixLength_t j = 0; j < result.columns(); j++) {
                TEST_ASSERT_EQUAL_INT_MESSAGE(expected.get(i, j), result.get(i, j), "Result Matrix Element not equivalent to Expected Matrix Element");
            }
        }
    }

    TEST_MESSAGE("Matrix Minor");
    {
        for (MatrixLength_t i = 0; i < matrix.rows(); i++) {
            for (MatrixLength_t j = 0; j < matrix.columns(); j++) {
                Matrix<int> result = matrix.minor(i, j);
                TEST_ASSERT_EQUAL_UINT_MESSAGE(matrix.rows() - 1, result.rows(), "Result Matrix Rows not equivalent to Source Matrix Rows minus 1");
                TEST_ASSERT_EQUAL_UINT_MESSAGE(matrix.columns() - 1, result.columns(), "Result Matrix Columns not equivalent to Source Matrix Columns minus 1");
                for (MatrixLength_t k = 0; k < matrix.rows(); k++) {
                    if (k == i) {
                        continue;
                    }
                    for (MatrixLength_t l = 0; l < matrix.columns(); l++) {
                        if (l == j) {
                            continue;
                        }
                        TEST_ASSERT_EQUAL_INT_MESSAGE(matrix.get(k, l), result.get(k < i ? k : k - 1, l < j ? l : l - 1), "Result Matrix Element not equivalent to Source Matrix Element");
                    }
                }
            }
        }
    }

    TEST_MESSAGE("Matrix Trace");
    {
        const int trace = matrix.trace();
        int sum = 0;
        for (MatrixLength_t i = 0; i < matrix.rows(); i++) {
            sum += matrix.get(i, i);
        }
        TEST_ASSERT_EQUAL_INT_MESSAGE(sum, trace, "Trace not equivalent to Sum of Diagonal Elements");
    }

    TEST_MESSAGE("Matrix Transpose");
    {
        Matrix<int> result = ~matrix;
        TEST_ASSERT_EQUAL_UINT_MESSAGE(matrix.columns(), result.rows(), "Result Matrix Rows not equivalent to Source Matrix Columns");
        TEST_ASSERT_EQUAL_UINT_MESSAGE(matrix.rows(), result.columns(), "Result Matrix Columns not equivalent to Source Matrix Rows");
        for (MatrixLength_t i = 0; i < matrix.rows(); i++) {
            for (MatrixLength_t j = 0; j < matrix.columns(); j++) {
                TEST_ASSERT_EQUAL_INT_MESSAGE(matrix.get(i, j), result.get(j, i), "Result Matrix Element not equivalent to Transposed Source Matrix Element");
            }
        }
    }

    TEST_MESSAGE("Matrix isDiagonal");
    {
        TEST_ASSERT_FALSE_MESSAGE(matrix.isDiagonal(), "Matrix is Diagonal");
        Matrix<int> diagonal(size);
        for (MatrixLength_t i = 0; i < matrix.rows(); i++) {
            diagonal.set(i, i, matrix.get(i, i));
        }
        TEST_ASSERT_TRUE_MESSAGE(diagonal.isDiagonal(), "Matrix is not Diagonal");
    }

    TEST_MESSAGE("Matrix isIdentity");
    {
        TEST_ASSERT_FALSE_MESSAGE(matrix.isIdentity(), "Matrix is Identity");
        Matrix<int> identity(size);
        for (MatrixLength_t i = 0; i < matrix.rows(); i++) {
            identity.set(i, i, 1);
        }
        TEST_ASSERT_TRUE_MESSAGE(identity.isIdentity(), "Matrix is not Identity");
    }

    TEST_MESSAGE("Matrix isSquare");
    {
        TEST_ASSERT_TRUE_MESSAGE(matrix.isSquare(), "Matrix is not Square");
        Matrix<int> notSquare(2, 3);
        TEST_ASSERT_FALSE_MESSAGE(notSquare.isSquare(), "Matrix is Square");
    }

    TEST_MESSAGE("Matrix isSymmetric");
    {
        TEST_ASSERT_FALSE_MESSAGE(matrix.isSymmetric(), "Matrix is Symmetric");
        Matrix<int> symmetric(size);
        for (MatrixLength_t i = 0; i < matrix.rows(); i++) {
            for (MatrixLength_t j = 0; j < matrix.columns(); j++) {
                symmetric.set(i, j, i + j);
            }
        }
        TEST_ASSERT_TRUE_MESSAGE(symmetric.isSymmetric(), "Matrix is not Symmetric");
    }

    TEST_MESSAGE("Matrix isSkewSymmetric");
    {
        TEST_ASSERT_FALSE_MESSAGE(matrix.isSkewSymmetric(), "Matrix is Skew Symmetric");
        Matrix<int> skewSymmetric(matrix);
        for (MatrixLength_t i = 0; i < matrix.rows(); i++) {
            for (MatrixLength_t j = i; j < matrix.columns(); j++) {
                if (i == j) continue;
                skewSymmetric.set(j, i, -matrix.get(i, j));
            }
        }
        TEST_ASSERT_TRUE_MESSAGE(skewSymmetric.isSkewSymmetric(), "Matrix is not Skew Symmetric");
    }

    TEST_MESSAGE("Matrix isZero");
    {
        TEST_ASSERT_FALSE_MESSAGE(matrix.isZero(), "Matrix is Zero");
        Matrix<int> zero(size);
        TEST_ASSERT_TRUE_MESSAGE(zero.isZero(), "Matrix is not Zero");
    }

    TEST_MESSAGE("Matrix isOne");
    {
        TEST_ASSERT_FALSE_MESSAGE(matrix.isOne(), "Matrix is One");
        Matrix<int> one(size);
        one += 1;
        TEST_ASSERT_TRUE_MESSAGE(one.isOne(), "Matrix is not One");
    }
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(Matrix_Constructor);
    RUN_TEST(Matrix_MultiMatrix_Operators);
    RUN_TEST(Matrix_MultiMatrix_Assignment_Operators);
    RUN_TEST(Matrix_Element_Operators);
    RUN_TEST(Matrix_Element_Assignment_Operators);
    RUN_TEST(Matrix_Operators);
    
    UNITY_END();

    return 0;
}