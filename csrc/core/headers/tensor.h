#include <string>
#include <vector>

namespace hamster {
namespace core {

// For c++ part, it is an wrapper for Numcpp, for gpu ops, we will use cuda tool chain as support
template <typename T>
class Tensor {

public:
    explicit Tensor(T* ptr, std::vector<uint32_t> sizes);
    explicit Tensor(T* ptr, uint32_t len);
    explicit Tensor(T* ptr, uint32_t rows, uint32_t cols);
    explicit Tensor(T* ptr, uint32_t channels, uint32_t rows, uint32_t cols);
    explicit Tensor(T* ptr, uint32_t n, uint32_t channels, uint32_t rows, uint32_t cols);
    explicit Tensor() = default;

    uint32_t dim() const;
    uint32_t numel() const;
    T* data_ptr() const;

private:
    std::string device_;
    std::vector<uint32_t> sizes_;
    uint32_t dim_;
    uint32_t numel_;
};

} // namespace core
} // namespace hamster
