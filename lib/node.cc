#include <acacia/node.h>
#include <assert.h>
#include <string>

namespace acat {

Node::Node(std::unique_ptr<NodeImpl> aImpl) : impl(std::move(aImpl)) {}

Node::~Node() {
  impl.reset();
}

NodePtr Node::Create(std::unique_ptr<NodeImpl> aImpl) {
  assert(aImpl != nullptr);
  return std::make_unique<Node>(std::move(aImpl));
}

std::string Node::Name() {
  return impl->Name();
}

std::string Node::RoleName() {
  return impl->RoleName();
}

int32_t Node::ChildCount() {
  return impl->ChildCount();
}

NodePtr Node::ChildAt(const int32_t index) {
  return impl->ChildAt(index);
}

}  // namespace acat
