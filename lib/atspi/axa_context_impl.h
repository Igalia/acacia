#pragma once

#include <axaccess/context.h>
#include <string>

namespace AXA {

class AtspiContextImpl: public ContextImpl {
public:
  struct State;

  static AXA::ContextImplPtr Create();
  AtspiContextImpl(State& aState);
  ~AtspiContextImpl();

  enum AccessibleAPIType GetAccessibleAPIType() override;
  NodePtr GetAccessibleRootByPID(const int pid) override;

 private:
  State& m;
};

};
