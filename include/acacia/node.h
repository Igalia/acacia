#pragma once

#include <memory>
#include <string>

#include "acacia/export.h"

namespace acacia {

class Node;
typedef std::unique_ptr<Node> NodePtr;

class NodeImpl {
 public:
  NodeImpl() {}
  virtual ~NodeImpl(){};
  virtual std::string Name() = 0;
  virtual std::string RoleName() = 0;
  virtual int32_t ChildCount() = 0;
  virtual NodePtr ChildAt(const int32_t index) = 0;
};

class ACACIA_EXPORT Node {
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

}  // namespace acacia
