#include "TensorTypeId.h"
#include <sstream>


namespace hamster {
std::ostream& operator<<(std::ostream& str, hamster::TensorTypeId rhs) {
std::ostringstream os;
os << rhs.underlyingId();
  return str << os.str();
}
} // namespace hamster