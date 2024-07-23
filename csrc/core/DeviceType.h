#pragma once

#include <ostream>
#include <functional>

#include "../utils/Macros.h"

namespace hamster {

enum class DeviceType : int16_t {
  CPU = 0,
  CUDA = 1, // CUDA.
  COMPILE_TIME_MAX_DEVICE_TYPES = 2,
};

constexpr int COMPILE_TIME_MAX_DEVICE_TYPES =
    static_cast<int>(DeviceType::COMPILE_TIME_MAX_DEVICE_TYPES);
std::string DeviceTypeName(
    DeviceType d,
    bool lower_case = false);

bool isValidDeviceType(DeviceType d);

std::ostream& operator<<(std::ostream& stream, DeviceType type);

} // namespace hamster

namespace std {
    template<>
    struct hash<hamster::DeviceType> {
        std::size_t operator()(hamster::DeviceType k) const {
            return std::hash<int>()(static_cast<int>(k));
        }
    };
}