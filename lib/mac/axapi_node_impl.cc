#include "lib/mac/axapi_node_impl.h"

#include <string>

#include "acacia/mac/axapi_node.h"

namespace acacia {

AXAPINodeImpl::AXAPINodeImpl(acacia::AXAPINode axapi_node)
    : axapi_node_(axapi_node) {}

std::string AXAPINodeImpl::Name() {
  if (!axapi_node_.HasAttribute("AXTitle"))
    return "";
  return axapi_node_.CopyStringAttributeValue("AXTitle");
}

std::string AXAPINodeImpl::RoleName() {
  if (!axapi_node_.HasAttribute("AXRole"))
    return "";
  return axapi_node_.CopyStringAttributeValue("AXRole");
}

int32_t AXAPINodeImpl::ChildCount() {
  return axapi_node_.GetListAttributeValueCount("AXChildren");
}

NodePtr AXAPINodeImpl::ChildAt(int32_t index) {
  std::vector<acacia::AXAPINode> children =
      axapi_node_.CopyNodeListAttributeValue("AXChildren");
  if (index < 0 || index >= children.size()) {
    throw std::invalid_argument("Index out of bounds");
  }
  std::unique_ptr<NodeImpl> child =
      std::make_unique<AXAPINodeImpl>(children[index]);
  return Node::Create(std::move(child));
}

}  // namespace acacia
