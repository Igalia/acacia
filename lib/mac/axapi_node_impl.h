#pragma once

#include <string>

#include "include/axaccess/mac/axapi_node.h"
#include "include/axaccess/node.h"

namespace axa {

using mac_inspect::AXAPINode;

class AXAPIContextImpl;

class AXAPINodeImpl : public NodeImpl {
 public:
  ~AXAPINodeImpl();

  std::string Name() override;
  std::string RoleName() override;
  int32_t ChildCount() override;
  NodePtr ChildAt(const int32_t index) override;

 private:
  AXAPINodeImpl(AXAPINode axapi_node);

  AXAPINode axapi_node_;

  friend class AXAPIContextImpl;
};

}  // namespace axa
