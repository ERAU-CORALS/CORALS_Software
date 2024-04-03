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

    public:
        // Constructors
        Tensor(int rows, int columns) : size({rows, columns}){
            initialize();
        }
        Tensor(TensorSize_t size) : size(size) {
            initialize();
        }
        Tensor(const Tensor &tensor) : size(tensor.size) {
            initialize(false);
            for (int i = 0; i < size.rows; i++) {
                for (int j = 0; j < size.columns; j++) {
                    set(i, j, tensor.get(i, j));
                }
            }
        }

        // Destructor
        ~Tensor() {
            destroy();
        }

        // MultiTensor Operations
        Tensor operator+(const Tensor &tensor) {
            assert(size.rows == tensor.size.rows && size.columns == tensor.size.columns);
            Tensor result(size);
            for (int i = 0; i < size.rows; i++) {
                for (int j = 0; j < size.columns; j++) {
                    result.set(i, j, get(i, j) + tensor.get(i, j));
                }
            }
            return result;
        }
        Tensor operator-(const Tensor &tensor) {
            assert(size.rows == tensor.size.rows && size.columns == tensor.size.columns);
            Tensor result(size);
            for (int i = 0; i < size.rows; i++) {
                for (int j = 0; j < size.columns; j++) {
                    result.set(i, j, get(i, j) - tensor.get(i, j));
                }
            }
            return result;
        }
        Tensor operator*(const Tensor &tensor) {
            assert(size.columns == tensor.size.rows);
            Tensor result({size.rows, tensor.size.columns});
            
            for (int r = 0; r < size.rows; r++) {
                for (int c = 0; c < tensor.size.columns; c++) {
                    T sum = 0;
                    for (int i = 0; i < size.columns; i++) {
                        sum += get(r, i) * tensor.get(i, c);
                    }
                    result.set(r, c, sum);
                }
            }

            return result;
        }

        // MultiTensor Assignment Operations
        void operator+=(const Tensor &tensor) {
            assert(size.rows == tensor.size.rows && size.columns == tensor.size.columns);
            for (int i = 0; i < size.rows; i++) {
                for (int j = 0; j < size.columns; j++) {
                    set(i, j, get(i, j) + tensor.get(i, j));
                }
            }
        }
        void operator-=(const Tensor &tensor) {
            assert(size.rows == tensor.size.rows && size.columns == tensor.size.columns);
            for (int i = 0; i < size.rows; i++) {
                for (int j = 0; j < size.columns; j++) {
                    set(i, j, get(i, j) - tensor.get(i, j));
                }
            }
        }
        void operator*=(const Tensor &tensor) {
            Tensor temp(*this);
            temp = temp * tensor;
            *this = temp;
        }
        void operator=(const Tensor &tensor) {
            destroy();
            size = tensor.size;
            initialize(false);
            for (int i = 0; i < size.rows; i++) {
                for (int j = 0; j < size.columns; j++) {
                    set(i, j, tensor.get(i, j));
                }
            }
        }

        // Element Operations
        template<typename U>
        Tensor operator+(const U &value) {
            Tensor result(this);
            result += value;
            return result;
        }
        template<typename U>
        Tensor operator-(const U &value) {
            Tensor result(this);
            result -= value;
            return result;
        }
        template<typename U>
        Tensor operator*(const U &value) {
            Tensor result(this);
            result *= value;
            return result;
        }
        template<typename U>
        Tensor operator/(const U &value) {
            Tensor result(this);
            result /= value;
            return result;
        }
        template<typename U>
        Tensor operator%(const U &value) {
            Tensor result(this);
            result %= value;
            return result;
        }
        template<typename U>
        Tensor operator^(const U &value) {
            Tensor result(this);
            result ^= value;
            return result;
        }

        // Element Assignment Operations
        template<typename U>
        void operator+=(const U &value) {
            for (int i = 0; i < size.rows * size.columns; i++) {
                data[i] += value;
            }
        }
        template<typename U>
        void operator-=(const U &value) {
            for (int i = 0; i < size.rows * size.columns; i++) {
                data[i] -= value;
            }
        }
        template<typename U>
        void operator*=(const U &value) {
            for (int i = 0; i < size.rows * size.columns; i++) {
                data[i] *= value;
            }
        }
        template<typename U>
        void operator/=(const U &value) {
            for (int i = 0; i < size.rows * size.columns; i++) {
                data[i] /= value;
            }
        }
        template<typename U>
        void operator%=(const U &value) {
            for (int i = 0; i < size.rows * size.columns; i++) {
                data[i] %= value;
            }
        }
        template<typename U>
        void operator^=(const U &value) {
            for (int i = 0; i < size.rows * size.columns; i++) {
                data[i] ^= value;
            }
        }

        // Access Operator Overloads
        T operator()(int row, int column) {
            return get(row, column);
        }

        // Tensor Functions
        Tensor vcat(const Tensor &top, const Tensor &bottom) {
            assert(top.size.columns == bottom.size.columns);
            Tensor result({top.size.rows + bottom.size.rows, top.size.columns});
            int i = 0
            const int topSize = top.size.rows * top.size.columns;
            for (; i < topSize; i++) {
                result.data[i] = top.data[i];
            }
            const int bottomSize = bottom.size.rows * bottom.size.columns;
            for (; i < topSize + bottomSize; i++) {
                result.data[i + topSize] = bottom.data[i];
            }
            return result;
        }

        Tensor hcat(const Tensor &left, const Tensor &right) {
            assert(left.size.rows == right.size.rows);
            Tensor result({left.size.rows, left.size.columns + right.size.columns});
            for (int i = 0; i < left.size.rows * size.columns; i++) {
                if (i % size.columns < left.size.columns) {
                    result.data[i] = left.data[i];
                } else {
                    result.data[i] = right.data[i - left.size.columns];
                }
            }
            return result;
        }

        bool isZero() {
            for (int i = 0; i < size.rows * size.columns; i++) {
                if (data[i] != 0) {
                    return false;
                }
            }
            return true;
        }

        bool isOne() {
            for (int i = 0; i < size.rows * size.columns; i++) {
                if (data[i] != 1) {
                    return false;
                }
            }
            return true;
        }

        // Tensor ABC Functions
        virtual void transpose() = 0;
        virtual TensorLength_t length() = 0;
        virtual TensorSize_t size() = 0;

    protected:
        void set(int row, int column, T value) {
            data[row * size.columns + column] = value;
        }

        T get(int row, int column) {
            return data[row * size.columns + column];
        }

    private:
        void initialize(bool zeroize = true) {
            data = new T[size.rows * size.columns];
            if (zeroize) {
                for (int i = 0; i < size.rows * size.columns; i++) {
                    data[i] = 0;
                }
            }
        }

        void destroy() {
            delete[] data;
        }

        TensorSize_t size;

        T *data;

};

} // end namespace DataStructures

#endif // __TENSOR_TPP__