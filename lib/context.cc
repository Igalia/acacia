#include <assert.h>
#include <axaccess/context.h>
#if defined(AXA_API_ATSPI)
  #include "atspi/axa_context_impl.h"
#endif

namespace AXA {

struct Context::State {

  State() = default;
  ~State() = default;
};

Context::Context(State& aState) : m(aState) {
#if defined(AXA_API_ATSPI)
  impl = std::move(AtspiContextImpl::Create());
#endif
}

Context::~Context() {
  assert(impl);
  impl.reset();
}

ContextPtr Context::Create() {
  Context::State state = {};
  ContextPtr result = std::make_shared<AXA::Context>(state);
  return result;
}

enum AccessibleAPIType Context::GetAccessibleAPIType() {
  return impl->GetAccessibleAPIType();
}

NodePtr Context::GetAccessibleRootByPID(const int pid) {
  return impl->GetAccessibleRootByPID(pid);
}

} // namespace AXA
