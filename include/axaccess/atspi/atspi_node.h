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

  bool isNull() const;

  std::string getRoleName() const;
  std::string getName() const;
  std::string getDescription() const;
  std::vector<std::string> getAttributes() const;
  std::vector<std::string> getInterfaces() const;
  std::vector<std::string> getRelations() const;
  std::vector<std::string> getStates() const;
  int getChildCount() const;
  AtspiNode getChildAtIndex(int index) const;
  std::vector<AtspiNode> getChildren() const;

  AtspiComponentInterface queryComponent() const;
};

#endif  // LIB_ATSPI_ATSPI_NODE_H_
