#pragma once

#include <memory>

namespace axa {

class Node;
typedef std::shared_ptr<Node> NodePtr;

class NodeImpl {
 public:
  NodeImpl() {
  }
  virtual std::string Name() = 0;
  virtual std::string RoleName() = 0;
  virtual int32_t ChildCount() = 0;
  virtual NodePtr ChildAt(const int32_t index) = 0;
};


class Node {
 public:
  static NodePtr Create(std::unique_ptr<NodeImpl> impl);
  Node(std::unique_ptr<NodeImpl> aImpl);
  ~Node();

  std::string Name();
  std::string RoleName();
  int32_t ChildCount();
  NodePtr ChildAt(const int32_t index);

 private:
  std::unique_ptr<NodeImpl> impl;
};

} // namespace axa
