#include "TensorTypeId.h"
#include "../utils/string_utils.h"

namespace c10 {

std::ostream& operator<<(std::ostream& str, c10::TensorTypeId rhs) {
  return str << c10::to_string(rhs.underlyingId());
}

} // namespace c10
