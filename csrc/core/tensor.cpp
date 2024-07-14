#include "tensor.h"

namespace hamster {
namespace core {

template <typename T>
void setTensorProperties(const Tensor<T>& tensor, uint32_t rows, uint32_t cols, uint32_t channels) {
    if (channels == -1 && rows == -1) {
        tensor->dim = 1;
    } else if (channels == -1) {
        tensor->dim = 2;
    } else {
        tensor->dim = 3;
    }
}

template <typename T>
Tensor<T>::Tensor(T* raw_ptr, uint32_t size) {
    this->data_ = arma::Cube<T>(raw_ptr, 1, size, 1, false, true);
}

template <typename T>
Tensor<T>::Tensor(T* raw_ptr, uint32_t rows, uint32_t cols) {
    this->data_ = arma::Cube<T>(raw_ptr, rows, cols, true, false);
}

template <typename T>
Tensor<T>::Tensor(T* raw_ptr, uint32_t rows, uint32_t cols, uint32_t channels) {
    this->data_ = arma::Cube<T>(raw_ptr, rows, cols, channels, true, false);
}

template <typename T>
Tensor<T>::Tensor(uint32_t channels, uint32_t rows, uint32_t cols) {
    data_ = arma::Cube<T>(rows, cols, channels);
}


template <typename T>
Tensor<T>::Tensor(uint32_t size) {
  data_ = arma::Cube<T>(1, size, 1);
}

template <typename T>
Tensor<T>::Tensor(uint32_t rows, uint32_t cols) {
  data_ = arma::Cube<T>(rows, cols, 1);
}




} // namespace core
} // namespace hamster