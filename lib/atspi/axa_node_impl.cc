#include "axa_node_impl.h"

#include <assert.h>

namespace axa {

AtspiNodeImpl::AtspiNodeImpl(AtspiNodePtr& aAtspiNode)
    : atspiNode(std::move(aAtspiNode)) {}

AtspiNodeImpl::~AtspiNodeImpl() {
  atspiNode.reset();
}

std::unique_ptr<NodeImpl> AtspiNodeImpl::Create(AtspiNodePtr& aAtspiNode) {
  assert(aAtspiNode);
  return std::make_unique<AtspiNodeImpl>(aAtspiNode);
}

std::string AtspiNodeImpl::Name() {
  return atspiNode->getName();
}

std::string AtspiNodeImpl::RoleName() {
  return atspiNode->getRoleName();
}

int32_t AtspiNodeImpl::ChildCount() {
  return atspiNode->getChildCount();
}

NodePtr AtspiNodeImpl::ChildAt(const int32_t index) {
  auto childNode = atspiNode->getChildAtIndex(index);
  if (childNode == nullptr)
    return nullptr;

  auto nodeImpl = AtspiNodeImpl::Create(childNode);

  return Node::Create(std::move(nodeImpl));
}

}  // namespace axa
