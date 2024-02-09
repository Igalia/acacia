#pragma once

#include <string>

#include "include/axaccess/mac/axapi_node.h"
#include "include/axaccess/node.h"

namespace axa {

using mac_inspect::AXAPINode;

class AXAPINodeImpl : public NodeImpl {
 public:
  AXAPINodeImpl(AXAPINode axapi_node);
  ~AXAPINodeImpl();

  std::string Name() override;
  std::string RoleName() override;
  int32_t ChildCount() override;
  NodePtr ChildAt(const int32_t index) override;

 private:
  AXAPINode axapi_node_;
};

}  // namespace axa
