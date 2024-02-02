#include "lib/mac/axapi_context_impl.h"

#include "lib/mac/axapi_node_impl.h"

namespace axa {

std::unique_ptr<ContextImpl> AXAPIContextImpl::Create() {
  return std::make_unique<AXAPIContextImpl>();
}

enum APIType AtspiContextImpl::GetAPIType() {
  return APIType::AXAPI;
}

NodePtr AtspiContextImpl::GetAccessibleRootByPID(const int pid) {
  std::unique_ptr<AXAPINodeImpl> root_node_impl =
      AXAPINodeImpl::Create(root_axapi_node);

  return Node::Create(std::move(root_node_impl));
}

}  // namespace axa
