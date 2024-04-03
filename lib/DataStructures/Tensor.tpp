/**
 ********************************************************************************
 * @file    Tensor.tpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Template implementation for 2-D Tensor ABC
 * @version 1.0
 * @date    2024-04-02
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __TENSOR_TPP__
#define __TENSOR_TPP__

#include <math.h>
#include <assert.h>

namespace DataStructures {

using TensorLength_t = unsigned int;

struct TensorSize_t {
    TensorLength_t rows;
    TensorLength_t columns;
};

template<typename T>
class Tensor {
    template<typename U>
    friend Tensor<U> hcat(const Tensor<U> &left, const Tensor<U> &right);
    template<typename U>
    friend Tensor<U> vcat(const Tensor<U> &top, const Tensor<U> &bottom);

    public:
        // Constructors
        Tensor(TensorLength_t rows, TensorLength_t columns) : tensor_size({rows, columns}){
            initialize();
        }
        Tensor(TensorSize_t tensor_size) : tensor_size(tensor_size) {
            initialize();
        }
        Tensor(const Tensor &tensor) : tensor_size(tensor.tensor_size) {
            initialize(false);
            for (TensorLength_t i = 0; i < tensor_size.rows; i++) {
                for (TensorLength_t j = 0; j < tensor_size.columns; j++) {
                    set(i, j, tensor.get(i, j));
                }
            }
        }

        // Destructor
        virtual ~Tensor() {
            destroy();
        }

        // MultiTensor Operations
        Tensor<T> operator+(Tensor<T> &tensor) {
            assert(tensor_size.rows == tensor.tensor_size.rows && tensor_size.columns == tensor.tensor_size.columns);
            Tensor<T> result(*this);
            result += tensor;
            return result;
        }
        Tensor<T> operator-(Tensor<T> &tensor) {
            assert(tensor_size.rows == tensor.tensor_size.rows && tensor_size.columns == tensor.tensor_size.columns);
            Tensor<T> result(*this);
            result -= tensor;
            return result;
        }
        Tensor<T> operator*(Tensor<T> &tensor) {
            assert(tensor_size.columns == tensor.tensor_size.rows);
            Tensor<T> result(tensor_size);
            
            for (TensorLength_t r = 0; r < tensor_size.rows; r++) {
                for (TensorLength_t c = 0; c < tensor.tensor_size.columns; c++) {
                    T sum = 0;
                    for (TensorLength_t i = 0; i < tensor_size.columns; i++) {
                        sum += get(r, i) * tensor.get(i, c);
                    }
                    result.set(r, c, sum);
                }
            }

            return result;
        }
        Tensor<T> operator~() {
            return transpose();
        }

        // MultiTensor Assignment Operations
        void operator+=(Tensor<T> &tensor) {
            assert(tensor_size.rows == tensor.tensor_size.rows && tensor_size.columns == tensor.tensor_size.columns);
            for (TensorLength_t i = 0; i < tensor_size.rows; i++) {
                for (TensorLength_t j = 0; j < tensor_size.columns; j++) {
                    set(i, j, get(i, j) + tensor.get(i, j));
                }
            }
        }
        void operator-=(Tensor<T> &tensor) {
            assert(tensor_size.rows == tensor.tensor_size.rows && tensor_size.columns == tensor.tensor_size.columns);
            for (TensorLength_t i = 0; i < tensor_size.rows; i++) {
                for (TensorLength_t j = 0; j < tensor_size.columns; j++) {
                    set(i, j, get(i, j) - tensor.get(i, j));
                }
            }
        }
        void operator*=(Tensor<T> &tensor) {
            Tensor<T> temp(*this);
            temp = temp * tensor;
            *this = temp;
        }
        void operator=(const Tensor<T> &tensor) {
            destroy();
            tensor_size = tensor.tensor_size;
            initialize(false);
            for (TensorLength_t i = 0; i < tensor_size.rows; i++) {
                for (TensorLength_t j = 0; j < tensor_size.columns; j++) {
                    set(i, j, tensor.get(i, j));
                }
            }
        }
        void operator<<(Tensor<T> &tensor) {
            *this = hcat(*this, tensor);
        }

        // Element Operations
        template<typename U>
        Tensor<T> operator+(const U &value) {
            Tensor<T> result(*this);
            result += value;
            return result;
        }
        template<typename U>
        Tensor<T> operator-(const U &value) {
            Tensor<T> result(*this);
            result -= value;
            return result;
        }
        template<typename U>
        Tensor<T> operator*(const U &value) {
            Tensor<T> result(*this);
            result *= value;
            return result;
        }
        template<typename U>
        Tensor<T> operator/(const U &value) {
            Tensor<T> result(*this);
            result /= value;
            return result;
        }
        template<typename U>
        Tensor<T> operator^(const U &value) {
            Tensor<T> result(*this);
            result ^= value;
            return result;
        }

        // Element Assignment Operations
        template<typename U>
        void operator+=(const U &value) {
            for (TensorLength_t i = 0; i < tensor_size.rows * tensor_size.columns; i++) {
                data[i] += value;
            }
        }
        template<typename U>
        void operator-=(const U &value) {
            for (TensorLength_t i = 0; i < tensor_size.rows * tensor_size.columns; i++) {
                data[i] -= value;
            }
        }
        template<typename U>
        void operator*=(const U &value) {
            for (TensorLength_t i = 0; i < tensor_size.rows * tensor_size.columns; i++) {
                data[i] *= value;
            }
        }
        template<typename U>
        void operator/=(const U &value) {
            for (TensorLength_t i = 0; i < tensor_size.rows * tensor_size.columns; i++) {
                data[i] /= value;
            }
        }
        template<typename U>
        void operator^=(const U &value) {
            for (TensorLength_t i = 0; i < tensor_size.rows * tensor_size.columns; i++) {
                data[i] = pow(data[i], value);
            }
        }

        // Access Operator Overloads
        T operator()(TensorLength_t row, TensorLength_t column) {
            return get(row, column);
        }

        bool isZero() {
            for (TensorLength_t i = 0; i < tensor_size.rows * tensor_size.columns; i++) {
                if (data[i] != 0) {
                    return false;
                }
            }
            return true;
        }

        bool isOne() {
            for (TensorLength_t i = 0; i < tensor_size.rows * tensor_size.columns; i++) {
                if (data[i] != 1) {
                    return false;
                }
            }
            return true;
        }

        virtual TensorLength_t length() {
            return tensor_size.rows > tensor_size.columns ? tensor_size.rows : tensor_size.columns;
        }
        TensorSize_t size() {
            return tensor_size;
        }
        TensorLength_t rows() {
            return tensor_size.rows;
        }
        TensorLength_t columns() {
            return tensor_size.columns;
        }

        void set(TensorLength_t row, TensorLength_t column, T value) {
            data[row * tensor_size.columns + column] = value;
        }

        T get(TensorLength_t row, TensorLength_t column) {
            return data[row * tensor_size.columns + column];
        }

    protected:

        virtual Tensor<T> transpose() {
            Tensor<T> result(tensor_size.columns, tensor_size.rows);
            for (TensorLength_t i = 0; i < tensor_size.rows; i++) {
                for (TensorLength_t j = 0; j < tensor_size.columns; j++) {
                    result.set(j, i, get(i, j));
                }
            }
            return result;
        }

    private:
        void initialize(bool zeroize = true) {
            data = new T[tensor_size.rows * tensor_size.columns];
            if (zeroize) {
                for (TensorLength_t i = 0; i < tensor_size.rows * tensor_size.columns; i++) {
                    data[i] = 0;
                }
            }
        }

        void destroy() {
            delete[] data;
        }

        TensorSize_t tensor_size;

        T *data;

};

// Tensor Friend Function Definitions
template<typename U>
Tensor<U> hcat(const Tensor<U> &left, const Tensor<U> &right) {
    assert(left.tensor_size.rows == right.tensor_size.rows);
    Tensor<U> result(left.tensor_size.rows, left.tensor_size.columns + right.tensor_size.columns);
    for (TensorLength_t i = 0; i < left.tensor_size.rows * result.tensor_size.columns; i++) {
        if (i % result.tensor_size.columns < left.tensor_size.columns) {
            result.data[i] = left.data[i];
        } else {
            result.data[i] = right.data[i - left.tensor_size.columns];
        }
    }
    return result;
}

template<typename U>
Tensor<U> vcat(const Tensor<U> &top, const Tensor<U> &bottom) {
    assert(top.tensor_size.columns == bottom.tensor_size.columns);
    Tensor<U> result({top.tensor_size.rows + bottom.tensor_size.rows, top.tensor_size.columns});
    TensorLength_t i = 0;
    const TensorLength_t topSize = top.tensor_size.rows * top.tensor_size.columns;
    for (; i < topSize; i++) {
        result.data[i] = top.data[i];
    }
    const TensorLength_t bottomSize = bottom.tensor_size.rows * bottom.tensor_size.columns;
    for (; i < topSize + bottomSize; i++) {
        result.data[i + topSize] = bottom.data[i];
    }
    return result;
}

} // end namespace DataStructures

#endif // __TENSOR_TPP__