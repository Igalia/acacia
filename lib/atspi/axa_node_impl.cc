#include <assert.h>
#include "axa_node_impl.h"

namespace AXA {

AtspiNodeImpl::AtspiNodeImpl(AtspiNodePtr& aAtspiNode):
  atspiNode(std::move(aAtspiNode)) {
}

AtspiNodeImpl::~AtspiNodeImpl() {
  atspiNode.reset();
}

AXA::NodeImplPtr AtspiNodeImpl::Create(AtspiNodePtr& aAtspiNode) {
  assert(aAtspiNode);
  NodeImplPtr result = std::make_unique<AtspiNodeImpl>(aAtspiNode);
  return result;
}

std::string AtspiNodeImpl::GetName() {
  return atspiNode->accessible_get_name();
}

std::string AtspiNodeImpl::GetRole() {
  return atspiNode->accessible_get_role_name();
}

int32_t AtspiNodeImpl::GetChildCount() {
  return atspiNode->accessible_get_child_count();
}

NodePtr AtspiNodeImpl::GetChildAt(const int32_t index) {
  auto childNode = atspiNode->accessible_get_child_at_index(index);
  if (childNode == nullptr)
    return nullptr;

  auto nodeImpl = AtspiNodeImpl::Create(childNode);
  if (nodeImpl == nullptr)
    return nullptr;

  return Node::Create(std::move(nodeImpl));
}

} // namespace AXA
