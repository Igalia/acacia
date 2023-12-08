%module mac_inspect
%{
#include <axaccess/mac/mac_inspect.h>
%}

%include "std_string.i"

namespace MacInspect {
  void logInfoForPID(long pid);

  class AXAPINode {
   public:
    getRole();
  };

  AXAPINode createAXAPINodeForApplication(long pid);
}
