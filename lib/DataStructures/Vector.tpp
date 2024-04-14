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

using VectorLength_t = unsigned int;

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
        Vector<T> operator+(const Vector<T> &vector) {
            // Vectors must be the same size
            assert(m_size == vector.m_size);

            Vector<T> result(m_size);
            for (VectorLength_t i = 0; i < m_size; i++) {
                result.m_data[i] = m_data[i] + vector.m_data[i];
            }
            return result;
        }

        /**
         ********************************************************************************
         * @brief   Subtract two vectors
         ********************************************************************************
         * @param[in]   vector  TYPE: const Vector<T>&
         * @return      Vector<T>
         ********************************************************************************
        **/
        Vector<T> operator-(const Vector<T> &vector) {
            // Vectors must be the same size
            assert(m_size == vector.m_size);

            Vector<T> result(m_size);
            for (VectorLength_t i = 0; i < m_size; i++) {
                result.m_data[i] = m_data[i] - vector.m_data[i];
            }
            return result;
        }

        /**
         ********************************************************************************
         * @brief   Find the dot product of two vectors
         ********************************************************************************
         * @param[in]   scalar  TYPE: const T
         * @return      T
         ********************************************************************************
        **/
        friend T dot(const Vector<T> &vector1, const Vector<T> &vector2) {
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
         * @brief   Find the cross product of two vectors
         ********************************************************************************
         * @param[in]   vector1 TYPE: const Vector<T>&
         * @param[in]   vector2 TYPE: const Vector<T>&
         * @return      Vector<T>
         ********************************************************************************
        **/
        friend Vector<T> cross(const Vector<T> &vector1, const Vector<T> &vector2) {
            // Vectors must be the same size
            assert(vector1.m_size == vector2.m_size);

            // Vectors must be 3D
            assert(vector1.m_size == 3);

            Vector<T> result(3);
            result.m_data[0] = vector1.m_data[1] * vector2.m_data[2] - vector1.m_data[2] * vector2.m_data[1];
            result.m_data[1] = vector1.m_data[2] * vector2.m_data[0] - vector1.m_data[0] * vector2.m_data[2];
            result.m_data[2] = vector1.m_data[0] * vector2.m_data[1] - vector1.m_data[1] * vector2.m_data[0];

            return result;
        }

        /**
         ********************************************************************************
         * @brief   Concatenate two vectors
         ********************************************************************************
         * @param[in]   vector  TYPE: const Vector<T>&
         * @return      Vector<T>
         ********************************************************************************
        **/
        Vector<T> operator<<(const Vector<T> &vector) {
            Vector<T> result(m_size + vector.m_size);

            for (VectorLength_t i = 0; i < m_size; i++) {
                result.m_data[i] = m_data[i];
            }
            for (VectorLength_t i = 0; i < vector.m_size; i++) {
                result.m_data[m_size + i] = vector.m_data[i];
            }

            return result;
        }
        // Alternative syntax
        Vector<T> operator||(const Vector<T> &vector) {
            return *this << vector;
        }

    // MultiVector Assignment Operations
        /**
         ********************************************************************************
         * @brief   Add a vector to this vector
         ********************************************************************************
         * @param[in]   vector  TYPE: const Vector<T>&
         * @return      Vector<T>&
         ********************************************************************************
        **/
        Vector<T>& operator+=(const Vector<T> &vector) {
            // Vectors must be the same size
            assert(m_size == vector.m_size);

            for (VectorLength_t i = 0; i < m_size; i++) {
                m_data[i] += vector.m_data[i];
            }

            return *this;
        }

        /**
         ********************************************************************************
         * @brief   Subtract a vector from this vector
         ********************************************************************************
         * @param[in]   vector  TYPE: const Vector<T>&
         * @return      Vector<T>&
         ********************************************************************************
        **/
        Vector<T>& operator-=(const Vector<T> &vector) {
            // Vectors must be the same size
            assert(m_size == vector.m_size);

            for (VectorLength_t i = 0; i < m_size; i++) {
                m_data[i] -= vector.m_data[i];
            }

            return *this;
        }

        /**
         ********************************************************************************
         * @brief   Dot a vector with this vector
         ********************************************************************************
         * @param[in]   vector  TYPE: const Vector<T>&
         ********************************************************************************
        **/
        void dot(const Vector<T> &vector) {
            // Vectors must be the same size
            assert(m_size == vector.m_size);

            for (VectorLength_t i = 0; i < m_size; i++) {
                m_data[i] *= vector.m_data[i];
            }
        }

        /**
         ********************************************************************************
         * @brief   Cross a vector with this vector
         ********************************************************************************
         * @param[in]   vector  TYPE: const Vector<T>&
         ********************************************************************************
        **/
        void cross(const Vector<T> &vector) {
            // Vectors must be the same size
            assert(m_size == vector.m_size);

            // Vectors must be 3D
            assert(m_size == 3);

            const T x = m_data[0];
            const T y = m_data[1];
            const T z = m_data[2];
            m_data[0] = y * vector.m_data[2] - z * vector.m_data[1];
            m_data[1] = z * vector.m_data[0] - x * vector.m_data[2];
            m_data[2] = x * vector.m_data[1] - y * vector.m_data[0];
        }

        /**
         ********************************************************************************
         * @brief   Concatenate a vector with this vector
         ********************************************************************************
         * @param[in]   vector  TYPE: const Vector<T>&
         ********************************************************************************
        **/
        void operator<<=(const Vector<T> &vector) {
            *this = *this << vector;
        }
        // Alternative syntax
        void operator|=(const Vector<T> &vector) {
            *this <<= vector;
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
        Vector<T> operator+(const T &value) {
            Vector<T> result(*this);
            result += value;
            return result;
        }

        /**
         ********************************************************************************
         * @brief   Subtract a value from each element in the vector
         ********************************************************************************
         * @param[in]   value   TYPE: const T&
         * @return      Vector<T>
         ********************************************************************************
        **/
        Vector<T> operator-(const T &value) {
            Vector<T> result(*this);
            result -= value;
            return result;
        }

        /**
         ********************************************************************************
         * @brief   Multiply each element in the vector by a value
         ********************************************************************************
         * @param[in]   value   TYPE: const T&
         * @return      Vector<T>
         ********************************************************************************
        **/
        Vector<T> operator*(const T &value) {
            Vector<T> result(*this);
            result *= value;
            return result;
        }

        /**
         ********************************************************************************
         * @brief   Divide each element in the vector by a value
         ********************************************************************************
         * @param[in]   value   TYPE: const T&
         * @return      Vector<T>
         ********************************************************************************
        **/

        Vector<T> operator/(const T &value) {
            Vector<T> result(*this);
            result /= value;
            return result;
        }

        /**
         ********************************************************************************
         * @brief   Raise each element in the vector to a power
         ********************************************************************************
         * @param[in]   value   TYPE: const T&
         * @return      Vector<T>
         ********************************************************************************
        **/
        Vector<T> operator^(const T &value) {
            Vector<T> result(*this);
            result ^= value;
            return result;
        }

    // Element Assignment Operations
        /**
         ********************************************************************************
         * @brief   Add a value to each element in the vector
         ********************************************************************************
         * @param[in]   value   TYPE: const T&
         ********************************************************************************
        **/
        void operator+=(const T &value) {
            for (VectorLength_t i = 0; i < m_size; i++) {
                m_data[i] += value;
            }
        }

        /**
         ********************************************************************************
         * @brief   Subtract a value from each element in the vector
         ********************************************************************************
         * @param[in]   value   TYPE: const T&
         ********************************************************************************
        **/
        void operator-=(const T &value) {
            for (VectorLength_t i = 0; i < m_size; i++) {
                m_data[i] -= value;
            }
        }

        /**
         ********************************************************************************
         * @brief   Multiply each element in the vector by a value
         ********************************************************************************
         * @param[in]   value   TYPE: const T&
         ********************************************************************************
        **/
        void operator*=(const T &value) {
            for (VectorLength_t i = 0; i < m_size; i++) {
                m_data[i] *= value;
            }
        }

        /**
         ********************************************************************************
         * @brief   Divide each element in the vector by a value
         ********************************************************************************
         * @param[in]   value   TYPE: const T&
         ********************************************************************************
        **/
        void operator/=(const T &value) {
            for (VectorLength_t i = 0; i < m_size; i++) {
                m_data[i] /= value;
            }
        }

        /**
         ********************************************************************************
         * @brief   Raise each element in the vector to a power
         ********************************************************************************
         * @param[in]   value   TYPE: const T&
         ********************************************************************************
        **/
        void operator^=(const T &value) {
            for (VectorLength_t i = 0; i < m_size; i++) {
                m_data[i] = pow(m_data[i], value);
            }
        }

    // Vector Operations
        /**
         ********************************************************************************
         * @brief   Find the magnitude of the vector
         ********************************************************************************
         * @return  T
         ********************************************************************************
        **/
        double magnitude() {
            T result = 0;
            for (VectorLength_t i = 0; i < m_size; i++) {
                result += m_data[i] * m_data[i];
            }
            return sqrt(result);
        }

        /**
         ********************************************************************************
         * @brief   Normalize the vector
         ********************************************************************************
         * @return  Vector<T>
         ********************************************************************************
        **/
        Vector<T> normalize() {
            Vector<double> result(m_size);
            for (VectorLength_t i = 0; i < m_size; i++) {
                result.m_data[i] = m_data[i];
            }
            result /= magnitude();
            return result;
        }

    // Vector Properties
        /**
         ********************************************************************************
         * @brief   Check if the vector is zero
         ********************************************************************************
         * @return  bool
         ********************************************************************************
        **/
        bool isZero() {
            for (VectorLength_t i = 0; i < m_size; i++) {
                if (m_data[i] != 0) {
                    return false;
                }
            }
            return true;
        }

        /**
         ********************************************************************************
         * @brief   Check if the vector is one
         ********************************************************************************
         * @return  bool
         ********************************************************************************
        **/
        bool isOne() {
            for (VectorLength_t i = 0; i < m_size; i++) {
                if (m_data[i] != 1) {
                    return false;
                }
            }
            return true;
        }

        /**
         ********************************************************************************
         * @brief   Get the length of the vector
         ********************************************************************************
         * @return  VectorLength_t
         ********************************************************************************
        **/
        VectorLength_t length() {
            return m_size;
        }
        // Alternative syntax
        VectorLength_t size() {
            return length();
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
        T get(const VectorLength_t index) {
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
        void set(const VectorLength_t index, const T &value) {
            assert(index < m_size);
            m_data[index] = value;
        }

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
         * @note    If zeroize is true, the matrix will be initialized to zero
         ********************************************************************************
        **/
        void initialize(bool zeroize = true) {
            m_data = new T(m_size);
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
         * @param[in]   matrix  TYPE: const Vector<T>&
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

} // end namespace DataStructures

#endif // __VECTOR_TPP__