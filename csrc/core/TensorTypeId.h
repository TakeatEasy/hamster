#pragma once

#include <iostream>
#include <string>

#include "../utils/Macros.h"
#include "IdWrapper.h"

namespace hamster {

namespace details {
using _tensorTypeId_underlyingType = uint8_t;
}

class TensorTypeId final
    : public hamster::
          IdWrapper<TensorTypeId, details::_tensorTypeId_underlyingType> {

public:
  // Don't use this!
  // Unfortunately, a default constructor needs to be defined because of
  // https://reviews.llvm.org/D41223
  constexpr TensorTypeId() noexcept : IdWrapper(0) {}

private:
  constexpr explicit TensorTypeId(
      details::_tensorTypeId_underlyingType id) noexcept
      : IdWrapper(id) {}

  friend class TensorTypeIdCreator;
  friend std::ostream& operator<<(std::ostream&, TensorTypeId);   
};

std::ostream& operator<<(std::ostream&, hamster::TensorTypeId);
} // namespace hamster

HAMSTER_DEFINE_HASH_FOR_IDWRAPPER(hamster::TensorTypeId)