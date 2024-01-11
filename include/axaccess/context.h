#pragma once

#include <memory>
#include "./node.h"

namespace AXA {

enum AccessibleAPIType {
  UNKNOWN,
  ATSPI,        // Linux
  AXUI,         // MacOS
  IACCESSIBLE2, // Windows
};

class ContextImpl;
typedef std::unique_ptr<ContextImpl> ContextImplPtr;

class ContextImpl {
public:
  virtual enum AccessibleAPIType GetAccessibleAPIType() = 0;
  virtual NodePtr GetAccessibleRootByPID(int pid) = 0;
};


class Context;
typedef std::shared_ptr<Context> ContextPtr;

class Context {
 public:
  struct State;

  static ContextPtr Create();
  Context(State& aState);
  ~Context();

  enum AccessibleAPIType GetAccessibleAPIType();
  NodePtr GetAccessibleRootByPID(const int pid);
 private:
  State& m;
  ContextImplPtr impl;
};

}
