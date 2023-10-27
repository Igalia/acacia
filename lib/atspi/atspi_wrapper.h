#include <string>

#include <atspi/atspi.h>

class AtspiWrapper {
  AtspiAccessible* accessible_;

  public:
    AtspiWrapper(AtspiAccessible* accessible): accessible_(accessible) {};

    std::string GetRole();
    std::string GetName();
};
