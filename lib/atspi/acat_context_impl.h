#pragma once

#include <string>

#include "acacia/context.h"

namespace acacia {

class AtspiContextImpl : public ContextImpl {
 public:
  static std::unique_ptr<ContextImpl> Create();
  AtspiContextImpl() = default;
  ~AtspiContextImpl() = default;

  enum APIType GetAPIType() override;
  NodePtr GetAccessibleRootByPID(const int pid) override;
};

}  // namespace acacia
