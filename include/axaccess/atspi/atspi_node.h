#ifndef LIB_ATSPI_ATSPI_NODE_H_
#define LIB_ATSPI_ATSPI_NODE_H_

#include <string>
#include <vector>

#include <atspi/atspi.h>

#include "axaccess/atspi/atspi_component_interface.h"

/**
 * Represents a node in the accessibility tree.
 * @ingroup atspi
 */
class AtspiNode {
  AtspiAccessible* accessible_;

 public:
  AtspiNode(AtspiAccessible* accessible) : accessible_(accessible){};
  AtspiNode() : accessible_(nullptr){};
  ~AtspiNode(){};

  bool is_null() const;

  std::string get_role_name() const;
  std::string get_name() const;
  std::string get_description() const;
  std::vector<std::string> get_attributes() const;
  std::vector<std::string> get_interfaces() const;
  std::vector<std::string> get_relations() const;
  std::vector<std::string> get_states() const;
  int get_child_count() const;
  AtspiNode get_child_at_index(int index) const;
  std::vector<AtspiNode> get_children() const;

  AtspiComponentInterface query_component() const;
};

#endif  // LIB_ATSPI_ATSPI_NODE_H_
