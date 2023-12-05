#ifndef LIB_ATSPI_ATSPI_NODE_H_
#define LIB_ATSPI_ATSPI_NODE_H_

#include <string>

#include <atspi/atspi.h>

class AtspiNode {
  AtspiAccessible* accessible_;

  public:
    AtspiNode(AtspiAccessible* accessible): accessible_(accessible) {};
    ~AtspiNode();

    std::string accessible_get_role_name();
    std::string accessible_get_name();
};

#endif // LIB_ATSPI_ATSPI_NODE_H_
