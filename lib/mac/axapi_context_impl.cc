#include "lib/mac/axapi_context_impl.h"

#include <memory>

#include "acacia/mac/axapi_node.h"
#include "acacia/node.h"
#include "lib/mac/axapi_node_impl.h"

namespace axa {

using mac_inspect::AXAPINode;

std::unique_ptr<ContextImpl> AXAPIContextImpl::Create() {
  return std::make_unique<AXAPIContextImpl>();
}

enum APIType AXAPIContextImpl::GetAPIType() {
  return APIType::AXAPI;
}

NodePtr AXAPIContextImpl::GetAccessibleRootByPID(const int pid) {
  AXAPINode root_axapi_node = AXAPINode::CreateForPID(pid);
  std::unique_ptr<NodeImpl> root_node_impl =
      std::unique_ptr<NodeImpl>(new AXAPINodeImpl(root_axapi_node));

  return Node::Create(std::move(root_node_impl));
}

}  // namespace axa
