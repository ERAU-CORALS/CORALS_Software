/**
 ********************************************************************************
 * @file    constructor.cpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Unit Test of Tensor Constructor
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

#include "Tensor.tpp"
using namespace DataStructures;

void Tensor_Constructor() {
    const char *description = "Verify Tensor Constructor creates a Tensor object";
    const char *for_set[] = {
        "Row Column Tensor, Size Tensor, Copy Tensor",
        "Integer, Decimal"
    };
    const char *preconditions[] = {
        "Valid Row Number",
        "Valid Column Number",
        "Valid Size Structure",
        "Valid Tensor to Copy"
    };
    const char *results[] = {
        "Tensor Created and Zeroed with Expected Size",
        "Tensor Created and Zeroed with Expected Size",
        "Tensor Created and Copied with Expected Size",
    };

    TestPreamble(description, for_set, preconditions, results);

    // Integer Row Column Tensor Constructor
    {
        Tensor<int> *tensor = nullptr;
        TensorLength_t rows = 3;
        TensorLength_t columns = 4;
        tensor = new Tensor<int>(rows, columns);
        Verify_Ptr("Tensor Memory Allocation", nullptr, tensor, NOT_EQUAL);
        Verify_UInt("Tensor Rows", rows, tensor->rows(), EQUAL);
        Verify_UInt("Tensor Columns", columns, tensor->columns(), EQUAL);
        for (TensorLength_t i = 0; i < rows; i++) {
            for (TensorLength_t j = 0; j < columns; j++) {
                Verify_Int("Tensor Element", 0, tensor->get(i, j), EQUAL);
            }
        }
        delete tensor;
    }

    // Integer Size Tensor Constructor
    {
        Tensor<int> *tensor = nullptr;
        TensorSize_t size = {3, 4};
        tensor = new Tensor<int>(size);
        Verify_Ptr("Tensor Memory Allocation", nullptr, tensor, NOT_EQUAL);
        Verify_UInt("Tensor Rows", size.rows, tensor->rows(), EQUAL);
        Verify_UInt("Tensor Columns", size.columns, tensor->columns(), EQUAL);
        for (TensorLength_t i = 0; i < size.rows; i++) {
            for (TensorLength_t j = 0; j < size.columns; j++) {
                Verify_Int("Tensor Element", 0, tensor->get(i, j), EQUAL);
            }
        }
        delete tensor;
    }

    // Integer Copy Tensor Constructor
    {
        Tensor<int> *tensor = nullptr;
        Tensor<int> *copy = nullptr;
        TensorLength_t rows = 3;
        TensorLength_t columns = 4;
        tensor = new Tensor<int>(rows, columns);
        for (TensorLength_t i = 0; i < rows; i++) {
            for (TensorLength_t j = 0; j < columns; j++) {
                tensor->set(i, j, i + j);
            }
        }
        copy = new Tensor<int>(*tensor);
        Verify_Ptr("Tensor Memory Allocation", nullptr, copy, NOT_EQUAL);
        Verify_UInt("Tensor Rows", rows, copy->rows(), EQUAL);
        Verify_UInt("Tensor Columns", columns, copy->columns(), EQUAL);
        for (TensorLength_t i = 0; i < rows; i++) {
            for (TensorLength_t j = 0; j < columns; j++) {
                Verify_Int("Tensor Element", i + j, copy->get(i, j), EQUAL);
            }
        }
        delete tensor;
        delete copy;
    }

    // Decimal Row Column Tensor Constructor
    {
        Tensor<double> *tensor = nullptr;
        TensorLength_t rows = 3;
        TensorLength_t columns = 4;
        tensor = new Tensor<double>(rows, columns);
        Verify_Ptr("Tensor Memory Allocation", nullptr, tensor, NOT_EQUAL);
        Verify_UInt("Tensor Rows", rows, tensor->rows(), EQUAL);
        Verify_UInt("Tensor Columns", columns, tensor->columns(), EQUAL);
        for (TensorLength_t i = 0; i < rows; i++) {
            for (TensorLength_t j = 0; j < columns; j++) {
                Verify_Double("Tensor Element", 0.0, tensor->get(i, j), EQUAL);
            }
        }
        delete tensor;
    }

    // Decimal Size Tensor Constructor
    {
        Tensor<double> *tensor = nullptr;
        TensorSize_t size = {3, 4};
        tensor = new Tensor<double>(size);
        Verify_Ptr("Tensor Memory Allocation", nullptr, tensor, NOT_EQUAL);
        Verify_UInt("Tensor Rows", size.rows, tensor->rows(), EQUAL);
        Verify_UInt("Tensor Columns", size.columns, tensor->columns(), EQUAL);
        for (TensorLength_t i = 0; i < size.rows; i++) {
            for (TensorLength_t j = 0; j < size.columns; j++) {
                Verify_Double("Tensor Element", 0.0, tensor->get(i, j), EQUAL);
            }
        }
        delete tensor;
    }

    // Decimal Copy Tensor Constructor
    {
        Tensor<double> *tensor = nullptr;
        Tensor<double> *copy = nullptr;
        TensorLength_t rows = 3;
        TensorLength_t columns = 4;
        tensor = new Tensor<double>(rows, columns);
        for (TensorLength_t i = 0; i < rows; i++) {
            for (TensorLength_t j = 0; j < columns; j++) {
                tensor->set(i, j, 1.5 + i + j);
            }
        }
        copy = new Tensor<double>(*tensor);
        Verify_Ptr("Tensor Memory Allocation", nullptr, copy, NOT_EQUAL);
        Verify_UInt("Tensor Rows", rows, copy->rows(), EQUAL);
        Verify_UInt("Tensor Columns", columns, copy->columns(), EQUAL);
        for (TensorLength_t i = 0; i < rows; i++) {
            for (TensorLength_t j = 0; j < columns; j++) {
                Verify_Double("Tensor Element", 1.5 + i + j, copy->get(i, j), EQUAL);
            }
        }
        delete tensor;
        delete copy;
    }

    TestPostamble();
}

void Tensor_MultiTensor_Operations() {
    const char *description = "Verify multi-tensor operations create result tensors as expected";
    const char *for_set[] = {
        "Addition, Subtraction, Multiplication, Transposition",
        "Integer, Decimal"
    };
    const char *preconditions[] = {
        "Valid Sizes"
    };
    const char *results[] = {
        "Tensor Created with Expected Size and Values"
    };

    TestPreamble(description, for_set, preconditions, results);

    // Integer tensors for most tests
    Tensor<int> int_tensor1(2, 2);
    int_tensor1.set(0, 0, 1);
    int_tensor1.set(0, 1, 2);
    int_tensor1.set(1, 0, 3);
    int_tensor1.set(1, 1, 4);

    Tensor<int> int_tensor2(2, 2);
    int_tensor2.set(0, 0, 5);
    int_tensor2.set(0, 1, 6);
    int_tensor2.set(1, 0, 7);
    int_tensor2.set(1, 1, 8);

    // Integer Tensor Addition
    {
        Tensor<int> result = int_tensor1 + int_tensor2;
        Verify_UInt("Tensor Rows", int_tensor1.rows(), result.rows(), EQUAL);
        Verify_UInt("Tensor Columns", int_tensor1.columns(), result.columns(), EQUAL);
        Verify_Int("Tensor Element", 6, result.get(0, 0), EQUAL);
        Verify_Int("Tensor Element", 8, result.get(0, 1), EQUAL);
        Verify_Int("Tensor Element", 10, result.get(1, 0), EQUAL);
        Verify_Int("Tensor Element", 12, result.get(1, 1), EQUAL);
    }

    // Integer Tensor Subtraction
    {
        Tensor<int> result = int_tensor1 - int_tensor2;
        Verify_UInt("Tensor Rows", int_tensor1.rows(), result.rows(), EQUAL);
        Verify_UInt("Tensor Columns", int_tensor1.columns(), result.columns(), EQUAL);
        Verify_Int("Tensor Element", -4, result.get(0, 0), EQUAL);
        Verify_Int("Tensor Element", -4, result.get(0, 1), EQUAL);
        Verify_Int("Tensor Element", -4, result.get(1, 0), EQUAL);
        Verify_Int("Tensor Element", -4, result.get(1, 1), EQUAL);
    }

    // Integer Tensor Multiplication
    {
        Tensor<int> int_mult_tensor1(3, 4);
        for (TensorLength_t i = 0; i < 3; i++) {
            for (TensorLength_t j = 0; j < 4; j++) {
                int_mult_tensor1.set(i, j, i + j);
            }
        }

        Tensor<int> int_mult_tensor2(4, 2);
        for (TensorLength_t i = 0; i < 4; i++) {
            for (TensorLength_t j = 0; j < 2; j++) {
                int_mult_tensor2.set(i, j, (i+1) * (j-3));
            }
        }
        
        Tensor<int> result = int_mult_tensor1 * int_mult_tensor2;
        Verify_UInt("Tensor Rows", int_mult_tensor1.rows(), result.rows(), EQUAL);
        Verify_UInt("Tensor Columns", int_mult_tensor2.columns(), result.columns(), EQUAL);
        Verify_Int("Tensor Element", -60, result.get(0, 0), EQUAL);
        Verify_Int("Tensor Element", -40, result.get(0, 1), EQUAL);
        Verify_Int("Tensor Element", -90, result.get(1, 0), EQUAL);
        Verify_Int("Tensor Element", -60, result.get(1, 1), EQUAL);
        Verify_Int("Tensor Element", -120, result.get(2, 0), EQUAL);
        Verify_Int("Tensor Element", -80, result.get(2, 1), EQUAL);
    }

    // Integer Tensor Transposition
    {
        Tensor<int> result = ~int_tensor1;
        Verify_UInt("Tensor Rows", int_tensor1.rows(), result.rows(), EQUAL);
        Verify_UInt("Tensor Columns", int_tensor1.columns(), result.columns(), EQUAL);
        Verify_Int("Tensor Element", 1, result.get(0, 0), EQUAL);
        Verify_Int("Tensor Element", 3, result.get(0, 1), EQUAL);
        Verify_Int("Tensor Element", 2, result.get(1, 0), EQUAL);
        Verify_Int("Tensor Element", 4, result.get(1, 1), EQUAL);
    }

    // Decimal tensors for most tests
    Tensor<double> double_tensor1(2, 2);
    double_tensor1.set(0, 0, 1.5);
    double_tensor1.set(0, 1, 2.5);
    double_tensor1.set(1, 0, 3.5);
    double_tensor1.set(1, 1, 4.5);

    Tensor<double> double_tensor2(2, 2);
    double_tensor2.set(0, 0, 5.5);
    double_tensor2.set(0, 1, 6.5);
    double_tensor2.set(1, 0, 7.5);
    double_tensor2.set(1, 1, 8.5);

    // Decimal Tensor Addition
    {
        Tensor<double> result = double_tensor1 + double_tensor2;
        Verify_UInt("Tensor Rows", double_tensor1.rows(), result.rows(), EQUAL);
        Verify_UInt("Tensor Columns", double_tensor1.columns(), result.columns(), EQUAL);
        Verify_Double("Tensor Element", 7.0, result.get(0, 0), EQUAL);
        Verify_Double("Tensor Element", 9.0, result.get(0, 1), EQUAL);
        Verify_Double("Tensor Element", 11.0, result.get(1, 0), EQUAL);
        Verify_Double("Tensor Element", 13.0, result.get(1, 1), EQUAL);
    }

    // Decimal Tensor Subtraction
    {
        Tensor<double> result = double_tensor1 - double_tensor2;
        Verify_UInt("Tensor Rows", double_tensor1.rows(), result.rows(), EQUAL);
        Verify_UInt("Tensor Columns", double_tensor1.columns(), result.columns(), EQUAL);
        Verify_Double("Tensor Element", -4.0, result.get(0, 0), EQUAL);
        Verify_Double("Tensor Element", -4.0, result.get(0, 1), EQUAL);
        Verify_Double("Tensor Element", -4.0, result.get(1, 0), EQUAL);
        Verify_Double("Tensor Element", -4.0, result.get(1, 1), EQUAL);
    }

    // Decimal Tensor Multiplication
    {
        Tensor<double> double_mult_tensor1(3, 4);
        for (TensorLength_t i = 0; i < 3; i++) {
            for (TensorLength_t j = 0; j < 4; j++) {
                double_mult_tensor1.set(i, j, 1.5 + i + j);
            }
        }

        Tensor<double> double_mult_tensor2(4, 2);
        for (TensorLength_t i = 0; i < 4; i++) {
            for (TensorLength_t j = 0; j < 2; j++) {
                double_mult_tensor2.set(i, j, (i+1.0) * (j-3.0));
            }
        }
        
        Tensor<double> result = double_mult_tensor1 * double_mult_tensor2;
        Verify_UInt("Tensor Rows", double_mult_tensor1.rows(), result.rows(), EQUAL);
        Verify_UInt("Tensor Columns", double_mult_tensor2.columns(), result.columns(), EQUAL);
        Verify_Double("Tensor Element", -105.0, result.get(0, 0), EQUAL);
        Verify_Double("Tensor Element", -70.0, result.get(0, 1), EQUAL);
        Verify_Double("Tensor Element", -135.0, result.get(1, 0), EQUAL);
        Verify_Double("Tensor Element", -90.0, result.get(1, 1), EQUAL);
        Verify_Double("Tensor Element", -165.0, result.get(2, 0), EQUAL);
        Verify_Double("Tensor Element", -110.0, result.get(2, 1), EQUAL);
    }

    // Decimal Tensor Transposition
    {
        Tensor<double> result = ~double_tensor1;
        Verify_UInt("Tensor Rows", double_tensor1.columns(), result.rows(), EQUAL);
        Verify_UInt("Tensor Columns", double_tensor1.rows(), result.columns(), EQUAL);
        Verify_Double("Tensor Element", 1.5, result.get(0, 0), EQUAL);
        Verify_Double("Tensor Element", 3.5, result.get(0, 1), EQUAL);
        Verify_Double("Tensor Element", 2.5, result.get(1, 0), EQUAL);
        Verify_Double("Tensor Element", 4.5, result.get(1, 1), EQUAL);
    }

    TestPostamble();
}

void Tensor_MultiTensor_Assignment_Operations() {
    const char *description = "Verify multi-tensor assignment operations modify tensors as expected";
    const char *for_set[] = {
        "Addition, Subtraction, Multiplication, Assignment, Concatenation",
        "Integer, Decimal"
    };
    const char *preconditions[] = {
        "Valid Sizes"
    };
    const char *results[] = {
        "Tensor Set with Expected Size and Values"
    };

    TestPreamble(description, for_set, preconditions, results);

    // Integer tensors for most tests
    Tensor<int> int_tensor1(2, 2);
    int_tensor1.set(0, 0, 1);
    int_tensor1.set(0, 1, 2);
    int_tensor1.set(1, 0, 3);
    int_tensor1.set(1, 1, 4);

    Tensor<int> int_tensor2(2, 2);
    int_tensor2.set(0, 0, 5);
    int_tensor2.set(0, 1, 6);
    int_tensor2.set(1, 0, 7);
    int_tensor2.set(1, 1, 8);

    // Integer Tensor Addition
    {
        Tensor<int> int_copy = int_tensor1;
        int_copy += int_tensor2;
        Verify_UInt("Tensor Rows", int_tensor1.rows(), int_copy.rows(), EQUAL);
        Verify_UInt("Tensor Columns", int_tensor1.columns(), int_copy.columns(), EQUAL);
        Verify_Int("Tensor Element", 6, int_copy.get(0, 0), EQUAL);
        Verify_Int("Tensor Element", 8, int_copy.get(0, 1), EQUAL);
        Verify_Int("Tensor Element", 10, int_copy.get(1, 0), EQUAL);
        Verify_Int("Tensor Element", 12, int_copy.get(1, 1), EQUAL);
    }

    // Integer Tensor Subtraction
    {
        Tensor<int> int_copy = int_tensor1;
        int_copy -= int_tensor2;
        Verify_UInt("Tensor Rows", int_tensor1.rows(), int_copy.rows(), EQUAL);
        Verify_UInt("Tensor Columns", int_tensor1.columns(), int_copy.columns(), EQUAL);
        Verify_Int("Tensor Element", -4, int_copy.get(0, 0), EQUAL);
        Verify_Int("Tensor Element", -4, int_copy.get(0, 1), EQUAL);
        Verify_Int("Tensor Element", -4, int_copy.get(1, 0), EQUAL);
        Verify_Int("Tensor Element", -4, int_copy.get(1, 1), EQUAL);
    }

    // Integer Tensor Multiplication
    {
        Tensor<int> int_mult_tensor1(3, 4);
        for (TensorLength_t i = 0; i < 3; i++) {
            for (TensorLength_t j = 0; j < 4; j++) {
                int_mult_tensor1.set(i, j, i + j);
            }
        }

        Tensor<int> int_mult_tensor2(4, 2);
        for (TensorLength_t i = 0; i < 4; i++) {
            for (TensorLength_t j = 0; j < 2; j++) {
                int_mult_tensor2.set(i, j, (i+1) * (j-3));
            }
        }
        
        TensorLength_t original_rows = int_mult_tensor1.rows();
        int_mult_tensor1 *= int_mult_tensor2;
        Verify_UInt("Tensor Rows", original_rows, int_mult_tensor1.rows(), EQUAL);
        Verify_UInt("Tensor Columns", int_mult_tensor2.columns(), int_mult_tensor1.columns(), EQUAL);
        Verify_Int("Tensor Element", -60, int_mult_tensor1.get(0, 0), EQUAL);
        Verify_Int("Tensor Element", -40, int_mult_tensor1.get(0, 1), EQUAL);
        Verify_Int("Tensor Element", -90, int_mult_tensor1.get(1, 0), EQUAL);
        Verify_Int("Tensor Element", -60, int_mult_tensor1.get(1, 1), EQUAL);
        Verify_Int("Tensor Element", -120, int_mult_tensor1.get(2, 0), EQUAL);
        Verify_Int("Tensor Element", -80, int_mult_tensor1.get(2, 1), EQUAL);
    }

    // Integer Tensor Assignment
    {
        Tensor<int> int_copy(int_tensor1.size());
        int_copy = int_tensor1;
        Verify_UInt("Tensor Rows", int_tensor1.rows(), int_copy.rows(), EQUAL);
        Verify_UInt("Tensor Columns", int_tensor1.columns(), int_copy.columns(), EQUAL);
        Verify_Int("Tensor Element", int_tensor1.get(0, 0), int_copy.get(0, 0), EQUAL);
        Verify_Int("Tensor Element", int_tensor1.get(0, 1), int_copy.get(0, 1), EQUAL);
        Verify_Int("Tensor Element", int_tensor1.get(1, 0), int_copy.get(1, 0), EQUAL);
        Verify_Int("Tensor Element", int_tensor1.get(1, 1), int_copy.get(1, 1), EQUAL);
    }

    // Integer Tensor Concatenation
    {
        int_tensor1 << int_tensor2;
        Verify_UInt("Tensor Rows", int_tensor1.rows(), 2u, EQUAL);
        Verify_UInt("Tensor Columns", (unsigned long)int_tensor1.columns(), 4u, EQUAL);
        Verify_Int("Tensor Element", 1, int_tensor1.get(0, 0), EQUAL);
        Verify_Int("Tensor Element", 2, int_tensor1.get(0, 1), EQUAL);
        Verify_Int("Tensor Element", 5, int_tensor1.get(0, 2), EQUAL);
        Verify_Int("Tensor Element", 6, int_tensor1.get(0, 3), EQUAL);
        Verify_Int("Tensor Element", 3, int_tensor1.get(1, 0), EQUAL);
        Verify_Int("Tensor Element", 4, int_tensor1.get(1, 1), EQUAL);
        Verify_Int("Tensor Element", 7, int_tensor1.get(1, 2), EQUAL);
        Verify_Int("Tensor Element", 8, int_tensor1.get(1, 3), EQUAL);
    }

    // Decimal tensors for most tests
    Tensor<double> double_tensor1(2, 2);
    double_tensor1.set(0, 0, 1.5);
    double_tensor1.set(0, 1, 2.5);
    double_tensor1.set(1, 0, 3.5);
    double_tensor1.set(1, 1, 4.5);

    Tensor<double> double_tensor2(2, 2);
    double_tensor2.set(0, 0, 5.5);
    double_tensor2.set(0, 1, 6.5);
    double_tensor2.set(1, 0, 7.5);
    double_tensor2.set(1, 1, 8.5);

    // Decimal Tensor Addition
    {
        Tensor<double> copy = double_tensor1;
        copy += double_tensor2;
        Verify_UInt("Tensor Rows", double_tensor1.rows(), copy.rows(), EQUAL);
        Verify_UInt("Tensor Columns", double_tensor1.columns(), copy.columns(), EQUAL);
        Verify_Double("Tensor Element", 7.0, copy.get(0, 0), EQUAL);
        Verify_Double("Tensor Element", 9.0, copy.get(0, 1), EQUAL);
        Verify_Double("Tensor Element", 11.0, copy.get(1, 0), EQUAL);
        Verify_Double("Tensor Element", 13.0, copy.get(1, 1), EQUAL);
    }

    // Decimal Tensor Subtraction
    {
        Tensor<double> copy = double_tensor1;
        copy -= double_tensor2;
        Verify_UInt("Tensor Rows", double_tensor1.rows(), copy.rows(), EQUAL);
        Verify_UInt("Tensor Columns", double_tensor1.columns(), copy.columns(), EQUAL);
        Verify_Double("Tensor Element", -4.0, copy.get(0, 0), EQUAL);
        Verify_Double("Tensor Element", -4.0, copy.get(0, 1), EQUAL);
        Verify_Double("Tensor Element", -4.0, copy.get(1, 0), EQUAL);
        Verify_Double("Tensor Element", -4.0, copy.get(1, 1), EQUAL);
    }

    // Decimal Tensor Multiplication
    {
        Tensor<double> double_mult_tensor1(3, 4);
        for (TensorLength_t i = 0; i < 3; i++) {
            for (TensorLength_t j = 0; j < 4; j++) {
                double_mult_tensor1.set(i, j, 1.5 + i + j);
            }
        }

        Tensor<double> double_mult_tensor2(4, 2);
        for (TensorLength_t i = 0; i < 4; i++) {
            for (TensorLength_t j = 0; j < 2; j++) {
                double_mult_tensor2.set(i, j, (i+1.0) * (j-3.0));
            }
        }
        
        TensorLength_t original_rows = double_mult_tensor1.rows();
        double_mult_tensor1 *= double_mult_tensor2;
        Verify_UInt("Tensor Rows", original_rows, double_mult_tensor1.rows(), EQUAL);
        Verify_UInt("Tensor Columns", double_mult_tensor2.columns(), double_mult_tensor1.columns(), EQUAL);
        Verify_Double("Tensor Element", -105.0, double_mult_tensor1.get(0, 0), EQUAL);
        Verify_Double("Tensor Element", -70.0, double_mult_tensor1.get(0, 1), EQUAL);
        Verify_Double("Tensor Element", -135.0, double_mult_tensor1.get(1, 0), EQUAL);
        Verify_Double("Tensor Element", -90.0, double_mult_tensor1.get(1, 1), EQUAL);
        Verify_Double("Tensor Element", -165.0, double_mult_tensor1.get(2, 0), EQUAL);
        Verify_Double("Tensor Element", -110.0, double_mult_tensor1.get(2, 1), EQUAL);
    }

    // Decimal Tensor Assignment
    {
        Tensor<double> double_copy(double_tensor1.size());
        double_copy = double_tensor1;
        Verify_UInt("Tensor Rows", double_tensor1.rows(), double_copy.rows(), EQUAL);
        Verify_UInt("Tensor Columns", double_tensor1.columns(), double_copy.columns(), EQUAL);
        Verify_Double("Tensor Element", double_tensor1.get(0, 0), double_copy.get(0, 0), EQUAL);
        Verify_Double("Tensor Element", double_tensor1.get(0, 1), double_copy.get(0, 1), EQUAL);
        Verify_Double("Tensor Element", double_tensor1.get(1, 0), double_copy.get(1, 0), EQUAL);
        Verify_Double("Tensor Element", double_tensor1.get(1, 1), double_copy.get(1, 1), EQUAL);
    }

    // Decimal Tensor Concatenation
    {
        double_tensor1 << double_tensor2;
        Verify_UInt("Tensor Rows", double_tensor1.rows(), 2u, EQUAL);
        Verify_UInt("Tensor Columns", double_tensor1.columns(), 4u, EQUAL);
        Verify_Double("Tensor Element", 1.5, double_tensor1.get(0, 0), EQUAL);
        Verify_Double("Tensor Element", 2.5, double_tensor1.get(0, 1), EQUAL);
        Verify_Double("Tensor Element", 5.5, double_tensor1.get(0, 2), EQUAL);
        Verify_Double("Tensor Element", 6.5, double_tensor1.get(0, 3), EQUAL);
        Verify_Double("Tensor Element", 3.5, double_tensor1.get(1, 0), EQUAL);
        Verify_Double("Tensor Element", 4.5, double_tensor1.get(1, 1), EQUAL);
        Verify_Double("Tensor Element", 7.5, double_tensor1.get(1, 2), EQUAL);
        Verify_Double("Tensor Element", 8.5, double_tensor1.get(1, 3), EQUAL);
    }

    TestPostamble();
}

void Tensor_MultiTensor_Element_Operations() {
    const char *description = "Verify tensor element operations modify tensors as expected";
    const char *for_set[] = {
        "Addition, Subtraction, Multiplication, Division, Exponentiation",
        "Integer, Decimal"
    };
    const char *preconditions[] = {
        "Valid Sizes"
    };
    const char *results[] = {
        "Tensor Set with Expected Size and Values"
    };

    TestPreamble(description, for_set, preconditions, results);

    // Integer tensors for most tests
    Tensor<int> int_tensor(2, 2);
    int_tensor.set(0, 0, 1);
    int_tensor.set(0, 1, 2);
    int_tensor.set(1, 0, 3);
    int_tensor.set(1, 1, 4);

    // Integer Element Addition
    {
        Tensor<int> result = int_tensor + 2;
        Verify_UInt("Tensor Rows", int_tensor.rows(), result.rows(), EQUAL);
        Verify_UInt("Tensor Columns", int_tensor.columns(), result.columns(), EQUAL);
        Verify_Int("Tensor Element", 3, result.get(0, 0), EQUAL);
        Verify_Int("Tensor Element", 4, result.get(0, 1), EQUAL);
        Verify_Int("Tensor Element", 5, result.get(1, 0), EQUAL);
        Verify_Int("Tensor Element", 6, result.get(1, 1), EQUAL);
    }

    // Integer Element Subtraction
    {
        Tensor<int> result = int_tensor - 2;
        Verify_UInt("Tensor Rows", int_tensor.rows(), result.rows(), EQUAL);
        Verify_UInt("Tensor Columns", int_tensor.columns(), result.columns(), EQUAL);
        Verify_Int("Tensor Element", -1, result.get(0, 0), EQUAL);
        Verify_Int("Tensor Element", 0, result.get(0, 1), EQUAL);
        Verify_Int("Tensor Element", 1, result.get(1, 0), EQUAL);
        Verify_Int("Tensor Element", 2, result.get(1, 1), EQUAL);
    }

    // Integer Element Multiplication
    {
        Tensor<int> result = int_tensor * 2;
        Verify_UInt("Tensor Rows", int_tensor.rows(), result.rows(), EQUAL);
        Verify_UInt("Tensor Columns", int_tensor.columns(), result.columns(), EQUAL);
        Verify_Int("Tensor Element", 2, result.get(0, 0), EQUAL);
        Verify_Int("Tensor Element", 4, result.get(0, 1), EQUAL);
        Verify_Int("Tensor Element", 6, result.get(1, 0), EQUAL);
        Verify_Int("Tensor Element", 8, result.get(1, 1), EQUAL);
    }

    // Integer Element Division
    {
        Tensor<int> result = int_tensor / 2;
        Verify_UInt("Tensor Rows", int_tensor.rows(), result.rows(), EQUAL);
        Verify_UInt("Tensor Columns", int_tensor.columns(), result.columns(), EQUAL);
        Verify_Int("Tensor Element", 0, result.get(0, 0), EQUAL);
        Verify_Int("Tensor Element", 1, result.get(0, 1), EQUAL);
        Verify_Int("Tensor Element", 1, result.get(1, 0), EQUAL);
        Verify_Int("Tensor Element", 2, result.get(1, 1), EQUAL);
    }

    // Integer Element Exponentiation
    {
        Tensor<int> result = int_tensor ^ 2;
        Verify_UInt("Tensor Rows", int_tensor.rows(), result.rows(), EQUAL);
        Verify_UInt("Tensor Columns", int_tensor.columns(), result.columns(), EQUAL);
        Verify_Int("Tensor Element", 1, result.get(0, 0), EQUAL);
        Verify_Int("Tensor Element", 4, result.get(0, 1), EQUAL);
        Verify_Int("Tensor Element", 9, result.get(1, 0), EQUAL);
        Verify_Int("Tensor Element", 16, result.get(1, 1), EQUAL);
    }

    // Decimal tensors for most tests
    Tensor<double> double_tensor(2, 2);
    double_tensor.set(0, 0, 1.5);
    double_tensor.set(0, 1, 2.5);
    double_tensor.set(1, 0, 3.5);
    double_tensor.set(1, 1, 4.5);

    // Decimal Element Addition
    {
        Tensor<double> result = double_tensor + 2.5;
        Verify_UInt("Tensor Rows", double_tensor.rows(), result.rows(), EQUAL);
        Verify_UInt("Tensor Columns", double_tensor.columns(), result.columns(), EQUAL);
        Verify_Double("Tensor Element", 4.0, result.get(0, 0), EQUAL);
        Verify_Double("Tensor Element", 5.0, result.get(0, 1), EQUAL);
        Verify_Double("Tensor Element", 6.0, result.get(1, 0), EQUAL);
        Verify_Double("Tensor Element", 7.0, result.get(1, 1), EQUAL);
    }

    // Decimal Element Subtraction
    {
        Tensor<double> result = double_tensor - 2.5;
        Verify_UInt("Tensor Rows", double_tensor.rows(), result.rows(), EQUAL);
        Verify_UInt("Tensor Columns", double_tensor.columns(), result.columns(), EQUAL);
        Verify_Double("Tensor Element", -1.0, result.get(0, 0), EQUAL);
        Verify_Double("Tensor Element", 0.0, result.get(0, 1), EQUAL);
        Verify_Double("Tensor Element", 1.0, result.get(1, 0), EQUAL);
        Verify_Double("Tensor Element", 2.0, result.get(1, 1), EQUAL);
    }

    // Decimal Element Multiplication
    {
        Tensor<double> result = double_tensor * 2.5;
        Verify_UInt("Tensor Rows", double_tensor.rows(), result.rows(), EQUAL);
        Verify_UInt("Tensor Columns", double_tensor.columns(), result.columns(), EQUAL);
        Verify_Double("Tensor Element", 3.75, result.get(0, 0), EQUAL);
        Verify_Double("Tensor Element", 6.25, result.get(0, 1), EQUAL);
        Verify_Double("Tensor Element", 8.75, result.get(1, 0), EQUAL);
        Verify_Double("Tensor Element", 11.25, result.get(1, 1), EQUAL);
    }

    // Decimal Element Division
    {
        Tensor<double> result = double_tensor / 2.5;
        Verify_UInt("Tensor Rows", double_tensor.rows(), result.rows(), EQUAL);
        Verify_UInt("Tensor Columns", double_tensor.columns(), result.columns(), EQUAL);
        Verify_Double("Tensor Element", 0.6, result.get(0, 0), EQUAL);
        Verify_Double("Tensor Element", 1.0, result.get(0, 1), EQUAL);
        Verify_Double("Tensor Element", 1.4, result.get(1, 0), EQUAL);
        Verify_Double("Tensor Element", 1.8, result.get(1, 1), EQUAL);
    }

    // Decimal Element Exponentiation
    {
        Tensor<double> result = double_tensor ^ 2.0;
        Verify_UInt("Tensor Rows", double_tensor.rows(), result.rows(), EQUAL);
        Verify_UInt("Tensor Columns", double_tensor.columns(), result.columns(), EQUAL);
        Verify_Double("Tensor Element", 2.25, result.get(0, 0), EQUAL);
        Verify_Double("Tensor Element", 6.25, result.get(0, 1), EQUAL);
        Verify_Double("Tensor Element", 12.25, result.get(1, 0), EQUAL);
        Verify_Double("Tensor Element", 20.25, result.get(1, 1), EQUAL);
    }

    TestPostamble();
}

void Tensor_MultiTensor_Element_Assignment_Operations() {
    const char *description = "Verify tensor element operations modify tensors as expected";
    const char *for_set[] = {
        "Addition, Subtraction, Multiplication, Division, Exponentiation",
        "Integer, Decimal"
    };
    const char *preconditions[] = {
        "Valid Sizes"
    };
    const char *results[] = {
        "Tensor Set with Expected Size and Values"
    };

    TestPreamble(description, for_set, preconditions, results);

    // Integer tensors for most tests
    Tensor<int> int_tensor(2, 2);
    int_tensor.set(0, 0, 1);
    int_tensor.set(0, 1, 2);
    int_tensor.set(1, 0, 3);
    int_tensor.set(1, 1, 4);

    // Integer Element Addition
    {
        Tensor<int> copy_int = int_tensor;
        copy_int += 2;
        Verify_UInt("Tensor Rows", int_tensor.rows(), copy_int.rows(), EQUAL);
        Verify_UInt("Tensor Columns", int_tensor.columns(), copy_int.columns(), EQUAL);
        Verify_Int("Tensor Element", 3, copy_int.get(0, 0), EQUAL);
        Verify_Int("Tensor Element", 4, copy_int.get(0, 1), EQUAL);
        Verify_Int("Tensor Element", 5, copy_int.get(1, 0), EQUAL);
        Verify_Int("Tensor Element", 6, copy_int.get(1, 1), EQUAL);
    }

    // Integer Element Subtraction
    {
        Tensor<int> copy_int = int_tensor;
        copy_int -= 2;
        Verify_UInt("Tensor Rows", int_tensor.rows(), copy_int.rows(), EQUAL);
        Verify_UInt("Tensor Columns", int_tensor.columns(), copy_int.columns(), EQUAL);
        Verify_Int("Tensor Element", -1, copy_int.get(0, 0), EQUAL);
        Verify_Int("Tensor Element", 0, copy_int.get(0, 1), EQUAL);
        Verify_Int("Tensor Element", 1, copy_int.get(1, 0), EQUAL);
        Verify_Int("Tensor Element", 2, copy_int.get(1, 1), EQUAL);
    }

    // Integer Element Multiplication
    {
        Tensor<int> copy_int = int_tensor;
        copy_int *= 2;
        Verify_UInt("Tensor Rows", int_tensor.rows(), copy_int.rows(), EQUAL);
        Verify_UInt("Tensor Columns", int_tensor.columns(), copy_int.columns(), EQUAL);
        Verify_Int("Tensor Element", 2, copy_int.get(0, 0), EQUAL);
        Verify_Int("Tensor Element", 4, copy_int.get(0, 1), EQUAL);
        Verify_Int("Tensor Element", 6, copy_int.get(1, 0), EQUAL);
        Verify_Int("Tensor Element", 8, copy_int.get(1, 1), EQUAL);
    }

    // Integer Element Division
    {
        Tensor<int> copy_int = int_tensor;
        copy_int /= 2;
        Verify_UInt("Tensor Rows", int_tensor.rows(), copy_int.rows(), EQUAL);
        Verify_UInt("Tensor Columns", int_tensor.columns(), copy_int.columns(), EQUAL);
        Verify_Int("Tensor Element", 0, copy_int.get(0, 0), EQUAL);
        Verify_Int("Tensor Element", 1, copy_int.get(0, 1), EQUAL);
        Verify_Int("Tensor Element", 1, copy_int.get(1, 0), EQUAL);
        Verify_Int("Tensor Element", 2, copy_int.get(1, 1), EQUAL);
    }

    // Integer Element Exponentiation
    {
        Tensor<int> copy_int = int_tensor;
        copy_int ^= 2;
        Verify_UInt("Tensor Rows", int_tensor.rows(), copy_int.rows(), EQUAL);
        Verify_UInt("Tensor Columns", int_tensor.columns(), copy_int.columns(), EQUAL);
        Verify_Int("Tensor Element", 1, copy_int.get(0, 0), EQUAL);
        Verify_Int("Tensor Element", 4, copy_int.get(0, 1), EQUAL);
        Verify_Int("Tensor Element", 9, copy_int.get(1, 0), EQUAL);
        Verify_Int("Tensor Element", 16, copy_int.get(1, 1), EQUAL);
    }

    // Decimal tensors for most tests
    Tensor<double> double_tensor(2, 2);
    double_tensor.set(0, 0, 1.5);
    double_tensor.set(0, 1, 2.5);
    double_tensor.set(1, 0, 3.5);
    double_tensor.set(1, 1, 4.5);

    // Decimal Element Addition
    {
        Tensor<double> copy_double = double_tensor;
        copy_double += 2.5;
        Verify_UInt("Tensor Rows", double_tensor.rows(), copy_double.rows(), EQUAL);
        Verify_UInt("Tensor Columns", double_tensor.columns(), copy_double.columns(), EQUAL);
        Verify_Double("Tensor Element", 4.0, copy_double.get(0, 0), EQUAL);
        Verify_Double("Tensor Element", 5.0, copy_double.get(0, 1), EQUAL);
        Verify_Double("Tensor Element", 6.0, copy_double.get(1, 0), EQUAL);
        Verify_Double("Tensor Element", 7.0, copy_double.get(1, 1), EQUAL);
    }

    // Decimal Element Subtraction
    {
        Tensor<double> copy_double = double_tensor;
        copy_double -= 2.5;
        Verify_UInt("Tensor Rows", double_tensor.rows(), copy_double.rows(), EQUAL);
        Verify_UInt("Tensor Columns", double_tensor.columns(), copy_double.columns(), EQUAL);
        Verify_Double("Tensor Element", -1.0, copy_double.get(0, 0), EQUAL);
        Verify_Double("Tensor Element", 0.0, copy_double.get(0, 1), EQUAL);
        Verify_Double("Tensor Element", 1.0, copy_double.get(1, 0), EQUAL);
        Verify_Double("Tensor Element", 2.0, copy_double.get(1, 1), EQUAL);
    }

    // Decimal Element Multiplication
    {
        Tensor<double> copy_double = double_tensor;
        copy_double *= 2.5;
        Verify_UInt("Tensor Rows", double_tensor.rows(), copy_double.rows(), EQUAL);
        Verify_UInt("Tensor Columns", double_tensor.columns(), copy_double.columns(), EQUAL);
        Verify_Double("Tensor Element", 3.75, copy_double.get(0, 0), EQUAL);
        Verify_Double("Tensor Element", 6.25, copy_double.get(0, 1), EQUAL);
        Verify_Double("Tensor Element", 8.75, copy_double.get(1, 0), EQUAL);
        Verify_Double("Tensor Element", 11.25, copy_double.get(1, 1), EQUAL);
    }

    // Decimal Element Division
    {
        Tensor<double> copy_double = double_tensor;
        copy_double /= 2.5;
        Verify_UInt("Tensor Rows", double_tensor.rows(), copy_double.rows(), EQUAL);
        Verify_UInt("Tensor Columns", double_tensor.columns(), copy_double.columns(), EQUAL);
        Verify_Double("Tensor Element", 0.6, copy_double.get(0, 0), EQUAL);
        Verify_Double("Tensor Element", 1.0, copy_double.get(0, 1), EQUAL);
        Verify_Double("Tensor Element", 1.4, copy_double.get(1, 0), EQUAL);
        Verify_Double("Tensor Element", 1.8, copy_double.get(1, 1), EQUAL);
    }

    // Decimal Element Exponentiation
    {
        Tensor<double> copy_double = double_tensor;
        copy_double ^= 2.0;
        Verify_UInt("Tensor Rows", double_tensor.rows(), copy_double.rows(), EQUAL);
        Verify_UInt("Tensor Columns", double_tensor.columns(), copy_double.columns(), EQUAL);
        Verify_Double("Tensor Element", 2.25, copy_double.get(0, 0), EQUAL);
        Verify_Double("Tensor Element", 6.25, copy_double.get(0, 1), EQUAL);
        Verify_Double("Tensor Element", 12.25, copy_double.get(1, 0), EQUAL);
        Verify_Double("Tensor Element", 20.25, copy_double.get(1, 1), EQUAL);
    }

    TestPostamble();
}

void setup() {
    Serial.begin(115200);
    delay(3000);
    assert(Serial);

    Tensor_Constructor();
    Tensor_MultiTensor_Operations();
    Tensor_MultiTensor_Assignment_Operations();
    Tensor_MultiTensor_Element_Operations();
    Tensor_MultiTensor_Element_Assignment_Operations();
}

void loop() {
    while (true) continue;
}
