#include <string>
#include <vector>
#include <armadillo>

namespace hamster {
namespace core {

// For c++ part, it is an wrapper for Numcpp, for gpu ops, we will use cuda tool chain as support
template <typename T>
class Tensor {

public:
    explicit Tensor(T* raw_ptr, uint32_t rows);

    explicit Tensor(T* raw_ptr, uint32_t rows, uint32_t cols);

    explicit Tensor(T* raw_ptr, uint32_t channels, uint32_t rows, uint32_t cols);

    explicit Tensor(T* raw_ptr, const std::vector<uint32_t>& shapes);

    explicit Tensor() = default;

    explicit Tensor(uint32_t n, uint32_t channels, uint32_t rows, uint32_t cols);

    explicit Tensor(uint32_t channels, uint32_t rows, uint32_t cols);

    explicit Tensor(uint32_t rows, uint32_t cols);

    explicit Tensor(uint32_t rows);


    uint32_t dim() const;

    uint32_t numel() const;

    uint32_t rows() const;

    uint32_t cols() const;

    uint32_t channels() const;

    T* data_ptr() const;

    bool is_empty() const;

    std::vector<uint32_t> shapes() const;


private:
    std::string device_;
    std::vector<uint32_t> sizes_;
    uint32_t dim_;
    uint32_t numel_;
    arma::Cube<T> data_;
};

} // namespace core
} // namespace hamster
