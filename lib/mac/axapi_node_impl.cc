#include "lib/mac/axapi_node_impl.h"

#include <string>

namespace axa {

AXAPINodeImpl::AXAPINodeImpl(AXAPINode axapi_node) : axapi_node_(axapi_node) {}

std::string AXAPINodeImpl::RoleName() {
  return axapi_node_.CopyStringAttributeValue("AXRole");
}

std::string AXAPINodeImpl::Name() {
  return axapi_node_.CopyStringAttributeValue("AXTitle");
}

int32_t AXAPINodeImpl::ChildCount() {
  std::vector<AXAPINode> children =
      axapi_node_.CopyNodeListAttributeValue("AXChildren");
  return children.size();
}

NodePtr AXAPINodeImpl::ChildAt(int32_t index) {
  std::vector<AXAPINode> children =
      axapi_node_.CopyNodeListAttributeValue("AXChildren");
  if (index < 0 || index >= children.size()) {
    throw std::invalid_argument("Index out of bounds");
  }
  std::unique_ptr<NodeImpl> child =
      std::make_unique<AXAPINodeImpl>(children[index]);
  return Node::Create(std::move(child));
}

}  // namespace axa
