#include "../utils/C++17.h"
#include "../utils/Exception.h"
#include "TensorTypeIdRegistration.h"


namespace hamster {
TensorTypeIds::TensorTypeIds() : creator_(), registry_() {}

TensorTypeIds& TensorTypeIds::singleton() {
  static TensorTypeIds singleton;
  return singleton;
}

TensorTypeIdCreator::TensorTypeIdCreator() : last_id_(0) {}

hamster::TensorTypeId TensorTypeIdCreator::create() {
  auto id = TensorTypeId(++last_id_);

  if (last_id_ == 0) { // overflow happened!
    // If this happens in prod, we have to change
    // details::_tensorTypeId_underlyingType to uint16_t.
    AT_ERROR(
        "Tried to define more than ",
        std::numeric_limits<details::_tensorTypeId_underlyingType>::max() - 1,
        " tensor types, which is unsupported");
  }

  return id;
}

TensorTypeIdRegistry::TensorTypeIdRegistry() : registeredTypeIds_(), mutex_() {}

void TensorTypeIdRegistry::registerId(hamster::TensorTypeId id) {
  std::lock_guard<std::mutex> lock(mutex_);
  registeredTypeIds_.emplace(id);
}

void TensorTypeIdRegistry::deregisterId(hamster::TensorTypeId id) {
  std::lock_guard<std::mutex> lock(mutex_);
  registeredTypeIds_.erase(id);
}

hamster::TensorTypeId TensorTypeIds::createAndRegister() {
  hamster::TensorTypeId id = creator_.create();
  registry_.registerId(id);
  return id;
}

void TensorTypeIds::deregister(hamster::TensorTypeId id) {
  registry_.deregisterId(id);
}

TensorTypeIdRegistrar::TensorTypeIdRegistrar()
    : id_(TensorTypeIds::singleton().createAndRegister()) {}

TensorTypeIdRegistrar::~TensorTypeIdRegistrar() {
  TensorTypeIds::singleton().deregister(id_);
}

C10_DEFINE_TENSOR_TYPE(UndefinedTensorId);
C10_DEFINE_TENSOR_TYPE(CPUTensorId);
C10_DEFINE_TENSOR_TYPE(CUDATensorId);

} // namespace hamster