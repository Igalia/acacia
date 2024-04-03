#pragma once

#include <memory>
#include "acacia/export.h"

#include "./node.h"

namespace axa {

enum APIType {
  UNKNOWN,
  ATSPI,         // Linux
  AXAPI,         // MacOS
  IACCESSIBLE2,  // Windows
};

class ContextImpl {
 public:
  virtual ~ContextImpl(){};
  virtual enum APIType GetAPIType() = 0;
  virtual NodePtr GetAccessibleRootByPID(int pid) = 0;
};

class Context;
typedef std::shared_ptr<Context> ContextPtr;

class AXA_EXPORT Context {
 public:
  static ContextPtr Create();
  Context();
  ~Context();

  enum APIType GetAPIType();
  NodePtr GetAccessibleRootByPID(const int pid);

 private:
  std::unique_ptr<ContextImpl> impl;
};

}  // namespace axa
