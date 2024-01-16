#pragma once

#include <memory>

namespace AXA {

class Node;
typedef std::shared_ptr<Node> NodePtr;

class NodeImpl;
typedef std::unique_ptr<NodeImpl> NodeImplPtr;

class NodeImpl {
 public:
  NodeImpl() {
  }
  virtual std::string GetName() = 0;
  virtual std::string GetRoleName() = 0;
  virtual int32_t GetChildCount() = 0;
  virtual NodePtr GetChildAt(const int32_t index) = 0;
};


class Node {
 public:
  struct State;

  static AXA::NodePtr Create(NodeImplPtr impl);
  Node(State& aState, NodeImplPtr aImpl);
  ~Node();

  std::string GetName();
  std::string GetRoleName();
  int32_t GetChildCount();
  NodePtr GetChildAt(const int32_t index);

 private:
  State& m;
  NodeImplPtr impl;
};

}
