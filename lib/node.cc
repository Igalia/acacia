#include <assert.h>
#include <axaccess/node.h>
#include <string>

namespace AXA {

struct Node::State {
  State() = default;
  ~State() = default;
};

Node::Node(State& aState, NodeImplPtr aImpl):
  m(aState),
  impl(std::move(aImpl)) {
}

Node::~Node() {
  impl.reset();
}

AXA::NodePtr Node::Create(NodeImplPtr aImpl) {
  assert(aImpl != nullptr);
  Node::State state = {};
  NodePtr result = std::make_shared<Node>(state, std::move(aImpl));
  return result;
}

std::string Node::GetName() {
  return impl->GetName();
}

std::string Node::GetRole() {
  return impl->GetRole();
}

int32_t Node::GetChildCount() {
  return impl->GetChildCount();
}

NodePtr Node::GetChildAt(const int32_t index) {
  return impl->GetChildAt(index);
}

} // namespace AXA
