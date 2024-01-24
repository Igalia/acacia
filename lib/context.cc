#include <assert.h>
#include <axaccess/context.h>
#if defined(AXA_API_ATSPI)
  #include "atspi/axa_context_impl.h"
#endif

namespace axa {

Context::Context() {
#if defined(AXA_API_ATSPI)
  impl = std::move(AtspiContextImpl::Create());
#endif
}

Context::~Context() {
  assert(impl);
  impl.reset();
}

ContextPtr Context::Create() {
  ContextPtr result = std::make_shared<Context>();
  return result;
}

enum APIType Context::GetAPIType() {
  return impl->GetAPIType();
}

NodePtr Context::GetAccessibleRootByPID(const int pid) {
  return impl->GetAccessibleRootByPID(pid);
}

} // namespace axa
