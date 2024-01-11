#pragma once

#include <axaccess/atspi/atspi_node.h>
#include <axaccess/node.h>
#include <string>

namespace AXA {

class AtspiNodeImpl: public NodeImpl {
public:
  static AXA::NodeImplPtr Create(AtspiNodePtr& atspiNode);
  AtspiNodeImpl(AtspiNodePtr& atspiNode);
  ~AtspiNodeImpl();

  std::string GetName() override;
  std::string GetRole() override;
  int32_t GetChildCount() override;
  NodePtr GetChildAt(const int32_t index) override;

 private:
  AtspiNodePtr atspiNode;
};

};
