/**
 ********************************************************************************
 * @file    vector.ino
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Unit Tests of Vector Class
 * @version 1.0
 * @date    2024-03-18
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#include <unity.h>

#include "Vector.tpp"
using namespace DataStructures::Vector;

void Vector_Constructor() {
    // Size for all Constructors
    VectorLength_t length = 3;

    TEST_MESSAGE("Vector Size Constructor");
    {
        Vector<int> vector(length);
        TEST_ASSERT_EQUAL_UINT_MESSAGE(length, vector.length(), "Vector Length not equal to Constructor Argument");
        for (VectorLength_t i = 0; i < length; i++) {
            TEST_ASSERT_EQUAL_INT_MESSAGE(0, vector.get(i), "Vector Element not initialized to 0");
        }
    }

    TEST_MESSAGE("Vector Copy Constructor");
    {
        // Create Vector to Copy
        Vector<int> vector(length);
        for (VectorLength_t i = 0; i < length; i++) {
            vector.set(i, i);
        }

        // Copy Vector
        Vector<int> copy(vector);
        TEST_ASSERT_EQUAL_UINT_MESSAGE(length, vector.length(), "Copied Vector Length not equal to Source Vector Length");
        for (VectorLength_t i = 0; i < length; i++) {
            TEST_ASSERT_EQUAL_INT_MESSAGE(vector.get(i), copy.get(i), "Copied Vector Element not equivalent to Source Vector Element");
        }
    }

    TEST_MESSAGE("Vector Assignment Operator");
    {
        // Create Vector to Assign
        Vector<int> vector(length);
        for (VectorLength_t i = 0; i < length; i++) {
            vector.set(i, i);
        }

        // Assign Vector
        Vector<int> assign = vector;
        TEST_ASSERT_EQUAL_UINT_MESSAGE(length, vector.length(), "Assigned Vector Length not equal to Source Vector Length");
        for (VectorLength_t i = 0; i < length; i++) {
            TEST_ASSERT_EQUAL_INT_MESSAGE(vector.get(i), assign.get(i), "Assigned Vector Element not equivalent to Source Vector Element");
        }
    }
}

void Vector_MultiVector_Operators() {
    // Size for all Vectors
    VectorLength_t length = 3;

    // Operating Vectors
    Vector<double> vector1(length);
    Vector<double> vector2(length);

    for (VectorLength_t i = 0; i < length; i++) {
        vector1.set(i, i + 1.0);
        vector2.set(i, 3.5*i + 1.0);
    }

    TEST_MESSAGE("Vector Addition");
    {
        Vector<double> result = vector1 + vector2;
        TEST_ASSERT_EQUAL_UINT_MESSAGE(length, result.length(), "Result Vector Length not equal to Source Vector Length");
        for (VectorLength_t i = 0; i < length; i++) {
            double expected = vector1.get(i) + vector2.get(i);
            TEST_ASSERT_FLOAT_WITHIN_MESSAGE(fabs(0.001 * expected), expected, result.get(i), "Result Vector Element not equivalent to Sum of Source Vector Elements");
        }
    }

    TEST_MESSAGE("Vector Subtraction");
    {
        Vector<double> result = vector1 - vector2;
        TEST_ASSERT_EQUAL_UINT_MESSAGE(length, result.length(), "Result Vector Length not equal to Source Vector Length");
        for (VectorLength_t i = 0; i < length; i++) {
            double expected = vector1.get(i) - vector2.get(i);
            TEST_ASSERT_FLOAT_WITHIN_MESSAGE(fabs(0.001 * expected), expected, result.get(i), "Result Vector Element not equivalent to Difference of Source Vector Elements");
        }
    }

    TEST_MESSAGE("Vector Dot Multiplication");
    {
        double result = vector1.dot(vector2);
        double expected = 0;
        for (VectorLength_t i = 0; i < length; i++) {
            expected += vector1.get(i) * vector2.get(i);
        }
        TEST_ASSERT_FLOAT_WITHIN_MESSAGE(fabs(0.001 * expected), expected, result, "Dot Product of Vectors not equal to Sum of Element Multiplication");
    }

    TEST_MESSAGE("Vector Cross Multiplication");
    {
        Vector<double> result = vector1 * vector2;
        TEST_ASSERT_EQUAL_UINT_MESSAGE(length, result.length(), "Result Vector Length not equal to Source Vector Length");

        double expected = vector1.get(1) * vector2.get(2) - vector1.get(2) * vector2.get(1);
        TEST_ASSERT_FLOAT_WITHIN_MESSAGE(fabs(0.001 * expected), expected, result.get(0), "Cross Product Element 1 not equal to Expected Value");
        expected = vector1.get(2) * vector2.get(0) - vector1.get(0) * vector2.get(2);
        TEST_ASSERT_FLOAT_WITHIN_MESSAGE(fabs(0.001 * expected), expected, result.get(1), "Cross Product Element 2 not equal to Expected Value");
        expected = vector1.get(0) * vector2.get(1) - vector1.get(1) * vector2.get(0);
        TEST_ASSERT_FLOAT_WITHIN_MESSAGE(fabs(0.001 * expected), expected, result.get(2), "Cross Product Element 3 not equal to Expected Value");
    }

    TEST_MESSAGE("Vector Concatenation");
    {
        Vector<double> result = vector1 << vector2;
        TEST_ASSERT_EQUAL_UINT_MESSAGE(vector1.length() + vector2.length(), result.length(), "Result Vector Length not equal to Sum of Source Vector Lengths");
        for (VectorLength_t i = 0; i < result.length(); i++) {
            if (i < vector1.length()) {
                TEST_ASSERT_EQUAL_FLOAT_MESSAGE(vector1.get(i), result.get(i), "Result Vector Element not equal to Source Vector Element");
            } else {
                TEST_ASSERT_EQUAL_FLOAT_MESSAGE(vector2.get(i - vector1.length()), result.get(i), "Result Vector Element not equal to Source Vector Element");
            }
        }
    }
}

void Vector_MultiVector_Assignment_Operators() {
    // Size for all Vectors
    VectorLength_t length = 3;

    // Operating Vectors
    Vector<double> vector1(length);
    Vector<double> vector2(length);

    for (VectorLength_t i = 0; i < length; i++) {
        double value = i;
        vector1.set(i, value);
        vector2.set(i, 3*value - 1);
    }

    TEST_MESSAGE("Vector Addition Assignment");
    {
        Vector<double> result = vector1;
        result += vector2;
        for (VectorLength_t i = 0; i < length; i++) {
            double expected = vector1.get(i) + vector2.get(i);
            TEST_ASSERT_FLOAT_WITHIN_MESSAGE(fabs(0.001 * expected), expected, result.get(i), "Result Vector Element not equivalent to Sum of Source Vector Elements");
        }
    }

    TEST_MESSAGE("Vector Subtraction Assignment");
    {
        Vector<double> result = vector1;
        result -= vector2;
        for (VectorLength_t i = 0; i < length; i++) {
            double expected = vector1.get(i) - vector2.get(i);
            TEST_ASSERT_FLOAT_WITHIN_MESSAGE(fabs(0.001 * expected), expected, result.get(i), "Result Vector Element not equivalent to Difference of Source Vector Elements");
        }
    }

    TEST_MESSAGE("Vector Cross Multiplication Assignment");
    {
        Vector<double> result = vector1;
        result *= vector2;

        double expected = vector1.get(1) * vector2.get(2) - vector1.get(2) * vector2.get(1);
        TEST_ASSERT_FLOAT_WITHIN_MESSAGE(fabs(0.001 * expected), expected, result.get(0), "Cross Product Element 1 not equal to Expected Value");
        expected = vector1.get(2) * vector2.get(0) - vector1.get(0) * vector2.get(2);
        TEST_ASSERT_FLOAT_WITHIN_MESSAGE(fabs(0.001 * expected), expected, result.get(1), "Cross Product Element 2 not equal to Expected Value");
        expected = vector1.get(0) * vector2.get(1) - vector1.get(1) * vector2.get(0);
        TEST_ASSERT_FLOAT_WITHIN_MESSAGE(fabs(0.001 * expected), expected, result.get(2), "Cross Product Element 3 not equal to Expected Value");
    }

    TEST_MESSAGE("Vector Concatenation Assignment");
    {
        Vector<double> result = vector1;
        result <<= vector2;
        TEST_ASSERT_EQUAL_UINT_MESSAGE(vector1.length() + vector2.length(), result.length(), "Result Vector Length not equal to Sum of Source Vector Lengths");
        for (VectorLength_t i = 0; i < result.length(); i++) {
            if (i < vector1.length()) {
                TEST_ASSERT_EQUAL_FLOAT_MESSAGE(vector1.get(i), result.get(i), "Result Vector Element not equal to Source Vector Element");
            } else {
                TEST_ASSERT_EQUAL_FLOAT_MESSAGE(vector2.get(i - vector1.length()), result.get(i), "Result Vector Element not equal to Source Vector Element");
            }
        }
    }
}

void Vector_Element_Operators() {
    // Size for all Vectors
    VectorLength_t length = 3;

    // Operating Vectors
    Vector<double> vector(length);

    for (VectorLength_t i = 0; i < length; i++) {
        double value = i;
        vector.set(i, 3*value + 1);
    }

    TEST_MESSAGE("Element Addition");
    {
        Vector<double> result = vector + 2;
        TEST_ASSERT_EQUAL_UINT_MESSAGE(length, result.length(), "Result Vector Length not equal to Source Vector Length");
        for (VectorLength_t i = 0; i < length; i++) {
            double expected = vector.get(i) + 2;
            TEST_ASSERT_FLOAT_WITHIN_MESSAGE(fabs(0.001 * expected), expected, result.get(i), "Result Vector Element not equivalent to Sum of Source Vector Elements");
        }
    }

    TEST_MESSAGE("Element Subtraction");
    {
        Vector<double> result = vector - 2;
        TEST_ASSERT_EQUAL_UINT_MESSAGE(length, result.length(), "Result Vector Length not equal to Source Vector Length");
        for (VectorLength_t i = 0; i < length; i++) {
            double expected = vector.get(i) - 2;
            TEST_ASSERT_FLOAT_WITHIN_MESSAGE(fabs(0.001 * expected), expected, result.get(i), "Result Vector Element not equivalent to Difference of Source Vector Elements");
        }
    }

    TEST_MESSAGE("Element Multiplication");
    {
        Vector<double> result = vector * 2;
        TEST_ASSERT_EQUAL_UINT_MESSAGE(length, result.length(), "Result Vector Length not equal to Source Vector Length");
        for (VectorLength_t i = 0; i < length; i++) {
            double expected = vector.get(i) * 2;
            TEST_ASSERT_FLOAT_WITHIN_MESSAGE(fabs(0.001 * expected), expected, result.get(i), "Result Vector Element not equivalent to Product of Source Vector Elements");
        }
    }

    TEST_MESSAGE("Element Division");
    {
        Vector<double> result = vector / 2;
        TEST_ASSERT_EQUAL_UINT_MESSAGE(length, result.length(), "Result Vector Length not equal to Source Vector Length");
        for (VectorLength_t i = 0; i < length; i++) {
            double expected = vector.get(i) / 2;
            TEST_ASSERT_FLOAT_WITHIN_MESSAGE(fabs(0.001 * expected), expected, result.get(i), "Result Vector Element not equivalent to Quotient of Source Vector Elements");
        }
    }

    TEST_MESSAGE("Element Exponentiation");
    {
        Vector<double> result = vector ^ 2.5;
        TEST_ASSERT_EQUAL_UINT_MESSAGE(length, result.length(), "Result Vector Length not equal to Source Vector Length");
        for (VectorLength_t i = 0; i < length; i++) {
            double expected = pow(vector.get(i), 2.5);
            TEST_ASSERT_INT_WITHIN_MESSAGE(fabs(0.001 * expected), expected, result.get(i), "Result Vector Element not equivalent to Exponentiation of Source Vector Element");
        }
    }
}

void Vector_Element_Assignment_Operators() {
    // Size for all Vectors
    VectorLength_t length = 3;

    // Operating Vectors
    Vector<double> vector(length);

    for (VectorLength_t i = 0; i < length; i++) {
        double value = i;
        vector.set(i, 3*value - 1);
    }

    TEST_MESSAGE("Element Assignment Addition");
    {
        Vector<double> result = vector;
        result += 2;
        for (VectorLength_t i = 0; i < length; i++) {
            double expected = vector.get(i) + 2;
            TEST_ASSERT_FLOAT_WITHIN_MESSAGE(fabs(0.001 * expected), expected, result.get(i), "Result Vector Element not equivalent to Sum of Source Vector Element and Scalar");
        }
    }
    
    TEST_MESSAGE("Element Assignment Subtraction");
    {
        Vector<double> result = vector;
        result -= 2;
        for (VectorLength_t i = 0; i < length; i++) {
            double expected = vector.get(i) - 2;
            TEST_ASSERT_FLOAT_WITHIN_MESSAGE(fabs(0.001 * expected), expected, result.get(i), "Result Vector Element not equivalent to Difference of Source Vector Element and Scalar");
        }
    }

    TEST_MESSAGE("Element Assignment Multiplication");
    {
        Vector<double> result = vector;
        result *= 2;
        for (VectorLength_t i = 0; i < length; i++) {
            double expected = vector.get(i) * 2;
            TEST_ASSERT_FLOAT_WITHIN_MESSAGE(fabs(0.001 * expected), expected, result.get(i), "Result Vector Element not equivalent to Product of Source Vector Element and Scalar");
        }
    }

    TEST_MESSAGE("Element Assignment Division");
    {
        Vector<double> result = vector;
        result /= 2;
        for (VectorLength_t i = 0; i < length; i++) {
            double expected = vector.get(i) / 2;
            TEST_ASSERT_FLOAT_WITHIN_MESSAGE(fabs(0.001 * expected), expected, result.get(i), "Result Vector Element not equivalent to Quotient of Source Vector Element and Scalar");
        }
    }

    TEST_MESSAGE("Element Assignment Exponentiation");
    {
        Vector<double> result = vector;
        result ^= 2.5;
        for (VectorLength_t i = 0; i < length; i++) {
            double expected = pow(vector.get(i), 2.5);
            TEST_ASSERT_FLOAT_WITHIN_MESSAGE(fabs(0.001 * expected), expected, result.get(i), "Result Vector Element not equivalent to Exponentiation of Source Vector Element and Scalar");
        }
    }
}

void Vector_Operators() {
    // Size for all Vectors
    VectorLength_t length = 3;

    // Operating Vectors
    Vector<double> vector(length);

    for (VectorLength_t i = 0; i < length; i++) {
        double value = i;
        vector.set(i, 3*value - 1);
    }

    TEST_MESSAGE("Vector Magnitude");
    {
        double result = vector.magnitude();
        double expected = sqrt(vector.dot(vector));
        TEST_ASSERT_FLOAT_WITHIN_MESSAGE(fabs(0.001 * expected), expected, result, "Vector Magnitude not equal to Square Root of Dot Product of Vector with Itself");
    }

    TEST_MESSAGE("Vector Normalize");
    {
        Vector<double> result = vector.normalize();
        double magnitude = vector.magnitude();
        for (VectorLength_t i = 0; i < length; i++) {
            double expected = vector.get(i) / magnitude;
            TEST_ASSERT_FLOAT_WITHIN_MESSAGE(fabs(0.001 * expected), expected, result.get(i), "Normalized Vector Element not equal to Element Divided by Magnitude");
        }
    }

    TEST_MESSAGE("Vector isZero");
    {
        Vector<double> zero(length);
        TEST_ASSERT_MESSAGE(zero.isZero(), "Known Zero Vector not recognized as Zero Vector");
        TEST_ASSERT_FALSE_MESSAGE(vector.isZero(), "Known Non-Zero Vector recognized as Zero Vector");
    }

    TEST_MESSAGE("Vector isOne");
    {
        Vector<double> one(length);
        one += 1;
        TEST_ASSERT_MESSAGE(one.isOne(), "Known One Vector not recognized as One Vector");
        TEST_ASSERT_FALSE_MESSAGE(vector.isOne(), "Known Non-One Vector recognized as One Vector");
    }

    TEST_MESSAGE("Length");
    {
        TEST_ASSERT_EQUAL_UINT_MESSAGE(length, vector.length(), "Vector Length not equal to Constructor Argument");
    }
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(Vector_Constructor);
    RUN_TEST(Vector_MultiVector_Operators);
    RUN_TEST(Vector_MultiVector_Assignment_Operators);
    RUN_TEST(Vector_Element_Operators);
    RUN_TEST(Vector_Element_Assignment_Operators);
    RUN_TEST(Vector_Operators);
    
    UNITY_END();
}