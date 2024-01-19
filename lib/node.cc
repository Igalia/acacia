#include <assert.h>
#include <axaccess/node.h>
#include <string>

namespace axa {

Node::Node(std::unique_ptr<NodeImpl> aImpl):
  impl(std::move(aImpl)) {
}

Node::~Node() {
  impl.reset();
}

NodePtr Node::Create(std::unique_ptr<NodeImpl> aImpl) {
  assert(aImpl != nullptr);
  NodePtr result = std::make_shared<Node>(std::move(aImpl));
  return result;
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

} // namespace axa
