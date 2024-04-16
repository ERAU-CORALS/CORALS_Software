/**
 ********************************************************************************
 * @file    Vector.tpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Template implementation for Vector class
 * @version 1.0
 * @date    2024-04-12
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __VECTOR_TPP__
#define __VECTOR_TPP__

#include <assert.h>
#include <math.h>

namespace DataStructures {
namespace Vector {

template<typename T> class Vector;

using VectorLength_t = unsigned int;

namespace Vector_Operations {

template<typename T> Vector<T> add(const Vector<T> &vector1, const Vector<T> &vector2);
template<typename T> Vector<T> subtract(const Vector<T> &vector1, const Vector<T> &vector2);
template<typename T> T dot(const Vector<T> &vector1, const Vector<T> &vector2);
template<typename T> Vector<T> cross(const Vector<T> &vector1, const Vector<T> &vector2);
template<typename T> Vector<T> concat(const Vector<T> &vector1, const Vector<T> &vector2);
template<typename T> double magnitude(const Vector<T> &vector);
template<typename T> Vector<double> normalize(const Vector<T> &vector);

} // end namespace Vector_Operations

namespace Vector_Property {

template<typename T> bool isZero(const Vector<T> &vector);
template<typename T> bool isOne(const Vector<T> &vector);

} // end namespace Vector_Property

namespace Element_Operations {

template<typename T> Vector<T> add(const Vector<T> &vector, const T value);
template<typename T> Vector<T> subtract(const Vector<T> &vector, const T value);
template<typename T> Vector<T> multiply(const Vector<T> &vector, const T value);
template<typename T> Vector<T> divide(const Vector<T> &vector, const T value);
template<typename T> Vector<T> power(const Vector<T> &vector, const T value);
        
} // end namespace Element_Operation

/**
 ********************************************************************************
 * @brief   Vector Class
 * @tparam  T
 ******************************************************************************** 
**/
template<typename T>
class Vector {
    public:
    // Constructors

        /**
         ********************************************************************************
         * @brief   Construct a new Vector
         ********************************************************************************
         * @param[in]   size    TYPE: const VectorLength_t
         ********************************************************************************
        **/
        Vector(const VectorLength_t size) {
            m_size = size;
            initialize();
        }

        /**
         ********************************************************************************
         * @brief   Copy a constant Vector object
         ********************************************************************************
         * @param[in]   vector  TYPE: const Vector<T>&
         ********************************************************************************
        **/
        Vector(const Vector<T> &vector) {
            m_size = vector.m_size;
            initialize(false);
            copy(vector);
        }

        /**
         ********************************************************************************
         * @brief   Assign a Vector object
         ********************************************************************************
         * @param[in]   vector  TYPE: const Vector<T>&
         * @return  Vector<T>&
         ********************************************************************************
        **/
        Vector<T>& operator=(const Vector<T> &vector) {
            if (this == &vector) return *this;
            destroy();
            m_size = vector.m_size;
            initialize(false);
            copy(vector);
            return *this;
        }

    // Destructor
        /**
         ********************************************************************************
         * @brief   Decostruct the Vector object
         ********************************************************************************
        **/
        virtual ~Vector() {
            destroy();
        }

    // MultiVector Operations
        /**
         ********************************************************************************
         * @brief   Add two vectors
         ********************************************************************************
         * @param[in]   vector  TYPE: const Vector<T>&
         * @return      Vector<T>
         ********************************************************************************
        **/
        inline Vector<T> operator+(const Vector<T> &vector) const {
            return Vector_Operations::add<T>(*this, vector);
        }

        /**
         ********************************************************************************
         * @brief   Subtract two vectors
         ********************************************************************************
         * @param[in]   vector  TYPE: const Vector<T>&
         * @return      Vector<T>
         ********************************************************************************
        **/
        inline Vector<T> operator-(const Vector<T> &vector) const {
            return Vector_Operations::subtract<T>(*this, vector);
        }

        /**
         ********************************************************************************
         * @brief   Dot a vector with this vector
         ********************************************************************************
         * @param[in]   vector  TYPE: const Vector<T>&
         ********************************************************************************
        **/
        inline T dot(const Vector<T> &vector) const {
            return Vector_Operations::dot<T>(*this, vector);
        }

        /**
         ********************************************************************************
         * @brief   Cross a vector with this vector
         ********************************************************************************
         * @param[in]   vector  TYPE: const Vector<T>&
         ********************************************************************************
        **/
        inline Vector<T> operator*(const Vector<T> &vector) const {
            return Vector_Operations::cross<T>(*this, vector);
        }

        /**
         ********************************************************************************
         * @brief   Concatenate two vectors
         ********************************************************************************
         * @param[in]   vector  TYPE: const Vector<T>&
         * @return      Vector<T>
         ********************************************************************************
        **/
        inline Vector<T> operator<<(const Vector<T> &vector) const {
            return Vector_Operations::concat<T>(*this, vector);
        }

    // MultiVector Assignment Operations
        /**
         ********************************************************************************
         * @brief   Add a vector to this vector
         ********************************************************************************
         * @param[in]   vector  TYPE: const Vector<T>&
         ********************************************************************************
        **/
        inline void operator+=(const Vector<T> &vector) {
            *this = Vector_Operations::add<T>(*this, vector);
        } 

        /**
         ********************************************************************************
         * @brief   Subtract a vector from this vector
         ********************************************************************************
         * @param[in]   vector  TYPE: const Vector<T>&
         ********************************************************************************
        **/
        inline void operator-=(const Vector<T> &vector) {
            *this = Vector_Operations::subtract<T>(*this, vector);
        }
        
        /**
         ********************************************************************************
         * @brief   Cross a vector with this vector
         ********************************************************************************
         * @param[in]   vector  TYPE: const Vector<T>&
         ********************************************************************************
        **/
        inline void operator*=(const Vector<T> &vector) {
            *this = Vector_Operations::cross<T>(*this, vector);
        }

        /**
         ********************************************************************************
         * @brief   Concatenate a vector with this vector
         ********************************************************************************
         * @param[in]   vector  TYPE: const Vector<T>&
         ********************************************************************************
        **/
        inline void operator<<=(const Vector<T> &vector) {
            *this = Vector_Operations::concat<T>(*this, vector);
        }

    // Element Operations
        /**
         ********************************************************************************
         * @brief   Add a value to each element in the vector
         ********************************************************************************
         * @param[in]   value   TYPE: const T&
         * @return      Vector<T>
         ********************************************************************************
        **/
        inline Vector<T> operator+(const T value) const {
            return Element_Operations::add<T>(*this, value);
        }

        /**
         ********************************************************************************
         * @brief   Subtract a value from each element in the vector
         ********************************************************************************
         * @param[in]   value   TYPE: const T&
         * @return      Vector<T>
         ********************************************************************************
        **/
        inline Vector<T> operator-(const T value) const {
            return Element_Operations::subtract<T>(*this, value);
        }

        /**
         ********************************************************************************
         * @brief   Multiply each element in the vector by a value
         ********************************************************************************
         * @param[in]   value   TYPE: const T&
         * @return      Vector<T>
         ********************************************************************************
        **/
        inline Vector<T> operator*(const T value) const {
            return Element_Operations::multiply<T>(*this, value);
        }

        /**
         ********************************************************************************
         * @brief   Divide each element in the vector by a value
         ********************************************************************************
         * @param[in]   value   TYPE: const T&
         * @return      Vector<T>
         ********************************************************************************
        **/
        inline Vector<T> operator/(const T value) const {
            return Element_Operations::divide<T>(*this, value);
        }

        /**
         ********************************************************************************
         * @brief   Raise each element in the vector to a power
         ********************************************************************************
         * @param[in]   value   TYPE: const T&
         * @return      Vector<T>
         ********************************************************************************
        **/
        inline Vector<T> operator^(const T value) const {
            return Element_Operations::power<T>(*this, value);
        }

    // Element Assignment Operations
        /**
         ********************************************************************************
         * @brief   Add a value to each element in the vector
         ********************************************************************************
         * @param[in]   value   TYPE: const T&
         ********************************************************************************
        **/
        inline void operator+=(const T value) {
            *this = Element_Operations::add<T>(*this, value);
        }

        /**
         ********************************************************************************
         * @brief   Subtract a value from each element in the vector
         ********************************************************************************
         * @param[in]   value   TYPE: const T&
         ********************************************************************************
        **/
        inline void operator-=(const T value) {
            *this = Element_Operations::subtract<T>(*this, value);
        }

        /**
         ********************************************************************************
         * @brief   Multiply each element in the vector by a value
         ********************************************************************************
         * @param[in]   value   TYPE: const T&
         ********************************************************************************
        **/
        inline void operator*=(const T value) {
            *this = Element_Operations::multiply<T>(*this, value);
        }

        /**
         ********************************************************************************
         * @brief   Divide each element in the vector by a value
         ********************************************************************************
         * @param[in]   value   TYPE: const T&
         ********************************************************************************
        **/
        inline void operator/=(const T value) {
            *this = Element_Operations::divide<T>(*this, value);
        }

        /**
         ********************************************************************************
         * @brief   Raise each element in the vector to a power
         ********************************************************************************
         * @param[in]   value   TYPE: const T&
         ********************************************************************************
        **/
        inline void operator^=(const T value) {
            *this = Element_Operations::power<T>(*this, value);
        }

    // Vector Operations
        /**
         ********************************************************************************
         * @brief   Find the magnitude of the vector
         ********************************************************************************
         * @return  double
         ********************************************************************************
        **/
        inline double magnitude() const {
            return Vector_Operations::magnitude<T>(*this);
        }

        /**
         ********************************************************************************
         * @brief   Normalize the vector
         ********************************************************************************
         * @return  Vector<double>
         ********************************************************************************
        **/
        inline Vector<double> normalize() const {
            return Vector_Operations::normalize<T>(*this);
        }

    // Vector Properties
        /**
         ********************************************************************************
         * @brief   Check if the vector is zero
         ********************************************************************************
         * @return  bool
         ********************************************************************************
        **/
        inline bool isZero() const {
            return Vector_Property::isZero<T>(*this);
        }

        /**
         ********************************************************************************
         * @brief   Check if the vector is one
         ********************************************************************************
         * @return  bool
         ********************************************************************************
        **/
        inline bool isOne() const {
            return Vector_Property::isOne<T>(*this);
        }

        /**
         ********************************************************************************
         * @brief   Get the length of the vector
         ********************************************************************************
         * @return  VectorLength_t
         ********************************************************************************
        **/
        inline VectorLength_t length() const {
            return m_size;
        }

    // Element Access
        /**
         ********************************************************************************
         * @brief   Get the value of an element in the vector
         ********************************************************************************
         * @param[in]   index   TYPE: const VectorLength_t
         * @return  T
         ********************************************************************************
        **/
        inline T get(const VectorLength_t index) const {
            assert(index < m_size);
            return m_data[index];
        }

        /**
         ********************************************************************************
         * @brief   Set the value of an element in the vector
         ********************************************************************************
         * @param[in]   index   TYPE: const VectorLength_t
         * @param[in]   value   TYPE: const T&
         ********************************************************************************
        **/
        inline void set(const VectorLength_t index, const T value) {
            assert(index < m_size);
            m_data[index] = value;
        }

    // Vector Friend Functions
        
        template<typename U> friend Vector<U> Vector_Operations::add(const Vector<U> &vector1, const Vector<U> &vector2);
        template<typename U> friend Vector<U> Vector_Operations::subtract(const Vector<U> &vector1, const Vector<U> &vector2);
        template<typename U> friend U Vector_Operations::dot(const Vector<U> &vector1, const Vector<U> &vector2);
        template<typename U> friend Vector<U> Vector_Operations::cross(const Vector<U> &vector1, const Vector<U> &vector2);
        template<typename U> friend Vector<U> Vector_Operations::concat(const Vector<U> &vector1, const Vector<U> &vector2);
        template<typename U> friend double Vector_Operations::magnitude(const Vector<U> &vector);
        template<typename U> friend Vector<double> Vector_Operations::normalize(const Vector<U> &vector);

        template<typename U> friend bool Vector_Property::isZero(const Vector<U> &vector);
        template<typename U> friend bool Vector_Property::isOne(const Vector<U> &vector);

        template<typename U> friend Vector<U> Element_Operations::add(const Vector<U> &vector, const U value);
        template<typename U> friend Vector<U> Element_Operations::subtract(const Vector<U> &vector, const U value);
        template<typename U> friend Vector<U> Element_Operations::multiply(const Vector<U> &vector, const U value);
        template<typename U> friend Vector<U> Element_Operations::divide(const Vector<U> &vector, const U value);
        template<typename U> friend Vector<U> Element_Operations::power(const Vector<U> &vector, const U value);

    private:
        VectorLength_t m_size;
        T *m_data;

    // Helper Functions
        /**
         ********************************************************************************
         * @brief   Initialize the vector
         ********************************************************************************
         * @param[in]   zeroize TYPE: bool
         ********************************************************************************
         * @note    If zeroize is true, the vector will be initialized to zero
         ********************************************************************************
        **/
        void initialize(bool zeroize = true) {
            m_data = new T[m_size];
            if (zeroize) {
                for (VectorLength_t i = 0; i < m_size; i++) {
                    m_data[i] = 0;
                }
            }
        }

        /**
         ********************************************************************************
         * @brief   Copy a vector
         ********************************************************************************
         * @param[in]   vector  TYPE: const Vector<T>&
         ********************************************************************************
        **/
        void copy(const Vector<T> &vector) {
            // Vectors must be the same size
            assert(m_size == vector.m_size);

            for (VectorLength_t i = 0; i < m_size; i++) {
                m_data[i] = vector.m_data[i];
            }
        }

        /**
         ********************************************************************************
         * @brief   Destroy the vector
         ********************************************************************************
        **/
        void destroy() {
            delete[] m_data;
        }
};

namespace Vector_Operations {

/**
 ********************************************************************************
 * @brief   Add two vectors
 ********************************************************************************
 * @tparam      T 
 * @param[in]   vector1 TYPE: const Vector<T>&
 * @param[in]   vector2 TYPE: const Vector<T>&
 * @return      Vector<T>
 ******************************************************************************** 
**/
template<typename T> Vector<T> add(const Vector<T> &vector1, const Vector<T> &vector2) {
    // Vectors must be the same size
    assert(vector1.m_size == vector2.m_size);

    Vector<T> result(vector1);
    for (VectorLength_t i = 0; i < vector1.m_size; i++) {
        result.m_data[i] += vector2.m_data[i];
    }

    return result;
}

/**
 ********************************************************************************
 * @brief   Subtract two vectors
 ********************************************************************************
 * @tparam      T 
 * @param[in]   vector1 TYPE: const Vector<T>&
 * @param[in]   vector2 TYPE: const Vector<T>&
 * @return      Vector<T>
 ********************************************************************************
**/
template<typename T> Vector<T> subtract(const Vector<T> &vector1, const Vector<T> &vector2) {
    // Vectors must be the same size
    assert(vector1.m_size == vector2.m_size);

    Vector<T> result(vector1);
    for (VectorLength_t i = 0; i < vector1.m_size; i++) {
        result.m_data[i] -= vector2.m_data[i];
    }

    return result;
}

/**
 ********************************************************************************
 * @brief   Dot two vectors
 ********************************************************************************
 * @tparam      T 
 * @param[in]   vector1 TYPE: const Vector<T>&
 * @param[in]   vector2 TYPE: const Vector<T>&
 * @return      T
 ********************************************************************************
**/
template<typename T> T dot(const Vector<T> &vector1, const Vector<T> &vector2) {
    // Vectors must be the same size
    assert(vector1.m_size == vector2.m_size);

    T result = 0;
    for (VectorLength_t i = 0; i < vector1.m_size; i++) {
        result += vector1.m_data[i] * vector2.m_data[i];
    }

    return result;
}

/**
 ********************************************************************************
 * @brief   Cross two vectors
 ********************************************************************************
 * @tparam      T 
 * @param[in]   vector1 TYPE: const Vector<T>&
 * @param[in]   vector2 TYPE: const Vector<T>&
 * @return      Vector<T>
 ********************************************************************************
**/
template<typename T> Vector<T> cross(const Vector<T> &vector1, const Vector<T> &vector2) {
    // Vectors must be the same size
    assert(vector1.m_size == vector2.m_size);

    Vector<T> result(vector1.m_size);
    result.m_data[0] = vector1.m_data[1] * vector2.m_data[2] - vector1.m_data[2] * vector2.m_data[1];
    result.m_data[1] = vector1.m_data[2] * vector2.m_data[0] - vector1.m_data[0] * vector2.m_data[2];
    result.m_data[2] = vector1.m_data[0] * vector2.m_data[1] - vector1.m_data[1] * vector2.m_data[0];

    return result;
}

/**
 ********************************************************************************
 * @brief   Concatenate two vectors
 ********************************************************************************
 * @tparam      T 
 * @param[in]   vector1 TYPE: const Vector<T>&
 * @param[in]   vector2 TYPE: const Vector<T>&
 * @return      Vector<T>
 ********************************************************************************
**/
template<typename T> Vector<T> concat(const Vector<T> &vector1, const Vector<T> &vector2) {
    Vector<T> result(vector1.m_size + vector2.m_size);
    for (VectorLength_t i = 0; i < vector1.m_size; i++) {
        result.m_data[i] = vector1.m_data[i];
    }
    for (VectorLength_t i = 0; i < vector2.m_size; i++) {
        result.m_data[vector1.m_size + i] = vector2.m_data[i];
    }

    return result;
}

/**
 ********************************************************************************
 * @brief   Find the magnitude of the vector
 ********************************************************************************
 * @tparam      T 
 * @param[in]   vector  TYPE: const Vector<T>&
 * @return      double
 ********************************************************************************
**/
template<typename T> double magnitude(const Vector<T> &vector) {
    double result = 0;
    for (VectorLength_t i = 0; i < vector.m_size; i++) {
        result += vector.m_data[i] * vector.m_data[i];
    }

    return sqrt(result);
}

/**
 ********************************************************************************
 * @brief   Normalize the vector
 ********************************************************************************
 * @tparam      T 
 * @param[in]   vector  TYPE: const Vector<T>&
 * @return      Vector<double>
 ********************************************************************************
**/
template<typename T> Vector<double> normalize(const Vector<T> &vector) {
    Vector<double> result(vector);
    result /= vector.magnitude();

    return result;
}

} // end namespace Vector_Operations

namespace Vector_Property {

/**
 ********************************************************************************
 * @brief   Check if the vector is zero
 ********************************************************************************
 * @tparam      T 
 * @param[in]   vector  TYPE: const Vector<T>&
 * @return      bool
 ********************************************************************************
**/
template<typename T> bool isZero(const Vector<T> &vector) {
    for (VectorLength_t i = 0; i < vector.m_size; i++) {
        if (vector.m_data[i] != 0) return false;
    }

    return true;
}

/**
 ********************************************************************************
 * @brief   Check if the vector is one
 ********************************************************************************
 * @tparam      T 
 * @param[in]   vector  TYPE: const Vector<T>&
 * @return      bool
 ********************************************************************************
**/
template<typename T> bool isOne(const Vector<T> &vector) {
    for (VectorLength_t i = 0; i < vector.m_size; i++) {
        if (vector.m_data[i] != 1) return false;
    }

    return true;
}

} // end namespace Vector_Property

namespace Element_Operations {

/**
 ********************************************************************************
 * @brief   Add a value to each element in the vector
 ********************************************************************************
 * @tparam      T 
 * @param[in]   vector  TYPE: const Vector<T>&
 * @param[in]   value   TYPE: const T&
 * @return      Vector<T>
 ********************************************************************************
**/
template<typename T> Vector<T> add(const Vector<T> &vector, const T value) {
    Vector<T> result(vector);
    for (VectorLength_t i = 0; i < vector.m_size; i++) {
        result.m_data[i] += value;
    }

    return result;
}

/**
 ********************************************************************************
 * @brief   Subtract a value from each element in the vector
 ********************************************************************************
 * @tparam      T 
 * @param[in]   vector  TYPE: const Vector<T>&
 * @param[in]   value   TYPE: const T&
 * @return      Vector<T>
 ********************************************************************************
**/
template<typename T> Vector<T> subtract(const Vector<T> &vector, const T value) {
    Vector<T> result(vector);
    for (VectorLength_t i = 0; i < vector.m_size; i++) {
        result.m_data[i] -= value;
    }

    return result;
}

/**
 ********************************************************************************
 * @brief   Multiply each element in the vector by a value
 ********************************************************************************
 * @tparam      T 
 * @param[in]   vector  TYPE: const Vector<T>&
 * @param[in]   value   TYPE: const T&
 * @return      Vector<T>
 ********************************************************************************
**/
template<typename T> Vector<T> multiply(const Vector<T> &vector, const T value) {
    Vector<T> result(vector);
    for (VectorLength_t i = 0; i < vector.m_size; i++) {
        result.m_data[i] *= value;
    }

    return result;
}

/**
 ********************************************************************************
 * @brief   Divide each element in the vector by a value
 ********************************************************************************
 * @tparam      T 
 * @param[in]   vector  TYPE: const Vector<T>&
 * @param[in]   value   TYPE: const T&
 * @return      Vector<T>
 ********************************************************************************
**/
template<typename T> Vector<T> divide(const Vector<T> &vector, const T value) {
    Vector<T> result(vector);
    for (VectorLength_t i = 0; i < vector.m_size; i++) {
        result.m_data[i] /= value;
    }

    return result;
}

/**
 ********************************************************************************
 * @brief   Raise each element in the vector to a power
 ********************************************************************************
 * @tparam      T 
 * @param[in]   vector  TYPE: const Vector<T>&
 * @param[in]   value   TYPE: const T&
 * @return      Vector<T>
 ********************************************************************************
**/
template<typename T> Vector<T> power(const Vector<T> &vector, const T value) {
    Vector<T> result(vector);
    for (VectorLength_t i = 0; i < vector.m_size; i++) {
        result.m_data[i] = pow(result.m_data[i], value);
    }

    return result;
}

} // end namespace Element_Operation

} // end namespace Vector
} // end namespace DataStructures

#endif // __VECTOR_TPP__