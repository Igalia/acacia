#include <assert.h>
#include "axa_context_impl.h"
#include "axa_node_impl.h"
#include <axaccess/atspi/linux_utils.h>

namespace AXA {

struct AtspiContextImpl::State {
  State() = default;
  ~State() = default;
};

AtspiContextImpl::AtspiContextImpl(State& aState):
  m(aState) {
}

AtspiContextImpl::~AtspiContextImpl() {
}

AXA::ContextImplPtr AtspiContextImpl::Create() {
  AtspiContextImpl::State state = {};
  ContextImplPtr result = std::make_unique<AtspiContextImpl>(state);
  return result;
}

enum AccessibleAPIType AtspiContextImpl::GetAccessibleAPIType() {
  return AccessibleAPIType::ATSPI;
}

NodePtr AtspiContextImpl::GetAccessibleRootByPID(const int pid) {
  auto atspiRoot = find_root_accessible_from_pid(pid);
  if (atspiRoot == nullptr)
    return nullptr;

  // This shouldn't fail (unless out of memory)
  auto rootNodeImpl = AtspiNodeImpl::Create(atspiRoot);
  if (rootNodeImpl == nullptr)
    return nullptr;

  return Node::Create(std::move(rootNodeImpl));
}

} // namespace AXA
