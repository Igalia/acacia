#include <acacia/context.h>
#include <assert.h>
#if defined(AXA_API_ATSPI)
#include "atspi/axa_context_impl.h"
#elif defined(AXA_API_AXAPI)
#include "lib/mac/axapi_context_impl.h"
#endif

namespace axa {

Context::Context() {
#if defined(AXA_API_ATSPI)
  impl = std::move(AtspiContextImpl::Create());
#elif defined(AXA_API_AXAPI)
  impl = std::move(AXAPIContextImpl::Create());
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

}  // namespace axa
