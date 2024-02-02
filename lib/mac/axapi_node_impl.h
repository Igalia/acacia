#pragma once

#include <string>

#include "include/axaccess/mac/axapi_node.h"
#include "include/axaccess/node.h"

namespace axa {

class AXAPINodeImpl : public NodeImpl {
 public:
  static std::unique_ptr<NodeImpl> Create(AXAPINodePtr& atspiNode);
  AXAPINodeImpl(AXAPINodePtr& atspiNode);
  ~AXAPINodeImpl();

  std::string Name() override;
  std::string RoleName() override;
  int32_t ChildCount() override;
  NodePtr ChildAt(const int32_t index) override;

 private:
  AXAPINodePtr atspiNode;
};

}  // namespace axa
