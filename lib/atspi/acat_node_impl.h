#pragma once

#include <acacia/atspi/atspi_node.h>
#include <acacia/node.h>
#include <string>

namespace acacia {

class AtspiNodeImpl : public NodeImpl {
 public:
  static std::unique_ptr<NodeImpl> Create(AtspiNodePtr& atspiNode);
  AtspiNodeImpl(AtspiNodePtr& atspiNode);
  ~AtspiNodeImpl();

  std::string Name() override;
  std::string RoleName() override;
  int32_t ChildCount() override;
  NodePtr ChildAt(const int32_t index) override;

 private:
  AtspiNodePtr atspiNode;
};

}  // namespace acacia
