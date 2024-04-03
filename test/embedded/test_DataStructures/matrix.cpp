/**
 ********************************************************************************
 * @file    matrix.cpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Unit Tests of Matrix Class
 * @version 1.0
 * @date    2024-03-18
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#include <Arduino.h>

#include <unity.h>
#include <assert.h>
#include "test_utilities.hpp"

#include "Matrix.tpp"
using namespace DataStructures;

void Matrix_Constructor() {
    const char *description = "Verify Matrix Constructor creates a Matrix object";
    const char *for_set[] = {
        "Row Column Matrix, Size Matrix, Copy Matrix",
        "Integer, Decimal"
    };
    const char *preconditions[] = {
        "Valid Row Number",
        "Valid Column Number",
        "Valid Size Structure",
        "Valid Matrix to Copy"
    };
    const char *results[] = {
        "Matrix Created and Zeroed with Expected Size",
        "Matrix Created and Zeroed with Expected Size",
        "Matrix Created and Copied with Expected Size",
    };

    TestPreamble(description, for_set, preconditions, results);

    // Integer Row Column Matrix Constructor
    {
        Matrix<int> *matrix = nullptr;
        MatrixLength_t rows = 3;
        MatrixLength_t columns = 4;
        matrix = new Matrix<int>(rows, columns);
        Verify_Ptr("Matrix Memory Allocation", nullptr, matrix, NOT_EQUAL);
        Verify_UInt("Matrix Rows", rows, matrix->rows(), EQUAL);
        Verify_UInt("Matrix Columns", columns, matrix->columns(), EQUAL);
        for (MatrixLength_t i = 0; i < rows; i++) {
            for (MatrixLength_t j = 0; j < columns; j++) {
                Verify_Int("Matrix Element", 0, matrix->get(i, j), EQUAL);
            }
        }
        delete matrix;
    }

    // Integer Size Matrix Constructor
    {
        Matrix<int> *matrix = nullptr;
        MatrixSize_t size = {3, 4};
        matrix = new Matrix<int>(size);
        Verify_Ptr("Matrix Memory Allocation", nullptr, matrix, NOT_EQUAL);
        Verify_UInt("Matrix Rows", size.rows, matrix->rows(), EQUAL);
        Verify_UInt("Matrix Columns", size.columns, matrix->columns(), EQUAL);
        for (MatrixLength_t i = 0; i < size.rows; i++) {
            for (MatrixLength_t j = 0; j < size.columns; j++) {
                Verify_Int("Matrix Element", 0, matrix->get(i, j), EQUAL);
            }
        }
        delete matrix;
    }

    // Integer Copy Matrix Constructor
    {
        Matrix<int> *matrix = nullptr;
        Matrix<int> *copy = nullptr;
        MatrixLength_t rows = 3;
        MatrixLength_t columns = 4;
        matrix = new Matrix<int>(rows, columns);
        for (MatrixLength_t i = 0; i < rows; i++) {
            for (MatrixLength_t j = 0; j < columns; j++) {
                matrix->set(i, j, i + j);
            }
        }
        copy = new Matrix<int>(*matrix);
        Verify_Ptr("Matrix Memory Allocation", nullptr, copy, NOT_EQUAL);
        Verify_UInt("Matrix Rows", rows, copy->rows(), EQUAL);
        Verify_UInt("Matrix Columns", columns, copy->columns(), EQUAL);
        for (MatrixLength_t i = 0; i < rows; i++) {
            for (MatrixLength_t j = 0; j < columns; j++) {
                Verify_Int("Matrix Element", i + j, copy->get(i, j), EQUAL);
            }
        }
        delete matrix;
        delete copy;
    }

    // Decimal Row Column Matrix Constructor
    {
        Matrix<double> *matrix = nullptr;
        MatrixLength_t rows = 3;
        MatrixLength_t columns = 4;
        matrix = new Matrix<double>(rows, columns);
        Verify_Ptr("Matrix Memory Allocation", nullptr, matrix, NOT_EQUAL);
        Verify_UInt("Matrix Rows", rows, matrix->rows(), EQUAL);
        Verify_UInt("Matrix Columns", columns, matrix->columns(), EQUAL);
        for (MatrixLength_t i = 0; i < rows; i++) {
            for (MatrixLength_t j = 0; j < columns; j++) {
                Verify_Double("Matrix Element", 0.0, matrix->get(i, j), EQUAL);
            }
        }
        delete matrix;
    }

    // Decimal Size Matrix Constructor
    {
        Matrix<double> *matrix = nullptr;
        MatrixSize_t size = {3, 4};
        matrix = new Matrix<double>(size);
        Verify_Ptr("Matrix Memory Allocation", nullptr, matrix, NOT_EQUAL);
        Verify_UInt("Matrix Rows", size.rows, matrix->rows(), EQUAL);
        Verify_UInt("Matrix Columns", size.columns, matrix->columns(), EQUAL);
        for (MatrixLength_t i = 0; i < size.rows; i++) {
            for (MatrixLength_t j = 0; j < size.columns; j++) {
                Verify_Double("Matrix Element", 0.0, matrix->get(i, j), EQUAL);
            }
        }
        delete matrix;
    }

    // Decimal Copy Matrix Constructor
    {
        Matrix<double> *matrix = nullptr;
        Matrix<double> *copy = nullptr;
        MatrixLength_t rows = 3;
        MatrixLength_t columns = 4;
        matrix = new Matrix<double>(rows, columns);
        for (MatrixLength_t i = 0; i < rows; i++) {
            for (MatrixLength_t j = 0; j < columns; j++) {
                matrix->set(i, j, 1.5 + i + j);
            }
        }
        copy = new Matrix<double>(*matrix);
        Verify_Ptr("Matrix Memory Allocation", nullptr, copy, NOT_EQUAL);
        Verify_UInt("Matrix Rows", rows, copy->rows(), EQUAL);
        Verify_UInt("Matrix Columns", columns, copy->columns(), EQUAL);
        for (MatrixLength_t i = 0; i < rows; i++) {
            for (MatrixLength_t j = 0; j < columns; j++) {
                Verify_Double("Matrix Element", 1.5 + i + j, copy->get(i, j), EQUAL);
            }
        }
        delete matrix;
        delete copy;
    }

    TestPostamble();
}

void Matrix_MultiMatrix_Operations() {
    const char *description = "Verify multi-matrix operations create result matrixs as expected";
    const char *for_set[] = {
        "Addition, Subtraction, Multiplication, Transposition",
        "Integer, Decimal"
    };
    const char *preconditions[] = {
        "Valid Sizes"
    };
    const char *results[] = {
        "Matrix Created with Expected Size and Values"
    };

    TestPreamble(description, for_set, preconditions, results);

    // Integer matrixs for most tests
    Matrix<int> int_matrix1(2, 2);
    int_matrix1.set(0, 0, 1);
    int_matrix1.set(0, 1, 2);
    int_matrix1.set(1, 0, 3);
    int_matrix1.set(1, 1, 4);

    Matrix<int> int_matrix2(2, 2);
    int_matrix2.set(0, 0, 5);
    int_matrix2.set(0, 1, 6);
    int_matrix2.set(1, 0, 7);
    int_matrix2.set(1, 1, 8);

    // Integer Matrix Addition
    {
        Matrix<int> result = int_matrix1 + int_matrix2;
        Verify_UInt("Matrix Rows", int_matrix1.rows(), result.rows(), EQUAL);
        Verify_UInt("Matrix Columns", int_matrix1.columns(), result.columns(), EQUAL);
        Verify_Int("Matrix Element", 6, result.get(0, 0), EQUAL);
        Verify_Int("Matrix Element", 8, result.get(0, 1), EQUAL);
        Verify_Int("Matrix Element", 10, result.get(1, 0), EQUAL);
        Verify_Int("Matrix Element", 12, result.get(1, 1), EQUAL);
    }

    // Integer Matrix Subtraction
    {
        Matrix<int> result = int_matrix1 - int_matrix2;
        Verify_UInt("Matrix Rows", int_matrix1.rows(), result.rows(), EQUAL);
        Verify_UInt("Matrix Columns", int_matrix1.columns(), result.columns(), EQUAL);
        Verify_Int("Matrix Element", -4, result.get(0, 0), EQUAL);
        Verify_Int("Matrix Element", -4, result.get(0, 1), EQUAL);
        Verify_Int("Matrix Element", -4, result.get(1, 0), EQUAL);
        Verify_Int("Matrix Element", -4, result.get(1, 1), EQUAL);
    }

    // Integer Matrix Multiplication
    {
        Matrix<int> int_mult_matrix1(3, 4);
        for (MatrixLength_t i = 0; i < 3; i++) {
            for (MatrixLength_t j = 0; j < 4; j++) {
                int_mult_matrix1.set(i, j, i + j);
            }
        }

        Matrix<int> int_mult_matrix2(4, 2);
        for (MatrixLength_t i = 0; i < 4; i++) {
            for (MatrixLength_t j = 0; j < 2; j++) {
                int_mult_matrix2.set(i, j, (i+1) * (j-3));
            }
        }
        
        Matrix<int> result = int_mult_matrix1 * int_mult_matrix2;
        Verify_UInt("Matrix Rows", int_mult_matrix1.rows(), result.rows(), EQUAL);
        Verify_UInt("Matrix Columns", int_mult_matrix2.columns(), result.columns(), EQUAL);
        Verify_Int("Matrix Element", -60, result.get(0, 0), EQUAL);
        Verify_Int("Matrix Element", -40, result.get(0, 1), EQUAL);
        Verify_Int("Matrix Element", -90, result.get(1, 0), EQUAL);
        Verify_Int("Matrix Element", -60, result.get(1, 1), EQUAL);
        Verify_Int("Matrix Element", -120, result.get(2, 0), EQUAL);
        Verify_Int("Matrix Element", -80, result.get(2, 1), EQUAL);
    }

    // Integer Matrix Transposition
    {
        Matrix<int> result = ~int_matrix1;
        Verify_UInt("Matrix Rows", int_matrix1.rows(), result.rows(), EQUAL);
        Verify_UInt("Matrix Columns", int_matrix1.columns(), result.columns(), EQUAL);
        Verify_Int("Matrix Element", 1, result.get(0, 0), EQUAL);
        Verify_Int("Matrix Element", 3, result.get(0, 1), EQUAL);
        Verify_Int("Matrix Element", 2, result.get(1, 0), EQUAL);
        Verify_Int("Matrix Element", 4, result.get(1, 1), EQUAL);
    }

    // Decimal matrixs for most tests
    Matrix<double> double_matrix1(2, 2);
    double_matrix1.set(0, 0, 1.5);
    double_matrix1.set(0, 1, 2.5);
    double_matrix1.set(1, 0, 3.5);
    double_matrix1.set(1, 1, 4.5);

    Matrix<double> double_matrix2(2, 2);
    double_matrix2.set(0, 0, 5.5);
    double_matrix2.set(0, 1, 6.5);
    double_matrix2.set(1, 0, 7.5);
    double_matrix2.set(1, 1, 8.5);

    // Decimal Matrix Addition
    {
        Matrix<double> result = double_matrix1 + double_matrix2;
        Verify_UInt("Matrix Rows", double_matrix1.rows(), result.rows(), EQUAL);
        Verify_UInt("Matrix Columns", double_matrix1.columns(), result.columns(), EQUAL);
        Verify_Double("Matrix Element", 7.0, result.get(0, 0), EQUAL);
        Verify_Double("Matrix Element", 9.0, result.get(0, 1), EQUAL);
        Verify_Double("Matrix Element", 11.0, result.get(1, 0), EQUAL);
        Verify_Double("Matrix Element", 13.0, result.get(1, 1), EQUAL);
    }

    // Decimal Matrix Subtraction
    {
        Matrix<double> result = double_matrix1 - double_matrix2;
        Verify_UInt("Matrix Rows", double_matrix1.rows(), result.rows(), EQUAL);
        Verify_UInt("Matrix Columns", double_matrix1.columns(), result.columns(), EQUAL);
        Verify_Double("Matrix Element", -4.0, result.get(0, 0), EQUAL);
        Verify_Double("Matrix Element", -4.0, result.get(0, 1), EQUAL);
        Verify_Double("Matrix Element", -4.0, result.get(1, 0), EQUAL);
        Verify_Double("Matrix Element", -4.0, result.get(1, 1), EQUAL);
    }

    // Decimal Matrix Multiplication
    {
        Matrix<double> double_mult_matrix1(3, 4);
        for (MatrixLength_t i = 0; i < 3; i++) {
            for (MatrixLength_t j = 0; j < 4; j++) {
                double_mult_matrix1.set(i, j, 1.5 + i + j);
            }
        }

        Matrix<double> double_mult_matrix2(4, 2);
        for (MatrixLength_t i = 0; i < 4; i++) {
            for (MatrixLength_t j = 0; j < 2; j++) {
                double_mult_matrix2.set(i, j, (i+1.0) * (j-3.0));
            }
        }
        
        Matrix<double> result = double_mult_matrix1 * double_mult_matrix2;
        Verify_UInt("Matrix Rows", double_mult_matrix1.rows(), result.rows(), EQUAL);
        Verify_UInt("Matrix Columns", double_mult_matrix2.columns(), result.columns(), EQUAL);
        Verify_Double("Matrix Element", -105.0, result.get(0, 0), EQUAL);
        Verify_Double("Matrix Element", -70.0, result.get(0, 1), EQUAL);
        Verify_Double("Matrix Element", -135.0, result.get(1, 0), EQUAL);
        Verify_Double("Matrix Element", -90.0, result.get(1, 1), EQUAL);
        Verify_Double("Matrix Element", -165.0, result.get(2, 0), EQUAL);
        Verify_Double("Matrix Element", -110.0, result.get(2, 1), EQUAL);
    }

    // Decimal Matrix Transposition
    {
        Matrix<double> result = ~double_matrix1;
        Verify_UInt("Matrix Rows", double_matrix1.columns(), result.rows(), EQUAL);
        Verify_UInt("Matrix Columns", double_matrix1.rows(), result.columns(), EQUAL);
        Verify_Double("Matrix Element", 1.5, result.get(0, 0), EQUAL);
        Verify_Double("Matrix Element", 3.5, result.get(0, 1), EQUAL);
        Verify_Double("Matrix Element", 2.5, result.get(1, 0), EQUAL);
        Verify_Double("Matrix Element", 4.5, result.get(1, 1), EQUAL);
    }

    TestPostamble();
}

void Matrix_MultiMatrix_Assignment_Operations() {
    const char *description = "Verify multi-matrix assignment operations modify matrixs as expected";
    const char *for_set[] = {
        "Addition, Subtraction, Multiplication, Assignment, Concatenation",
        "Integer, Decimal"
    };
    const char *preconditions[] = {
        "Valid Sizes"
    };
    const char *results[] = {
        "Matrix Set with Expected Size and Values"
    };

    TestPreamble(description, for_set, preconditions, results);

    // Integer matrixs for most tests
    Matrix<int> int_matrix1(2, 2);
    int_matrix1.set(0, 0, 1);
    int_matrix1.set(0, 1, 2);
    int_matrix1.set(1, 0, 3);
    int_matrix1.set(1, 1, 4);

    Matrix<int> int_matrix2(2, 2);
    int_matrix2.set(0, 0, 5);
    int_matrix2.set(0, 1, 6);
    int_matrix2.set(1, 0, 7);
    int_matrix2.set(1, 1, 8);

    // Integer Matrix Addition
    {
        Matrix<int> int_copy = int_matrix1;
        int_copy += int_matrix2;
        Verify_UInt("Matrix Rows", int_matrix1.rows(), int_copy.rows(), EQUAL);
        Verify_UInt("Matrix Columns", int_matrix1.columns(), int_copy.columns(), EQUAL);
        Verify_Int("Matrix Element", 6, int_copy.get(0, 0), EQUAL);
        Verify_Int("Matrix Element", 8, int_copy.get(0, 1), EQUAL);
        Verify_Int("Matrix Element", 10, int_copy.get(1, 0), EQUAL);
        Verify_Int("Matrix Element", 12, int_copy.get(1, 1), EQUAL);
    }

    // Integer Matrix Subtraction
    {
        Matrix<int> int_copy = int_matrix1;
        int_copy -= int_matrix2;
        Verify_UInt("Matrix Rows", int_matrix1.rows(), int_copy.rows(), EQUAL);
        Verify_UInt("Matrix Columns", int_matrix1.columns(), int_copy.columns(), EQUAL);
        Verify_Int("Matrix Element", -4, int_copy.get(0, 0), EQUAL);
        Verify_Int("Matrix Element", -4, int_copy.get(0, 1), EQUAL);
        Verify_Int("Matrix Element", -4, int_copy.get(1, 0), EQUAL);
        Verify_Int("Matrix Element", -4, int_copy.get(1, 1), EQUAL);
    }

    // Integer Matrix Multiplication
    {
        Matrix<int> int_mult_matrix1(3, 4);
        for (MatrixLength_t i = 0; i < 3; i++) {
            for (MatrixLength_t j = 0; j < 4; j++) {
                int_mult_matrix1.set(i, j, i + j);
            }
        }

        Matrix<int> int_mult_matrix2(4, 2);
        for (MatrixLength_t i = 0; i < 4; i++) {
            for (MatrixLength_t j = 0; j < 2; j++) {
                int_mult_matrix2.set(i, j, (i+1) * (j-3));
            }
        }
        
        MatrixLength_t original_rows = int_mult_matrix1.rows();
        int_mult_matrix1 *= int_mult_matrix2;
        Verify_UInt("Matrix Rows", original_rows, int_mult_matrix1.rows(), EQUAL);
        Verify_UInt("Matrix Columns", int_mult_matrix2.columns(), int_mult_matrix1.columns(), EQUAL);
        Verify_Int("Matrix Element", -60, int_mult_matrix1.get(0, 0), EQUAL);
        Verify_Int("Matrix Element", -40, int_mult_matrix1.get(0, 1), EQUAL);
        Verify_Int("Matrix Element", -90, int_mult_matrix1.get(1, 0), EQUAL);
        Verify_Int("Matrix Element", -60, int_mult_matrix1.get(1, 1), EQUAL);
        Verify_Int("Matrix Element", -120, int_mult_matrix1.get(2, 0), EQUAL);
        Verify_Int("Matrix Element", -80, int_mult_matrix1.get(2, 1), EQUAL);
    }

    // Integer Matrix Assignment
    {
        Matrix<int> int_copy(int_matrix1.size());
        int_copy = int_matrix1;
        Verify_UInt("Matrix Rows", int_matrix1.rows(), int_copy.rows(), EQUAL);
        Verify_UInt("Matrix Columns", int_matrix1.columns(), int_copy.columns(), EQUAL);
        Verify_Int("Matrix Element", int_matrix1.get(0, 0), int_copy.get(0, 0), EQUAL);
        Verify_Int("Matrix Element", int_matrix1.get(0, 1), int_copy.get(0, 1), EQUAL);
        Verify_Int("Matrix Element", int_matrix1.get(1, 0), int_copy.get(1, 0), EQUAL);
        Verify_Int("Matrix Element", int_matrix1.get(1, 1), int_copy.get(1, 1), EQUAL);
    }

    // Integer Matrix Concatenation
    {
        int_matrix1 << int_matrix2;
        Verify_UInt("Matrix Rows", int_matrix1.rows(), 2u, EQUAL);
        Verify_UInt("Matrix Columns", (unsigned long)int_matrix1.columns(), 4u, EQUAL);
        Verify_Int("Matrix Element", 1, int_matrix1.get(0, 0), EQUAL);
        Verify_Int("Matrix Element", 2, int_matrix1.get(0, 1), EQUAL);
        Verify_Int("Matrix Element", 5, int_matrix1.get(0, 2), EQUAL);
        Verify_Int("Matrix Element", 6, int_matrix1.get(0, 3), EQUAL);
        Verify_Int("Matrix Element", 3, int_matrix1.get(1, 0), EQUAL);
        Verify_Int("Matrix Element", 4, int_matrix1.get(1, 1), EQUAL);
        Verify_Int("Matrix Element", 7, int_matrix1.get(1, 2), EQUAL);
        Verify_Int("Matrix Element", 8, int_matrix1.get(1, 3), EQUAL);
    }

    // Decimal matrixs for most tests
    Matrix<double> double_matrix1(2, 2);
    double_matrix1.set(0, 0, 1.5);
    double_matrix1.set(0, 1, 2.5);
    double_matrix1.set(1, 0, 3.5);
    double_matrix1.set(1, 1, 4.5);

    Matrix<double> double_matrix2(2, 2);
    double_matrix2.set(0, 0, 5.5);
    double_matrix2.set(0, 1, 6.5);
    double_matrix2.set(1, 0, 7.5);
    double_matrix2.set(1, 1, 8.5);

    // Decimal Matrix Addition
    {
        Matrix<double> copy = double_matrix1;
        copy += double_matrix2;
        Verify_UInt("Matrix Rows", double_matrix1.rows(), copy.rows(), EQUAL);
        Verify_UInt("Matrix Columns", double_matrix1.columns(), copy.columns(), EQUAL);
        Verify_Double("Matrix Element", 7.0, copy.get(0, 0), EQUAL);
        Verify_Double("Matrix Element", 9.0, copy.get(0, 1), EQUAL);
        Verify_Double("Matrix Element", 11.0, copy.get(1, 0), EQUAL);
        Verify_Double("Matrix Element", 13.0, copy.get(1, 1), EQUAL);
    }

    // Decimal Matrix Subtraction
    {
        Matrix<double> copy = double_matrix1;
        copy -= double_matrix2;
        Verify_UInt("Matrix Rows", double_matrix1.rows(), copy.rows(), EQUAL);
        Verify_UInt("Matrix Columns", double_matrix1.columns(), copy.columns(), EQUAL);
        Verify_Double("Matrix Element", -4.0, copy.get(0, 0), EQUAL);
        Verify_Double("Matrix Element", -4.0, copy.get(0, 1), EQUAL);
        Verify_Double("Matrix Element", -4.0, copy.get(1, 0), EQUAL);
        Verify_Double("Matrix Element", -4.0, copy.get(1, 1), EQUAL);
    }

    // Decimal Matrix Multiplication
    {
        Matrix<double> double_mult_matrix1(3, 4);
        for (MatrixLength_t i = 0; i < 3; i++) {
            for (MatrixLength_t j = 0; j < 4; j++) {
                double_mult_matrix1.set(i, j, 1.5 + i + j);
            }
        }

        Matrix<double> double_mult_matrix2(4, 2);
        for (MatrixLength_t i = 0; i < 4; i++) {
            for (MatrixLength_t j = 0; j < 2; j++) {
                double_mult_matrix2.set(i, j, (i+1.0) * (j-3.0));
            }
        }
        
        MatrixLength_t original_rows = double_mult_matrix1.rows();
        double_mult_matrix1 *= double_mult_matrix2;
        Verify_UInt("Matrix Rows", original_rows, double_mult_matrix1.rows(), EQUAL);
        Verify_UInt("Matrix Columns", double_mult_matrix2.columns(), double_mult_matrix1.columns(), EQUAL);
        Verify_Double("Matrix Element", -105.0, double_mult_matrix1.get(0, 0), EQUAL);
        Verify_Double("Matrix Element", -70.0, double_mult_matrix1.get(0, 1), EQUAL);
        Verify_Double("Matrix Element", -135.0, double_mult_matrix1.get(1, 0), EQUAL);
        Verify_Double("Matrix Element", -90.0, double_mult_matrix1.get(1, 1), EQUAL);
        Verify_Double("Matrix Element", -165.0, double_mult_matrix1.get(2, 0), EQUAL);
        Verify_Double("Matrix Element", -110.0, double_mult_matrix1.get(2, 1), EQUAL);
    }

    // Decimal Matrix Assignment
    {
        Matrix<double> double_copy(double_matrix1.size());
        double_copy = double_matrix1;
        Verify_UInt("Matrix Rows", double_matrix1.rows(), double_copy.rows(), EQUAL);
        Verify_UInt("Matrix Columns", double_matrix1.columns(), double_copy.columns(), EQUAL);
        Verify_Double("Matrix Element", double_matrix1.get(0, 0), double_copy.get(0, 0), EQUAL);
        Verify_Double("Matrix Element", double_matrix1.get(0, 1), double_copy.get(0, 1), EQUAL);
        Verify_Double("Matrix Element", double_matrix1.get(1, 0), double_copy.get(1, 0), EQUAL);
        Verify_Double("Matrix Element", double_matrix1.get(1, 1), double_copy.get(1, 1), EQUAL);
    }

    // Decimal Matrix Concatenation
    {
        double_matrix1 << double_matrix2;
        Verify_UInt("Matrix Rows", double_matrix1.rows(), 2u, EQUAL);
        Verify_UInt("Matrix Columns", double_matrix1.columns(), 4u, EQUAL);
        Verify_Double("Matrix Element", 1.5, double_matrix1.get(0, 0), EQUAL);
        Verify_Double("Matrix Element", 2.5, double_matrix1.get(0, 1), EQUAL);
        Verify_Double("Matrix Element", 5.5, double_matrix1.get(0, 2), EQUAL);
        Verify_Double("Matrix Element", 6.5, double_matrix1.get(0, 3), EQUAL);
        Verify_Double("Matrix Element", 3.5, double_matrix1.get(1, 0), EQUAL);
        Verify_Double("Matrix Element", 4.5, double_matrix1.get(1, 1), EQUAL);
        Verify_Double("Matrix Element", 7.5, double_matrix1.get(1, 2), EQUAL);
        Verify_Double("Matrix Element", 8.5, double_matrix1.get(1, 3), EQUAL);
    }

    TestPostamble();
}

void Matrix_MultiMatrix_Element_Operations() {
    const char *description = "Verify matrix element operations modify matrixs as expected";
    const char *for_set[] = {
        "Addition, Subtraction, Multiplication, Division, Exponentiation",
        "Integer, Decimal"
    };
    const char *preconditions[] = {
        "Valid Sizes"
    };
    const char *results[] = {
        "Matrix Set with Expected Size and Values"
    };

    TestPreamble(description, for_set, preconditions, results);

    // Integer matrixs for most tests
    Matrix<int> int_matrix(2, 2);
    int_matrix.set(0, 0, 1);
    int_matrix.set(0, 1, 2);
    int_matrix.set(1, 0, 3);
    int_matrix.set(1, 1, 4);

    // Integer Element Addition
    {
        Matrix<int> result = int_matrix + 2;
        Verify_UInt("Matrix Rows", int_matrix.rows(), result.rows(), EQUAL);
        Verify_UInt("Matrix Columns", int_matrix.columns(), result.columns(), EQUAL);
        Verify_Int("Matrix Element", 3, result.get(0, 0), EQUAL);
        Verify_Int("Matrix Element", 4, result.get(0, 1), EQUAL);
        Verify_Int("Matrix Element", 5, result.get(1, 0), EQUAL);
        Verify_Int("Matrix Element", 6, result.get(1, 1), EQUAL);
    }

    // Integer Element Subtraction
    {
        Matrix<int> result = int_matrix - 2;
        Verify_UInt("Matrix Rows", int_matrix.rows(), result.rows(), EQUAL);
        Verify_UInt("Matrix Columns", int_matrix.columns(), result.columns(), EQUAL);
        Verify_Int("Matrix Element", -1, result.get(0, 0), EQUAL);
        Verify_Int("Matrix Element", 0, result.get(0, 1), EQUAL);
        Verify_Int("Matrix Element", 1, result.get(1, 0), EQUAL);
        Verify_Int("Matrix Element", 2, result.get(1, 1), EQUAL);
    }

    // Integer Element Multiplication
    {
        Matrix<int> result = int_matrix * 2;
        Verify_UInt("Matrix Rows", int_matrix.rows(), result.rows(), EQUAL);
        Verify_UInt("Matrix Columns", int_matrix.columns(), result.columns(), EQUAL);
        Verify_Int("Matrix Element", 2, result.get(0, 0), EQUAL);
        Verify_Int("Matrix Element", 4, result.get(0, 1), EQUAL);
        Verify_Int("Matrix Element", 6, result.get(1, 0), EQUAL);
        Verify_Int("Matrix Element", 8, result.get(1, 1), EQUAL);
    }

    // Integer Element Division
    {
        Matrix<int> result = int_matrix / 2;
        Verify_UInt("Matrix Rows", int_matrix.rows(), result.rows(), EQUAL);
        Verify_UInt("Matrix Columns", int_matrix.columns(), result.columns(), EQUAL);
        Verify_Int("Matrix Element", 0, result.get(0, 0), EQUAL);
        Verify_Int("Matrix Element", 1, result.get(0, 1), EQUAL);
        Verify_Int("Matrix Element", 1, result.get(1, 0), EQUAL);
        Verify_Int("Matrix Element", 2, result.get(1, 1), EQUAL);
    }

    // Integer Element Exponentiation
    {
        Matrix<int> result = int_matrix ^ 2;
        Verify_UInt("Matrix Rows", int_matrix.rows(), result.rows(), EQUAL);
        Verify_UInt("Matrix Columns", int_matrix.columns(), result.columns(), EQUAL);
        Verify_Int("Matrix Element", 1, result.get(0, 0), EQUAL);
        Verify_Int("Matrix Element", 4, result.get(0, 1), EQUAL);
        Verify_Int("Matrix Element", 9, result.get(1, 0), EQUAL);
        Verify_Int("Matrix Element", 16, result.get(1, 1), EQUAL);
    }

    // Decimal matrixs for most tests
    Matrix<double> double_matrix(2, 2);
    double_matrix.set(0, 0, 1.5);
    double_matrix.set(0, 1, 2.5);
    double_matrix.set(1, 0, 3.5);
    double_matrix.set(1, 1, 4.5);

    // Decimal Element Addition
    {
        Matrix<double> result = double_matrix + 2.5;
        Verify_UInt("Matrix Rows", double_matrix.rows(), result.rows(), EQUAL);
        Verify_UInt("Matrix Columns", double_matrix.columns(), result.columns(), EQUAL);
        Verify_Double("Matrix Element", 4.0, result.get(0, 0), EQUAL);
        Verify_Double("Matrix Element", 5.0, result.get(0, 1), EQUAL);
        Verify_Double("Matrix Element", 6.0, result.get(1, 0), EQUAL);
        Verify_Double("Matrix Element", 7.0, result.get(1, 1), EQUAL);
    }

    // Decimal Element Subtraction
    {
        Matrix<double> result = double_matrix - 2.5;
        Verify_UInt("Matrix Rows", double_matrix.rows(), result.rows(), EQUAL);
        Verify_UInt("Matrix Columns", double_matrix.columns(), result.columns(), EQUAL);
        Verify_Double("Matrix Element", -1.0, result.get(0, 0), EQUAL);
        Verify_Double("Matrix Element", 0.0, result.get(0, 1), EQUAL);
        Verify_Double("Matrix Element", 1.0, result.get(1, 0), EQUAL);
        Verify_Double("Matrix Element", 2.0, result.get(1, 1), EQUAL);
    }

    // Decimal Element Multiplication
    {
        Matrix<double> result = double_matrix * 2.5;
        Verify_UInt("Matrix Rows", double_matrix.rows(), result.rows(), EQUAL);
        Verify_UInt("Matrix Columns", double_matrix.columns(), result.columns(), EQUAL);
        Verify_Double("Matrix Element", 3.75, result.get(0, 0), EQUAL);
        Verify_Double("Matrix Element", 6.25, result.get(0, 1), EQUAL);
        Verify_Double("Matrix Element", 8.75, result.get(1, 0), EQUAL);
        Verify_Double("Matrix Element", 11.25, result.get(1, 1), EQUAL);
    }

    // Decimal Element Division
    {
        Matrix<double> result = double_matrix / 2.5;
        Verify_UInt("Matrix Rows", double_matrix.rows(), result.rows(), EQUAL);
        Verify_UInt("Matrix Columns", double_matrix.columns(), result.columns(), EQUAL);
        Verify_Double("Matrix Element", 0.6, result.get(0, 0), EQUAL);
        Verify_Double("Matrix Element", 1.0, result.get(0, 1), EQUAL);
        Verify_Double("Matrix Element", 1.4, result.get(1, 0), EQUAL);
        Verify_Double("Matrix Element", 1.8, result.get(1, 1), EQUAL);
    }

    // Decimal Element Exponentiation
    {
        Matrix<double> result = double_matrix ^ 2.0;
        Verify_UInt("Matrix Rows", double_matrix.rows(), result.rows(), EQUAL);
        Verify_UInt("Matrix Columns", double_matrix.columns(), result.columns(), EQUAL);
        Verify_Double("Matrix Element", 2.25, result.get(0, 0), EQUAL);
        Verify_Double("Matrix Element", 6.25, result.get(0, 1), EQUAL);
        Verify_Double("Matrix Element", 12.25, result.get(1, 0), EQUAL);
        Verify_Double("Matrix Element", 20.25, result.get(1, 1), EQUAL);
    }

    TestPostamble();
}

void Matrix_MultiMatrix_Element_Assignment_Operations() {
    const char *description = "Verify matrix element operations modify matrixs as expected";
    const char *for_set[] = {
        "Addition, Subtraction, Multiplication, Division, Exponentiation",
        "Integer, Decimal"
    };
    const char *preconditions[] = {
        "Valid Sizes"
    };
    const char *results[] = {
        "Matrix Set with Expected Size and Values"
    };

    TestPreamble(description, for_set, preconditions, results);

    // Integer matrixs for most tests
    Matrix<int> int_matrix(2, 2);
    int_matrix.set(0, 0, 1);
    int_matrix.set(0, 1, 2);
    int_matrix.set(1, 0, 3);
    int_matrix.set(1, 1, 4);

    // Integer Element Addition
    {
        Matrix<int> copy_int = int_matrix;
        copy_int += 2;
        Verify_UInt("Matrix Rows", int_matrix.rows(), copy_int.rows(), EQUAL);
        Verify_UInt("Matrix Columns", int_matrix.columns(), copy_int.columns(), EQUAL);
        Verify_Int("Matrix Element", 3, copy_int.get(0, 0), EQUAL);
        Verify_Int("Matrix Element", 4, copy_int.get(0, 1), EQUAL);
        Verify_Int("Matrix Element", 5, copy_int.get(1, 0), EQUAL);
        Verify_Int("Matrix Element", 6, copy_int.get(1, 1), EQUAL);
    }

    // Integer Element Subtraction
    {
        Matrix<int> copy_int = int_matrix;
        copy_int -= 2;
        Verify_UInt("Matrix Rows", int_matrix.rows(), copy_int.rows(), EQUAL);
        Verify_UInt("Matrix Columns", int_matrix.columns(), copy_int.columns(), EQUAL);
        Verify_Int("Matrix Element", -1, copy_int.get(0, 0), EQUAL);
        Verify_Int("Matrix Element", 0, copy_int.get(0, 1), EQUAL);
        Verify_Int("Matrix Element", 1, copy_int.get(1, 0), EQUAL);
        Verify_Int("Matrix Element", 2, copy_int.get(1, 1), EQUAL);
    }

    // Integer Element Multiplication
    {
        Matrix<int> copy_int = int_matrix;
        copy_int *= 2;
        Verify_UInt("Matrix Rows", int_matrix.rows(), copy_int.rows(), EQUAL);
        Verify_UInt("Matrix Columns", int_matrix.columns(), copy_int.columns(), EQUAL);
        Verify_Int("Matrix Element", 2, copy_int.get(0, 0), EQUAL);
        Verify_Int("Matrix Element", 4, copy_int.get(0, 1), EQUAL);
        Verify_Int("Matrix Element", 6, copy_int.get(1, 0), EQUAL);
        Verify_Int("Matrix Element", 8, copy_int.get(1, 1), EQUAL);
    }

    // Integer Element Division
    {
        Matrix<int> copy_int = int_matrix;
        copy_int /= 2;
        Verify_UInt("Matrix Rows", int_matrix.rows(), copy_int.rows(), EQUAL);
        Verify_UInt("Matrix Columns", int_matrix.columns(), copy_int.columns(), EQUAL);
        Verify_Int("Matrix Element", 0, copy_int.get(0, 0), EQUAL);
        Verify_Int("Matrix Element", 1, copy_int.get(0, 1), EQUAL);
        Verify_Int("Matrix Element", 1, copy_int.get(1, 0), EQUAL);
        Verify_Int("Matrix Element", 2, copy_int.get(1, 1), EQUAL);
    }

    // Integer Element Exponentiation
    {
        Matrix<int> copy_int = int_matrix;
        copy_int ^= 2;
        Verify_UInt("Matrix Rows", int_matrix.rows(), copy_int.rows(), EQUAL);
        Verify_UInt("Matrix Columns", int_matrix.columns(), copy_int.columns(), EQUAL);
        Verify_Int("Matrix Element", 1, copy_int.get(0, 0), EQUAL);
        Verify_Int("Matrix Element", 4, copy_int.get(0, 1), EQUAL);
        Verify_Int("Matrix Element", 9, copy_int.get(1, 0), EQUAL);
        Verify_Int("Matrix Element", 16, copy_int.get(1, 1), EQUAL);
    }

    // Decimal matrixs for most tests
    Matrix<double> double_matrix(2, 2);
    double_matrix.set(0, 0, 1.5);
    double_matrix.set(0, 1, 2.5);
    double_matrix.set(1, 0, 3.5);
    double_matrix.set(1, 1, 4.5);

    // Decimal Element Addition
    {
        Matrix<double> copy_double = double_matrix;
        copy_double += 2.5;
        Verify_UInt("Matrix Rows", double_matrix.rows(), copy_double.rows(), EQUAL);
        Verify_UInt("Matrix Columns", double_matrix.columns(), copy_double.columns(), EQUAL);
        Verify_Double("Matrix Element", 4.0, copy_double.get(0, 0), EQUAL);
        Verify_Double("Matrix Element", 5.0, copy_double.get(0, 1), EQUAL);
        Verify_Double("Matrix Element", 6.0, copy_double.get(1, 0), EQUAL);
        Verify_Double("Matrix Element", 7.0, copy_double.get(1, 1), EQUAL);
    }

    // Decimal Element Subtraction
    {
        Matrix<double> copy_double = double_matrix;
        copy_double -= 2.5;
        Verify_UInt("Matrix Rows", double_matrix.rows(), copy_double.rows(), EQUAL);
        Verify_UInt("Matrix Columns", double_matrix.columns(), copy_double.columns(), EQUAL);
        Verify_Double("Matrix Element", -1.0, copy_double.get(0, 0), EQUAL);
        Verify_Double("Matrix Element", 0.0, copy_double.get(0, 1), EQUAL);
        Verify_Double("Matrix Element", 1.0, copy_double.get(1, 0), EQUAL);
        Verify_Double("Matrix Element", 2.0, copy_double.get(1, 1), EQUAL);
    }

    // Decimal Element Multiplication
    {
        Matrix<double> copy_double = double_matrix;
        copy_double *= 2.5;
        Verify_UInt("Matrix Rows", double_matrix.rows(), copy_double.rows(), EQUAL);
        Verify_UInt("Matrix Columns", double_matrix.columns(), copy_double.columns(), EQUAL);
        Verify_Double("Matrix Element", 3.75, copy_double.get(0, 0), EQUAL);
        Verify_Double("Matrix Element", 6.25, copy_double.get(0, 1), EQUAL);
        Verify_Double("Matrix Element", 8.75, copy_double.get(1, 0), EQUAL);
        Verify_Double("Matrix Element", 11.25, copy_double.get(1, 1), EQUAL);
    }

    // Decimal Element Division
    {
        Matrix<double> copy_double = double_matrix;
        copy_double /= 2.5;
        Verify_UInt("Matrix Rows", double_matrix.rows(), copy_double.rows(), EQUAL);
        Verify_UInt("Matrix Columns", double_matrix.columns(), copy_double.columns(), EQUAL);
        Verify_Double("Matrix Element", 0.6, copy_double.get(0, 0), EQUAL);
        Verify_Double("Matrix Element", 1.0, copy_double.get(0, 1), EQUAL);
        Verify_Double("Matrix Element", 1.4, copy_double.get(1, 0), EQUAL);
        Verify_Double("Matrix Element", 1.8, copy_double.get(1, 1), EQUAL);
    }

    // Decimal Element Exponentiation
    {
        Matrix<double> copy_double = double_matrix;
        copy_double ^= 2.0;
        Verify_UInt("Matrix Rows", double_matrix.rows(), copy_double.rows(), EQUAL);
        Verify_UInt("Matrix Columns", double_matrix.columns(), copy_double.columns(), EQUAL);
        Verify_Double("Matrix Element", 2.25, copy_double.get(0, 0), EQUAL);
        Verify_Double("Matrix Element", 6.25, copy_double.get(0, 1), EQUAL);
        Verify_Double("Matrix Element", 12.25, copy_double.get(1, 0), EQUAL);
        Verify_Double("Matrix Element", 20.25, copy_double.get(1, 1), EQUAL);
    }

    TestPostamble();
}

void Matrix_State() {
    const char *description = "Verify matrix state methods return expected values";
    const char *for_set[] = {
        "isZero, isOne, length, size, rows, columns"
    };
    const char *preconditions[] = {
        "Valid Sizes"
    };
    const char *results[] = {
        "Matrix Set with Expected Size and Values"
    };

    TestPreamble(description, for_set, preconditions, results);

    // Integer matrix
    MatrixLength_t rows = 4;
    MatrixLength_t columns = 3;
    Matrix<int> zero_matrix(rows, columns);
    Matrix<int> one_matrix(rows, columns);
    one_matrix += 1;
    Matrix<int> matrix(rows, columns);
    for (MatrixLength_t i = 0; i < rows; i++) {
        for (MatrixLength_t j = 0; j < columns; j++) {
            matrix.set(i, j, i * j);
        }
    }

    // Integer Matrix isZero
    {
        Verify("Zero Matrix isZero", zero_matrix.isZero(), true, EQUAL);
        Verify("One Matrix isZero", one_matrix.isZero(), false, EQUAL);
        Verify("Random Matrix isZero", matrix.isZero(), false, EQUAL);
    }

    // Integer Matrix isOne
    {
        Verify("Zero Matrix isOne", zero_matrix.isOne(), false, EQUAL);
        Verify("One Matrix isOne", one_matrix.isOne(), true, EQUAL);
        Verify("Random Matrix isOne", matrix.isOne(), false, EQUAL);
    }

    // Integer Matrix length
    {
        Verify_UInt("Zero Matrix length", zero_matrix.length(), rows, EQUAL);
        Verify_UInt("One Matrix length", one_matrix.length(), rows, EQUAL);
        Verify_UInt("Random Matrix length", matrix.length(), rows, EQUAL);
    }

    // Integer Matrix size
    {
        MatrixSize_t expected_size = {rows, columns};
        Verify_Memory("Zero Matrix size", zero_matrix.size(), &expected_size, sizeof(MatrixSize_t));
        Verify_Memory("One Matrix size", one_matrix.size(), &expected_size, sizeof(MatrixSize_t));
        Verify_Memory("Random Matrix size", matrix.size(), &expected_size, sizeof(MatrixSize_t));
    }

    // Integer Matrix rows
    {
        Verify_UInt("Zero Matrix rows", zero_matrix.rows(), rows, EQUAL);
        Verify_UInt("One Matrix rows", one_matrix.rows(), rows, EQUAL);
        Verify_UInt("Random Matrix rows", matrix.rows(), rows, EQUAL);
    }

    // Integer Matrix columns
    {
        Verify_UInt("Zero Matrix columns", zero_matrix.columns(), columns, EQUAL);
        Verify_UInt("One Matrix columns", one_matrix.columns(), columns, EQUAL);
        Verify_UInt("Random Matrix columns", matrix.columns(), columns, EQUAL);
    }

    TestPostamble();
}

void setup() {
    Serial.begin(115200);
    delay(3000);
    assert(Serial);

    Matrix_Constructor();
    Matrix_MultiMatrix_Operations();
    Matrix_MultiMatrix_Assignment_Operations();
    Matrix_MultiMatrix_Element_Operations();
    Matrix_MultiMatrix_Element_Assignment_Operations();
    Matrix_State();
}

void loop() {
    while (true) continue;
}
