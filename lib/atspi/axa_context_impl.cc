#include "axa_context_impl.h"
#include <assert.h>
#include <axaccess/atspi/linux_utils.h>
#include "axa_node_impl.h"

namespace axa {

std::unique_ptr<ContextImpl> AtspiContextImpl::Create() {
  return std::make_unique<AtspiContextImpl>();
}

enum APIType AtspiContextImpl::GetAPIType() {
  return APIType::ATSPI;
}

NodePtr AtspiContextImpl::GetAccessibleRootByPID(const int pid) {
  auto atspiRoot = find_root_accessible_from_pid(pid);
  if (atspiRoot == nullptr)
    return nullptr;

  auto rootNodeImpl = AtspiNodeImpl::Create(atspiRoot);

  return Node::Create(std::move(rootNodeImpl));
}

}  // namespace axa
