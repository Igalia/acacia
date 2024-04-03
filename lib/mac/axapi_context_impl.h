#pragma once

#include <string>

#include "acacia/context.h"

namespace acat {

class AXAPIContextImpl : public ContextImpl {
 public:
  static std::unique_ptr<ContextImpl> Create();
  AXAPIContextImpl() = default;
  ~AXAPIContextImpl() = default;

  enum APIType GetAPIType() override;
  NodePtr GetAccessibleRootByPID(const int pid) override;
};

}  // namespace acat
