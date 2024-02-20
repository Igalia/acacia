#pragma once

#include <string>

#include "axaccess/context.h"

namespace axa {

class AtspiContextImpl : public ContextImpl {
 public:
  static std::unique_ptr<ContextImpl> Create();
  AtspiContextImpl() = default;
  ~AtspiContextImpl() = default;

  enum APIType GetAPIType() override;
  NodePtr GetAccessibleRootByPID(const int pid) override;
};

}  // namespace axa
