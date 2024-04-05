#ifndef LIB_ATSPI_ATSPI_NODE_H_
#define LIB_ATSPI_ATSPI_NODE_H_

#include <string>
#include <vector>

#include <atspi/atspi.h>

#include "acacia/atspi/atspi_action_interface.h"
#include "acacia/atspi/atspi_component_interface.h"
#include "acacia/atspi/atspi_document_interface.h"
#include "acacia/atspi/atspi_hyperlink_interface.h"
#include "acacia/atspi/atspi_table_cell_interface.h"
#include "acacia/atspi/atspi_table_interface.h"
#include "acacia/atspi/atspi_text_interface.h"
#include "acacia/atspi/atspi_value_interface.h"

namespace acacia {

/**
 * Represents a node in the AT-SPI accessibility tree. This object wraps an
 * [AtspiAccessible](https://docs.gtk.org/atspi2/class.Accessible.html) pointer.
 * @ingroup atspi
 */
class AtspiNode {
  AtspiAccessible* accessible_;

 public:
  AtspiNode(AtspiAccessible* accessible) : accessible_(accessible){};
  AtspiNode() : accessible_(nullptr){};
  ~AtspiNode(){};

  /**
   * Tests whether the underlying AtspiAccessible pointer is the null pointer.
   * An AtspiNode with an null AtspiAccessible pointer will be created if the
   * wrapped API returned a nullptr with no error codes.
   * @ingroup atspi
   */
  bool isNull() const;

  /**
   * Wraps
   * [atspi_accessible_get_role_name](https://docs.gtk.org/atspi2/method.Accessible.get_role_name.html).
   * @ingroup atspi
   */
  std::string getRoleName() const;

  /**
   * Wraps
   * [atspi_accessible_get_name](https://docs.gtk.org/atspi2/method.Accessible.get_name.html).
   * @ingroup atspi
   */
  std::string getName() const;

  /**
   * Wraps
   * [atspi_accessible_get_description](https://docs.gtk.org/atspi2/method.Accessible.get_description.html).
   * @ingroup atspi
   */
  std::string getDescription() const;

  /**
   * Wraps
   * [atspi_accessible_get_attributes](https://docs.gtk.org/atspi2/method.Accessible.get_attributes.html).
   * @ingroup atspi
   *
   * @returns A vector of strings representing a GHashTable*. Each string in the
   * vector is a key value pair separated by a ":" character, for example,
   * "xml-roles:main".
   */
  std::vector<std::string> getAttributes() const;

  /**
   * Wraps
   * [atspi_accessible_get_interfaces](https://docs.gtk.org/atspi2/method.Accessible.get_interfaces.html).
   * @ingroup atspi
   *
   * @returns A vector of strings.
   */
  std::vector<std::string> getInterfaces() const;

  /**
   * Wraps
   * [atspi_accessible_get_relation_set](https://docs.gtk.org/atspi2/method.Accessible.get_relation_set.html).
   * @ingroup atspi
   *
   * @returns A vector of strings.
   */
  std::vector<std::string> getRelations() const;

  /**
   * Helper function to get an AtspiNode referred to by relation to this node.
   * @ingroup atspi
   *
   * @param relation_index: Index of the relation in array returned by @ref
   * getRelations.
   * @param target_index: Optional. Defaults to 0.
   *
   * @returns An @ref AtspiNode.
   */
  AtspiNode getTargetForRelationAtIndex(int relation_index,
                                        int target_index = 0) const;

  /**
   * Wraps
   * [atspi_accessible_get_states_set](https://docs.gtk.org/atspi2/method.Accessible.get_state_set.html)
   * to get the state set, and calls
   * [atspi_state_set_get_states](https://docs.gtk.org/atspi2/method.StateSet.get_states.html)
   * to get the string values for the state set.
   * @ingroup atspi
   *
   * @returns A vector of strings.
   */
  std::vector<std::string> getStates() const;

  /**
   * Wraps
   * [atspi_accessible_get_child_count](https://docs.gtk.org/atspi2/method.Accessible.get_child_count.html).
   * @ingroup atspi
   */
  int getChildCount() const;

  /**
   * Wraps
   * [atspi_accessible_get_child_at_index](https://docs.gtk.org/atspi2/method.Accessible.get_child_at_index.html).
   * @ingroup atspi
   *
   * @param index: Index of the child to retrieve.
   *
   * @returns An @ref AtspiNode.
   */
  AtspiNode getChildAtIndex(int index) const;

  /**
   * Helper function to return a vector of all children.
   * @ingroup atspi
   *
   * @returns An vector of @ref AtspiNode.
   */
  std::vector<AtspiNode> getChildren() const;

  /**
   * Wraps
   * [atspi_accessible_get_action_iface](https://docs.gtk.org/atspi2/method.Accessible.get_action_iface.html).
   * @ingroup atspi
   *
   * @returns An @ref AtspiActionInterface.
   */
  AtspiActionInterface queryAction() const;

  /**
   * Wraps
   * [atspi_accessible_get_component_iface](https://docs.gtk.org/atspi2/method.Accessible.get_component_iface.html).
   * @ingroup atspi
   *
   * @returns An @ref AtspiComponentInterface.
   */
  AtspiComponentInterface queryComponent() const;

  /**
   * Wraps
   * [atspi_accessible_get_document_iface](https://docs.gtk.org/atspi2/method.Accessible.get_document_iface.html).
   * @ingroup atspi
   *
   * @returns An @ref AtspiDocumentInterface.
   */
  AtspiDocumentInterface queryDocument() const;

  /**
   * Wraps
   * [atspi_accessible_get_hyperlink](https://docs.gtk.org/atspi2/method.Accessible.get_hyperlink.html).
   * @ingroup atspi
   *
   * @returns An @ref AtspiHyperlinkInterface.
   */
  AtspiHyperlinkInterface queryHyperlink() const;

  /**
   * Wraps
   * [atspi_accessible_get_table_iface](https://docs.gtk.org/atspi2/method.Accessible.get_table_iface.html).
   * @ingroup atspi
   *
   * @returns An @ref AtspiTableInterface.
   */
  AtspiTableInterface queryTable() const;

  /**
   * Wraps
   * [atspi_accessible_get_table_cell](https://docs.gtk.org/atspi2/method.Accessible.get_table_cell.html).
   * @ingroup atspi
   *
   * @returns An @ref AtspiTableCellInterface.
   */
  AtspiTableCellInterface queryTableCell() const;

  /**
   * Wraps
   * [atspi_accessible_get_text_iface](https://docs.gtk.org/atspi2/method.Accessible.get_text_iface.html).
   * @ingroup atspi
   *
   * @returns An @ref AtspiTextInterface.
   */
  AtspiTextInterface queryText() const;

  /**
   * Wraps
   * [atspi_accessible_get_value_iface](https://docs.gtk.org/atspi2/method.Accessible.get_value_iface.html).
   * @ingroup atspi
   *
   * @returns An @ref AtspiValueInterface.
   */
  AtspiValueInterface queryValue() const;
};

}  // namespace acacia

#endif  // LIB_ATSPI_ATSPI_NODE_H_
