#ifndef LIB_ATSPI_ATSPI_NODE_H_
#define LIB_ATSPI_ATSPI_NODE_H_

#include <memory>
#include <string>
#include <vector>

#include <atspi/atspi.h>

class AtspiNode;
typedef std::unique_ptr<AtspiNode> AtspiNodePtr;

class AtspiNode {
  AtspiAccessible* accessible_;

 public:
  AtspiNode(AtspiAccessible* accessible) : accessible_(accessible){};
  ~AtspiNode();

  std::string get_role_name();
  std::string get_name();
  int get_child_count();
  AtspiNodePtr get_child_at_index(int index);
  std::vector<AtspiNodePtr> get_children();
};

#endif  // LIB_ATSPI_ATSPI_NODE_H_
