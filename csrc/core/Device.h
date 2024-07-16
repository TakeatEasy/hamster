#include "DeviceType.h"

#include <cstddef>
#include <functional>
#include <string>

namespace hamster{
namespace core {

class Device {

public:
    Device(DeviceType type, int32_t index = -1) : type_(type), index_(index) {}

    Device(const std::string& device_string);

    /// Returns true if the type and index of this `Device` matches that of
    /// `other`.
    bool operator==(const Device& other) const noexcept {
        return this->type_ == other.type_ && this->index_ == other.index_;
    }

    /// Returns true if the type or index of this `Device` differs from that of
    /// `other`.
    bool operator!=(const Device& other) const noexcept {
        return !(*this == other);
    }

    /// Sets the device index.
    void set_index(int32_t index) {
        index_ = index;
    }

    /// Returns the type of device this is.
    DeviceType type() const noexcept {
        return type_;
    }

    /// Returns the optional index.
    int32_t index() const noexcept {
        return index_;
    }

    /// Returns true if the device has a non-default index.
    bool has_index() const noexcept {
        return index_ != -1;
    }

    /// Return true if the device is of CUDA type.
    bool is_cuda() const noexcept {
        return type_ == DeviceType::CUDA;
    }

    /// Return true if the device is of CPU type.
    bool is_cpu() const noexcept {
        return type_ == DeviceType::CPU;
    }

    private:
    DeviceType type_;
    int32_t index_ = -1;
};

std::ostream& operator<<(std::ostream& stream, const Device& device);


} // namespace core
} // namespace hamster