#include "csrc/core/TensorOptions.h"

#include "csrc/core/Device.h"
#include "csrc/core/Layout.h"
#include "csrc/core/ScalarType.h"
#include "csrc/utils/Optional.h"

#include <iostream>

namespace at {

std::ostream& operator<<(
    std::ostream& stream,
    const TensorOptions& options) {
  return stream << "TensorOptions(dtype=" << options.dtype()
                << ", device=" << options.device()
                << ", layout=" << options.layout()
                << ", requires_grad=" << std::boolalpha
                << options.requires_grad() << ")";
}

} // namespace at
