/**
 ********************************************************************************
 * @file    vector.inc
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Unit Tests of Vector Class
 * @version 1.0
 * @date    2024-03-18
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#include <Arduino.h>
#include <math.h>
#include <unity.h>

#include "test_utilities.hpp"

#include "Vector.tpp"
using namespace DataStructures;

void Vector_Constructor() {
    const char *description = "Verify Vector Constructor creates a Vector object";
    const char *for_set[] = {
        "Vector Size Constructor", 
        "Vector Copy Constructor",
        "Vector Assignment Operator"
    };
    const char *preconditions[] = {
        "Valid Size",
        "Valid Vector to Copy",
        "Valid Vector to Assign"
    };
    const char *results[] = {
        "Vector Created and Zeroed with Expected Size",
        "Vector Created and Copied with Expected Size",
        "Vector Created and Assigned with Expected Size",
    };

    TestPreamble(description, for_set, preconditions, results);

    // Size for all Constructors
    VectorLength_t length = 3;

    Print("Common Vector Parameters:");
    Print("Columns: %u", length);

    Banner("Vector Size Constructor");
    {
        Vector<int> vector(length);
        Verify_UInt("Vector Length", length, vector.length(), EQUAL);
        for (VectorLength_t i = 0; i < length; i++) {
            Verify_Int("Vector Element", 0, vector.get(i), EQUAL);
        }
    }

    Banner("Vector Copy Constructor");
    {
        // Create Vector to Copy
        Vector<int> vector(length);
        for (VectorLength_t i = 0; i < length; i++) {
            vector.set(i, i);
        }

        // Copy Vector
        Vector<int> copy(vector);
        Verify_UInt("Vector Length", vector.length(), copy.length(), EQUAL);
        for (VectorLength_t i = 0; i < length; i++) {
            Verify_Int("Vector Element", vector.get(i), copy.get(i), EQUAL);
        }
    }

    Banner("Vector Assignment Operator");
    {
        // Create Vector to Assign
        Vector<int> vector(length);
        for (VectorLength_t i = 0; i < length; i++) {
            vector.set(i, i);
        }

        // Assign Vector
        Vector<int> assign = vector;
        Verify_UInt("Vector Length", vector.length(), assign.length(), EQUAL);
        for (VectorLength_t i = 0; i < length; i++) {
            Verify_Int("Vector Element", vector.get(i), assign.get(i), EQUAL);
        }
    }

    TestPostamble();
}

void Vector_MultiVector_Operators() {
    const char *description = "Verify Vector MultiVector Operators creates new Vector objects as expected";
    const char *for_set[] = {
        "Vector Addition", 
        "Vector Subtraction",
        "Vector Dot Multiplication",
        "Vector Cross Multiplication",
        "Vector Concatenation"
    };
    const char *preconditions[] = {
        "Valid Size",
        "Valid Vectors to Operate"
    };
    const char *results[] = {
        "Vector Created from Addition with Expected Size",
        "Vector Created from Subtraction with Expected Size",
        "Scalar Created from Dot Multiplication with Expected Size",
        "Vector Created from Cross Multiplication with Expected Size",
        "Vector Created from Concatenation with Expected Size"
    };

    TestPreamble(description, for_set, preconditions, results);

    // Size for all Vectors
    VectorLength_t length = 3;

    Print("Common Vector Parameters:");
    Print("Length: %u", length);

    // Operating Vectors
    Vector<int> vector1(length);
    Vector<int> vector2(length);

    for (VectorLength_t i = 0; i < length; i++) {
        const int value = i;
        vector1.set(i, value);
        vector2.set(i, 3*value - 1);
    }

    Print("Operating Vectors:");
    Print("Vector 1: [%d, %d, %d]", vector1.get(0), vector1.get(1), vector1.get(2));
    Print("Vector 2: [%d, %d, %d]", vector2.get(0), vector2.get(1), vector2.get(2));

    Banner("Vector Addition");
    {
        Vector<int> result = vector1 + vector2;
        Verify_UInt("Vector Length", length, result.length(), EQUAL);
        for (VectorLength_t i = 0; i < length; i++) {
            Verify_Int("Vector Element", vector1.get(i) + vector2.get(i), result.get(i), EQUAL);
        }
    }

    Banner("Vector Subtraction");
    {
        Vector<int> result = vector1 - vector2;
        Verify_UInt("Vector Length", length, result.length(), EQUAL);
        for (VectorLength_t i = 0; i < length; i++) {
            Verify_Int("Vector Element", vector1.get(i) - vector2.get(i), result.get(i), EQUAL);
        }
    }

    Banner("Vector Dot Multiplication");
    {
        int result = dot(vector1, vector2);
        int expected = 0;
        for (VectorLength_t i = 0; i < length; i++) {
            expected += vector1.get(i) * vector2.get(i);
        }
        Verify_Int("Scalar Result", expected, result, EQUAL);
    }

    Banner("Vector Cross Multiplication");
    {
        Vector<int> result = cross(vector1, vector2);
        Verify_UInt("Vector Length", length, result.length(), EQUAL);

        int expected = vector1.get(1) * vector2.get(2) - vector1.get(2) * vector2.get(1);
        Verify_Int("Vector Element 1", expected, result.get(0), EQUAL);
        expected = vector1.get(2) * vector2.get(0) - vector1.get(0) * vector2.get(2);
        Verify_Int("Vector Element 2", expected, result.get(1), EQUAL);
        expected = vector1.get(0) * vector2.get(1) - vector1.get(1) * vector2.get(0);
        Verify_Int("Vector Element 3", expected, result.get(2), EQUAL);
    }

    Banner("Vector Concatenation");
    {
        Vector<int> result = vector1 << vector2;
        Verify_UInt("Vector Length", 2*length, result.length(), EQUAL);
        for (VectorLength_t i = 0; i < length; i++) {
            Verify_Int("Vector Element", vector1.get(i), result.get(i), EQUAL);
            Verify_Int("Vector Element", vector2.get(i), result.get(i+length), EQUAL);
        }
    }

    TestPostamble();
}

void Vector_MultiVector_Assignment_Operators() {
    const char *description = "Verify Vector MultiVector Assignment Operators modify Vector objects as expected";
    const char *for_set[] = {
        "Vector Assignment Addition", 
        "Vector Assignment Subtraction",
        "Vector Assignment Dot Multiplication",
        "Vector Assignment Cross Multiplication",
        "Vector Assignment Concatenation"
    };
    const char *preconditions[] = {
        "Valid Size",
        "Valid Vectors to Operate"
    };
    const char *results[] = {
        "Vector Modified from Addition with Expected Size",
        "Vector Modified from Subtraction with Expected Size",
        "Scalar Created from Dot Multiplication with Expected Size",
        "Vector Modified from Cross Multiplication with Expected Size",
        "Vector Modified from Concatenation with Expected Size"
    };

    TestPreamble(description, for_set, preconditions, results);

    // Size for all Vectors
    VectorLength_t length = 3;

    Print("Common Vector Parameters:");
    Print("Length: %u", length);

    // Operating Vectors
    Vector<int> vector1(length);
    Vector<int> vector2(length);

    for (VectorLength_t i = 0; i < length; i++) {
        const int value = i;
        vector1.set(i, value);
        vector2.set(i, 3*value - 1);
    }

    Print("Operating Vectors:");
    Print("Vector 1: [%d, %d, %d]", vector1.get(0), vector1.get(1), vector1.get(2));
    Print("Vector 2: [%d, %d, %d]", vector2.get(0), vector2.get(1), vector2.get(2));

    Banner("Vector Addition Assignment");
    {
        Vector<int> result = vector1;
        result += vector2;
        Verify_UInt("Vector Length", length, result.length(), EQUAL);
        for (VectorLength_t i = 0; i < length; i++) {
            Verify_Int("Vector Element", vector1.get(i) + vector2.get(i), result.get(i), EQUAL);
        }
    }

    Banner("Vector Subtraction Assignment");
    {
        Vector<int> result = vector1;
        result -= vector2;
        Verify_UInt("Vector Length", length, result.length(), EQUAL);
        for (VectorLength_t i = 0; i < length; i++) {
            Verify_Int("Vector Element", vector1.get(i) - vector2.get(i), result.get(i), EQUAL);
        }
    }

    Banner("Vector Dot Multiplication Assignment");
    {
        int result = vector1.dot(vector2);
        int expected = 0;
        for (VectorLength_t i = 0; i < length; i++) {
            expected += vector1.get(i) * vector2.get(i);
        }
        Verify_Int("Scalar Result", expected, result, EQUAL);
    }

    Banner("Vector Cross Multiplication Assignment");
    {
        Vector<int> result = vector1;
        result.cross(vector2);
        Verify_UInt("Vector Length", length, result.length(), EQUAL);

        int expected = vector1.get(1) * vector2.get(2) - vector1.get(2) * vector2.get(1);
        Verify_Int("Vector Element 1", expected, result.get(0), EQUAL);
        expected = vector1.get(2) * vector2.get(0) - vector1.get(0) * vector2.get(2);
        Verify_Int("Vector Element 2", expected, result.get(1), EQUAL);
        expected = vector1.get(0) * vector2.get(1) - vector1.get(1) * vector2.get(0);
        Verify_Int("Vector Element 3", expected, result.get(2), EQUAL);
    }

    Banner("Vector Concatenation Assignment");
    {
        Vector<int> result = vector1;
        result <<= vector2;
        Verify_UInt("Vector Length", 2*length, result.length(), EQUAL);
        for (VectorLength_t i = 0; i < length; i++) {
            Verify_Int("Vector Element", vector1.get(i), result.get(i), EQUAL);
            Verify_Int("Vector Element", vector2.get(i), result.get(i+length), EQUAL);
        }
    }

    TestPostamble();
}

void Vector_MultiVector_Element_Operators() {
    const char *description = "Verify Vector Element Operators create new Vector objects as expected";
    const char *for_set[] = {
        "Element Addition", 
        "Element Subtraction",
        "Element Multiplication",
        "Element Division",
        "Element Exponentiation"
    };
    const char *preconditions[] = {
        "Valid Size",
        "Valid Vectors to Operate"
    };
    const char *results[] = {
        "Vector Created from Addition with Expected Size",
        "Vector Created from Subtraction with Expected Size",
        "Vector Created from Multiplication with Expected Size",
        "Vector Created from Division with Expected Size",
        "Vector Created from Exponentiation with Expected Size"
    };

    TestPreamble(description, for_set, preconditions, results);

    // Size for all Vectors
    VectorLength_t length = 3;

    Print("Common Vector Parameters:");
    Print("Length: %u", length);

    // Operating Vectors
    Vector<int> vector(length);

    for (VectorLength_t i = 0; i < length; i++) {
        const int value = i;
        vector.set(i, 3*value - 1);
    }

    Print("Operating Vectors:");
    Print("Vector 1: [%d, %d, %d]", vector.get(0), vector.get(1), vector.get(2));

    Banner("Element Addition");
    {
        Vector<int> result = vector + 2;
        Verify_UInt("Vector Length", length, result.length(), EQUAL);
        for (VectorLength_t i = 0; i < length; i++) {
            Verify_Int("Vector Element", vector.get(i) + 2, result.get(i), EQUAL);
        }
    }

    Banner("Element Subtraction");
    {
        Vector<int> result = vector - 2;
        Verify_UInt("Vector Length", length, result.length(), EQUAL);
        for (VectorLength_t i = 0; i < length; i++) {
            Verify_Int("Vector Element", vector.get(i) - 2, result.get(i), EQUAL);
        }
    }

    Banner("Element Multiplication");
    {
        Vector<int> result = vector * 2;
        Verify_UInt("Vector Length", length, result.length(), EQUAL);
        for (VectorLength_t i = 0; i < length; i++) {
            Verify_Int("Vector Element", vector.get(i) * 2, result.get(i), EQUAL);
        }
    }

    Banner("Element Division");
    {
        Vector<int> result = vector / 2;
        Verify_UInt("Vector Length", length, result.length(), EQUAL);
        for (VectorLength_t i = 0; i < length; i++) {
            Verify_Int("Vector Element", vector.get(i) / 2, result.get(i), EQUAL);
        }
    }

    Banner("Element Exponentiation");
    {
        Vector<int> result = vector ^ 2;
        Verify_UInt("Vector Length", length, result.length(), EQUAL);
        for (VectorLength_t i = 0; i < length; i++) {
            Verify_Int_Within("Vector Element", vector.get(i) * vector.get(i), result.get(i), 1);
        }
    }

    TestPostamble();
}

void Vector_MultiVector_Element_Assignment_Operators() {
    const char *description = "Verify Vector Element Assignment Operators modify Vector objects as expected";
    const char *for_set[] = {
        "Element Assignment Addition", 
        "Element Assignment Subtraction",
        "Element Assignment Multiplication",
        "Element Assignment Division",
        "Element Assignment Exponentiation"
    };
    const char *preconditions[] = {
        "Valid Size",
        "Valid Vectors to Operate"
    };
    const char *results[] = {
        "Vector Modified from Addition with Expected Size",
        "Vector Modified from Subtraction with Expected Size",
        "Vector Modified from Multiplication with Expected Size",
        "Vector Modified from Division with Expected Size",
        "Vector Modified from Exponentiation with Expected Size"
    };

    TestPreamble(description, for_set, preconditions, results);

    // Size for all Vectors
    VectorLength_t length = 3;

    Print("Common Vector Parameters:");
    Print("Length: %u", length);

    // Operating Vectors
    Vector<int> vector(length);

    for (VectorLength_t i = 0; i < length; i++) {
        const int value = i;
        vector.set(i, 3*value - 1);
    }

    Print("Operating Vectors:");
    Print("Vector 1: [%d, %d, %d]", vector.get(0), vector.get(1), vector.get(2));

    Banner("Element Assignment Addition");
    {
        Vector<int> result = vector;
        result += 2;
        Verify_UInt("Vector Length", length, result.length(), EQUAL);
        for (VectorLength_t i = 0; i < length; i++) {
            Verify_Int("Vector Element", vector.get(i) + 2, result.get(i), EQUAL);
        }
    }

    Banner("Element Assignment Subtraction");
    {
        Vector<int> result = vector;
        result -= 2;
        Verify_UInt("Vector Length", length, result.length(), EQUAL);
        for (VectorLength_t i = 0; i < length; i++) {
            Verify_Int("Vector Element", vector.get(i) - 2, result.get(i), EQUAL);
        }
    }

    Banner("Element Assignment Multiplication");
    {
        Vector<int> result = vector;
        result *= 2;
        Verify_UInt("Vector Length", length, result.length(), EQUAL);
        for (VectorLength_t i = 0; i < length; i++) {
            Verify_Int("Vector Element", vector.get(i) * 2, result.get(i), EQUAL);
        }
    }

    Banner("Element Assignment Division");
    {
        Vector<int> result = vector;
        result /= 2;
        Verify_UInt("Vector Length", length, result.length(), EQUAL);
        for (VectorLength_t i = 0; i < length; i++) {
            Verify_Int("Vector Element", vector.get(i) / 2, result.get(i), EQUAL);
        }
    }

    Banner("Element Assignment Exponentiation");
    {
        Vector<int> result = vector;
        result ^= 2;
        Verify_UInt("Vector Length", length, result.length(), EQUAL);
        for (VectorLength_t i = 0; i < length; i++) {
            Verify_Int_Within("Vector Element", vector.get(i) * vector.get(i), result.get(i), 1);
        }
    }

    TestPostamble();
}

void Vector_Operations() {
    const char *description = "Verify Vector Operations output as expected";
    const char *for_set[] = {
        "Magnitude", 
        "Normalize",
        "isZero",
        "isOne",
        "Length"
    };
    const char *preconditions[] = {
        "Valid Size",
        "Valid Vectors to Operate"
    };
    const char *results[] = {
        "Scalar Magnitude of Vector",
        "Vector Normalized to Unit Vector",
        "Boolean if Vector is Zero",
        "Boolean if Vector is One",
        "Scalar Length of Vector"
    };

    TestPreamble(description, for_set, preconditions, results);

    // Size for all Vectors
    VectorLength_t length = 3;

    Print("Common Vector Parameters:");
    Print("Length: %u", length);

    // Operating Vectors
    Vector<int> vector(length);

    for (VectorLength_t i = 0; i < length; i++) {
        const int value = i;
        vector.set(i, 3*value - 1);
    }

    Print("Operating Vectors:");
    Print("Vector 1: [%d, %d, %d]", vector.get(0), vector.get(1), vector.get(2));

    Banner("Magnitude");
    {
        double result = vector.magnitude();
        double expected = sqrt(dot(vector, vector));
        Verify_Double_Within("Vector Magnitude", expected, result, fabs(0.001 * expected));
    }

    Banner("Normalize");
    {
        Vector<double> result = vector.normalize();
        double magnitude = vector.magnitude();
        for (VectorLength_t i = 0; i < length; i++) {
            double expected = vector.get(i) / magnitude;
            Verify_Double_Within("Vector Element", expected, result.get(i), fabs(0.001 * expected));
        }
    }

    Banner("isZero");
    {
        Vector<int> zero(length);
        Verify("Zero Vector", true, zero.isZero(), EQUAL);
        Verify("Non-Zero Vector", false, vector.isZero(), EQUAL);
    }

    Banner("isOne");
    {
        Vector<int> one(length);
        one += 1;
        Verify("One Vector", true, one.isOne(), EQUAL);
        Verify("Non-One Vector", false, vector.isOne(), EQUAL);
    }

    Banner("Length");
    {
        Verify_UInt("Vector Length", length, vector.length(), EQUAL);
    }

    TestPostamble();
}

void Vector_Test() {

    Vector_Constructor();
    Vector_MultiVector_Operators();
    Vector_MultiVector_Assignment_Operators();
    Vector_MultiVector_Element_Operators();
    Vector_MultiVector_Element_Assignment_Operators();
    Vector_Operations();

}