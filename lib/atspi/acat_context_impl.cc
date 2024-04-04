#include "acat_context_impl.h"

#include <acacia/atspi/linux_utils.h>
#include <assert.h>

#include "acat_node_impl.h"

namespace acacia {

std::unique_ptr<ContextImpl> AtspiContextImpl::Create() {
  return std::make_unique<AtspiContextImpl>();
}

enum APIType AtspiContextImpl::GetAPIType() {
  return APIType::ATSPI;
}

NodePtr AtspiContextImpl::GetAccessibleRootByPID(const int pid) {
  auto atspiRoot = findRootAtspiNodeForPID(pid);
  if (atspiRoot == nullptr)
    return nullptr;

  auto rootNodeImpl = AtspiNodeImpl::Create(atspiRoot);

  return Node::Create(std::move(rootNodeImpl));
}

}  // namespace acacia
