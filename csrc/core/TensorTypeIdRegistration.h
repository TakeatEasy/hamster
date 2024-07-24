#pragma once

/**
 * To register your own tensor types, do in a header file:
 *   C10_DECLARE_TENSOR_TYPE(MY_TENSOR)
 * and in one (!) cpp file:
 *   C10_DEFINE_TENSOR_TYPE(MY_TENSOR)
 * Both must be in the same namespace.
 */

#include "../utils/Macros.h"
#include "TensorTypeId.h"

#include <atomic>
#include <mutex>
#include <unordered_set>

namespace hamster {
class TensorTypeIdCreator final {
 public:
  TensorTypeIdCreator();

  hamster::TensorTypeId create();

  static constexpr hamster::TensorTypeId undefined() noexcept {
    return hamster::TensorTypeId(0);
  }

 private:
  std::atomic<details::_tensorTypeId_underlyingType> last_id_;

  C10_DISABLE_COPY_AND_ASSIGN(TensorTypeIdCreator);
};


class TensorTypeIdRegistry final {
 public:
  TensorTypeIdRegistry();

  void registerId(hamster::TensorTypeId id);
  void deregisterId(hamster::TensorTypeId id);

 private:
  std::unordered_set<hamster::TensorTypeId> registeredTypeIds_;
  std::mutex mutex_;

  C10_DISABLE_COPY_AND_ASSIGN(TensorTypeIdRegistry);
};


class TensorTypeIds final {
 public:
  static TensorTypeIds& singleton();

  hamster::TensorTypeId createAndRegister();
  void deregister(hamster::TensorTypeId id);

  static constexpr hamster::TensorTypeId undefined() noexcept;

 private:
  TensorTypeIds();

  TensorTypeIdCreator creator_;
  TensorTypeIdRegistry registry_;

  C10_DISABLE_COPY_AND_ASSIGN(TensorTypeIds);
};

inline constexpr hamster::TensorTypeId TensorTypeIds::undefined() noexcept {
  return TensorTypeIdCreator::undefined();
}

class TensorTypeIdRegistrar final {
 public:
  TensorTypeIdRegistrar();
  ~TensorTypeIdRegistrar();

  hamster::TensorTypeId id() const noexcept;

 private:
  hamster::TensorTypeId id_;

  C10_DISABLE_COPY_AND_ASSIGN(TensorTypeIdRegistrar);
};

inline hamster::TensorTypeId TensorTypeIdRegistrar::id() const noexcept {
  return id_;
}


#define C10_DECLARE_TENSOR_TYPE(TensorName) \
  hamster::TensorTypeId TensorName()

#define C10_DEFINE_TENSOR_TYPE(TensorName)          \
  hamster::TensorTypeId TensorName() {                  \
    static TensorTypeIdRegistrar registration_raii; \
    return registration_raii.id();                  \
  }

C10_DECLARE_TENSOR_TYPE(UndefinedTensorId);
C10_DECLARE_TENSOR_TYPE(CPUTensorId); // PyTorch/Caffe2 supported
C10_DECLARE_TENSOR_TYPE(CUDATensorId); // PyTorch/Caffe2 supported
C10_DECLARE_TENSOR_TYPE(SparseCPUTensorId); // PyTorch only
C10_DECLARE_TENSOR_TYPE(SparseCUDATensorId); // PyTorch only
C10_DECLARE_TENSOR_TYPE(MKLDNNTensorId); // Caffe2 only
C10_DECLARE_TENSOR_TYPE(OpenGLTensorId); // Caffe2 only
C10_DECLARE_TENSOR_TYPE(OpenCLTensorId); // Caffe2 only
C10_DECLARE_TENSOR_TYPE(IDEEPTensorId); // Caffe2 only
C10_DECLARE_TENSOR_TYPE(HIPTensorId); // PyTorch/Caffe2 supported
C10_DECLARE_TENSOR_TYPE(SparseHIPTensorId); // PyTorch only

}