#include "Device.h"


namespace hamster{
namespace core {

DeviceType parse_type(const std::string& device_string) {
    static const std::array<std::pair<std::string, DeviceType>, 2> types = {{
        {"cpu", DeviceType::CPU},
        {"cuda", DeviceType::CUDA},
    }};

    auto device = std::find_if(
        types.begin(),
        types.end(),
        [device_string](const std::pair<std::string, DeviceType>& p) {
            return p.first == device_string;
        }
    );
    if (device != types.end()) {
        return device->second;
    }
}

Device::Device(const std::string& device_string) : Device(DeviceType::CPU) {
    int index = device_string.find(":");
    if (index == std::string::npos) {
        type_ = parse_type(device_string);
        return;
    } else {
        std::string s;
        s = device_string.substr(0, index);
        type_ = parse_type(s);
    }
    std::string device_index = device_string.substr(index + 1);
    try {
        index_ = std::stoi(device_index);
    } catch (const std::exception&) {
        std::cout <<"Could not parse device index in device string" << std::endl;
    }
}

std::ostream& operator<<(std::ostream& stream, const Device& device) {
    stream << device.type();
    if (device.has_index()) {
        stream << ":" << device.index();
    }
    return stream;
}

} // namespace core
} // namespace hamster