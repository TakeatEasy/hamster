#pragma once

#include <functional>
#include <iostream>

namespace hamster {
namespace core {

enum class DeviceType {
  CPU,
  CUDA
};

std::string DeviceTypeName(DeviceType d, bool lower_case = false);

bool isValidDeviceType(DeviceType d);

std::ostream &operator<<(std::ostream &stream, DeviceType type);

} // namespace core
} // namespace hamster

namespace std {
template <> struct hash<hamster::core::DeviceType> {
  std::size_t operator()(hamster::core::DeviceType k) const {
    return std::hash<int>()(static_cast<int>(k));
  }
};

} // namespace std