#pragma once

#include <string>

#include "include/axaccess/mac/axapi_node.h"
#include "include/axaccess/node.h"

namespace axa {

class AXAPINodeImpl : public NodeImpl {
 public:
  AXAPINodeImpl(mac_inspect::AXAPINode axapi_node);
  virtual ~AXAPINodeImpl();

  std::string Name() override;
  std::string RoleName() override;
  int32_t ChildCount() override;
  NodePtr ChildAt(const int32_t index) override;

 private:
  mac_inspect::AXAPINode axapi_node_;
};

}  // namespace axa
