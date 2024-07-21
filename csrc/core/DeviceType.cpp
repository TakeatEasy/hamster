#include <iostream>

#include "DeviceType.h"


namespace hamster {
namespace core {

std::string DeviceTypeName(DeviceType d, bool lower_case) {
    switch (d) {
        case DeviceType::CPU:
            return lower_case ? "cpu" : "CPU";
        case DeviceType::CUDA:
            return lower_case ? "cuda" : "CUDA";
        default:
            std::cout << "Using Error typename" << std::endl;
            return "";
    }
}

bool isValidDeviceType(DeviceType d) {
  switch (d) {
    case DeviceType::CPU:
    case DeviceType::CUDA:
      return true;
    default:
      return false;
  }
}

std::ostream& operator<<(std::ostream& stream, DeviceType type) {
  stream << DeviceTypeName(type, /* lower case */ true);
  return stream;
}

} // namespace core
} // namespace hamster