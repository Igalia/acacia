#pragma once

#include <memory>
#include "./node.h"

namespace axa {

enum APIType {
  UNKNOWN,
  ATSPI,        // Linux
  AXUI,         // MacOS
  IACCESSIBLE2, // Windows
};

class ContextImpl {
public:
  virtual enum APIType GetAPIType() = 0;
  virtual NodePtr GetAccessibleRootByPID(int pid) = 0;
};


class Context;
typedef std::shared_ptr<Context> ContextPtr;

class Context {
 public:
  static ContextPtr Create();
  Context();
  ~Context();

  enum APIType GetAPIType();
  NodePtr GetAccessibleRootByPID(const int pid);
 private:
  std::unique_ptr<ContextImpl> impl;
};

} // namespace axa
