#pragma once

#include <string>

#include "include/axaccess/context.h"

namespace axa {

class AXAPIContextImpl : public ContextImpl {
 public:
  static std::unique_ptr<ContextImpl> Create();
  AXAPIContextImpl() = default;
  ~AXAPIContextImpl() = default;

  enum APIType GetAPIType() override;
  NodePtr GetAccessibleRootByPID(const int pid) override;
};

}  // namespace axa
