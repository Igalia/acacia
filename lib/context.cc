#include <acacia/context.h>
#include <assert.h>
#if defined(ACACIA_CAT_ATSPI)
#include "atspi/acat_context_impl.h"
#elif defined(ACACIA_CAT_AXAPI)
#include "lib/mac/axapi_context_impl.h"
#endif

namespace acacia {

Context::Context() {
#if defined(ACACIA_CAT_ATSPI)
  impl = std::move(AtspiContextImpl::Create());
#elif defined(ACACIA_CAT_AXAPI)
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

}  // namespace acacia
