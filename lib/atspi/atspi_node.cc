#include <acacia/atspi/atspi_node.h>

#include <assert.h>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>

#include <glib.h>

#include "scoped_g_lib_ptr.h"

namespace {
static const std::string StateTypeToString(const AtspiStateType state) {
  switch (state) {
    case ATSPI_STATE_INVALID:
      return "ATSPI_STATE_INVALID";
    case ATSPI_STATE_ACTIVE:
      return "ATSPI_STATE_ACTIVE";
    case ATSPI_STATE_ARMED:
      return "ATSPI_STATE_ARMED";
    case ATSPI_STATE_BUSY:
      return "ATSPI_STATE_BUSY";
    case ATSPI_STATE_CHECKED:
      return "ATSPI_STATE_CHECKED";
    case ATSPI_STATE_COLLAPSED:
      return "ATSPI_STATE_COLLAPSED";
    case ATSPI_STATE_DEFUNCT:
      return "ATSPI_STATE_DEFUNCT";
    case ATSPI_STATE_EDITABLE:
      return "ATSPI_STATE_EDITABLE";
    case ATSPI_STATE_ENABLED:
      return "ATSPI_STATE_ENABLED";
    case ATSPI_STATE_EXPANDABLE:
      return "ATSPI_STATE_EXPANDABLE";
    case ATSPI_STATE_EXPANDED:
      return "ATSPI_STATE_EXPANDED";
    case ATSPI_STATE_FOCUSABLE:
      return "ATSPI_STATE_FOCUSABLE";
    case ATSPI_STATE_FOCUSED:
      return "ATSPI_STATE_FOCUSED";
    case ATSPI_STATE_HAS_TOOLTIP:
      return "ATSPI_STATE_HAS_TOOLTIP";
    case ATSPI_STATE_HORIZONTAL:
      return "ATSPI_STATE_HORIZONTAL";
    case ATSPI_STATE_ICONIFIED:
      return "ATSPI_STATE_ICONIFIED";
    case ATSPI_STATE_MODAL:
      return "ATSPI_STATE_MODAL";
    case ATSPI_STATE_MULTI_LINE:
      return "ATSPI_STATE_MULTI_LINE";
    case ATSPI_STATE_MULTISELECTABLE:
      return "ATSPI_STATE_MULTISELECTABLE";
    case ATSPI_STATE_OPAQUE:
      return "ATSPI_STATE_OPAQUE";
    case ATSPI_STATE_PRESSED:
      return "ATSPI_STATE_PRESSED";
    case ATSPI_STATE_RESIZABLE:
      return "ATSPI_STATE_RESIZABLE";
    case ATSPI_STATE_SELECTABLE:
      return "ATSPI_STATE_SELECTABLE";
    case ATSPI_STATE_SELECTED:
      return "ATSPI_STATE_SELECTED";
    case ATSPI_STATE_SENSITIVE:
      return "ATSPI_STATE_SENSITIVE";
    case ATSPI_STATE_SHOWING:
      return "ATSPI_STATE_SHOWING";
    case ATSPI_STATE_SINGLE_LINE:
      return "ATSPI_STATE_SINGLE_LINE";
    case ATSPI_STATE_STALE:
      return "ATSPI_STATE_STALE";
    case ATSPI_STATE_TRANSIENT:
      return "ATSPI_STATE_TRANSIENT";
    case ATSPI_STATE_VERTICAL:
      return "ATSPI_STATE_VERTICAL";
    case ATSPI_STATE_VISIBLE:
      return "ATSPI_STATE_VISIBLE";
    case ATSPI_STATE_MANAGES_DESCENDANTS:
      return "ATSPI_STATE_MANAGES_DESCENDANTS";
    case ATSPI_STATE_INDETERMINATE:
      return "ATSPI_STATE_INDETERMINATE";
    case ATSPI_STATE_REQUIRED:
      return "ATSPI_STATE_REQUIRED";
    case ATSPI_STATE_TRUNCATED:
      return "ATSPI_STATE_TRUNCATED";
    case ATSPI_STATE_ANIMATED:
      return "ATSPI_STATE_ANIMATED";
    case ATSPI_STATE_INVALID_ENTRY:
      return "ATSPI_STATE_INVALID_ENTRY";
    case ATSPI_STATE_SUPPORTS_AUTOCOMPLETION:
      return "ATSPI_STATE_SUPPORTS_AUTOCOMPLETION";
    case ATSPI_STATE_SELECTABLE_TEXT:
      return "ATSPI_STATE_SELECTABLE_TEXT";
    case ATSPI_STATE_IS_DEFAULT:
      return "ATSPI_STATE_IS_DEFAULT";
    case ATSPI_STATE_VISITED:
      return "ATSPI_STATE_VISITED";
    case ATSPI_STATE_CHECKABLE:
      return "ATSPI_STATE_CHECKABLE";
    case ATSPI_STATE_HAS_POPUP:
      return "ATSPI_STATE_HAS_POPUP";
    case ATSPI_STATE_READ_ONLY:
      return "ATSPI_STATE_READ_ONLY";
    default:
      return "ATSPI_STATE_UNKNOWN";
  }
}

static const std::string RelationTypeToString(
    const AtspiRelationType relation) {
  switch (relation) {
    case ATSPI_RELATION_NULL:
      return "ATSPI_RELATION_NULL";
    case ATSPI_RELATION_LABEL_FOR:
      return "ATSPI_RELATION_LABEL_FOR";
    case ATSPI_RELATION_LABELLED_BY:
      return "ATSPI_RELATION_LABELLED_BY";
    case ATSPI_RELATION_CONTROLLER_FOR:
      return "ATSPI_RELATION_CONTROLLER_FOR";
    case ATSPI_RELATION_CONTROLLED_BY:
      return "ATSPI_RELATION_CONTROLLED_BY";
    case ATSPI_RELATION_MEMBER_OF:
      return "ATSPI_RELATION_MEMBER_OF";
    case ATSPI_RELATION_TOOLTIP_FOR:
      return "ATSPI_RELATION_TOOLTIP_FOR";
    case ATSPI_RELATION_NODE_CHILD_OF:
      return "ATSPI_RELATION_NODE_CHILD_OF";
    case ATSPI_RELATION_NODE_PARENT_OF:
      return "ATSPI_RELATION_NODE_PARENT_OF";
    case ATSPI_RELATION_EXTENDED:
      return "ATSPI_RELATION_EXTENDED";
    case ATSPI_RELATION_FLOWS_TO:
      return "ATSPI_RELATION_FLOWS_TO";
    case ATSPI_RELATION_FLOWS_FROM:
      return "ATSPI_RELATION_FLOWS_FROM";
    case ATSPI_RELATION_SUBWINDOW_OF:
      return "ATSPI_RELATION_SUBWINDOW_OF";
    case ATSPI_RELATION_EMBEDS:
      return "ATSPI_RELATION_EMBEDS";
    case ATSPI_RELATION_EMBEDDED_BY:
      return "ATSPI_RELATION_EMBEDDED_BY";
    case ATSPI_RELATION_POPUP_FOR:
      return "ATSPI_RELATION_POPUP_FOR";
    case ATSPI_RELATION_PARENT_WINDOW_OF:
      return "ATSPI_RELATION_PARENT_WINDOW_OF";
    case ATSPI_RELATION_DESCRIPTION_FOR:
      return "ATSPI_RELATION_DESCRIPTION_FOR";
    case ATSPI_RELATION_DESCRIBED_BY:
      return "ATSPI_RELATION_DESCRIBED_BY";
    case ATSPI_RELATION_DETAILS:
      return "ATSPI_RELATION_DETAILS";
    case ATSPI_RELATION_DETAILS_FOR:
      return "ATSPI_RELATION_DETAILS_FOR";
    case ATSPI_RELATION_ERROR_MESSAGE:
      return "ATSPI_RELATION_ERROR_MESSAGE";
    case ATSPI_RELATION_ERROR_FOR:
      return "ATSPI_RELATION_ERROR_FOR";
    default:
      return "ATSPI_RELATION_UNKNOWN";
  }
}

void free_g_array_and_contents(GArray* array) {
  g_array_free(array, TRUE);
}

}  // Namespace

namespace acacia {

using ScopedCStr = ScopedGLibPtr<char>;
using ScopedGError = ScopedGTypePtr<GError, &g_error_free>;
using ScopedGHashTable = ScopedGTypePtr<GHashTable, &g_hash_table_destroy>;
using ScopedGArray = ScopedGTypePtr<GArray, &free_g_array_and_contents>;

bool AtspiNode::isNull() const {
  return accessible_.get() == NULL;
}

std::string AtspiNode::getRoleName() const {
  ScopedGError error;
  GError* error_ptr = error.get();
  ScopedCStr role_name(
      atspi_accessible_get_role_name(accessible_.get(), &error_ptr));
  if (error_ptr) {
    std::string err_msg = error->message;
    throw std::runtime_error(err_msg);
    return "";
  }

  return std::string(role_name.get());
}

std::string AtspiNode::getName() const {
  ScopedGError error;
  GError* error_ptr = error.get();
  ScopedCStr name(atspi_accessible_get_name(accessible_.get(), &error_ptr));
  if (error_ptr) {
    std::string err_msg = error->message;
    throw std::runtime_error(err_msg);
  }

  return std::string(name.get());
}

std::string AtspiNode::getDescription() const {
  ScopedGError error;
  GError* error_ptr = error.get();
  ScopedCStr description(
      atspi_accessible_get_description(accessible_.get(), &error_ptr));
  if (error_ptr) {
    std::string err_msg = error->message;
    throw std::runtime_error(err_msg);
  }

  return std::string(description.get());
}

std::vector<std::string> AtspiNode::getAttributes() const {
  ScopedGError error;
  GError* error_ptr = error.get();
  ScopedGHashTable attributes_hash(
      atspi_accessible_get_attributes(accessible_.get(), &error_ptr));
  if (error_ptr) {
    std::string err_msg = error->message;
    throw std::runtime_error(err_msg);
  }
  if (!attributes_hash.get()) {
    // TODO: this element probably does not exist any more, and should be marked
    throw std::runtime_error("ERROR: Attributes do not exist");
  }

  std::vector<std::string> attributes;
  GHashTableIter iter;
  gpointer key, value;
  g_hash_table_iter_init(&iter, attributes_hash.get());
  while (g_hash_table_iter_next(&iter, &key, &value)) {
    std::string attr_entry =
        static_cast<char*>(key) + std::string(":") + static_cast<char*>(value);
    attributes.push_back(attr_entry);
  }

  return attributes;
}

std::vector<std::string> AtspiNode::getInterfaces() const {
  ScopedGArray interface_array(
      atspi_accessible_get_interfaces(accessible_.get()));
  std::vector<std::string> interfaces;
  for (unsigned i = 0; i < interface_array->len; i++) {
    ScopedCStr interface(g_array_index(interface_array, char*, i));
    interfaces.push_back(interface.get());
  }
  return interfaces;
}

std::vector<std::string> AtspiNode::getRelations() const {
  ScopedGError error;
  GError* error_ptr = error.get();
  ScopedGArray relation_array(
      atspi_accessible_get_relation_set(accessible_.get(), &error_ptr));
  if (error_ptr) {
    std::string err_msg = error->message;
    throw std::runtime_error(err_msg);
  }

  std::vector<std::string> relations;
  for (unsigned i = 0; i < relation_array->len; i++) {
    ScopedGObjectPtr<AtspiRelation> relation(
        g_array_index(relation_array.get(), AtspiRelation*, i));
    AtspiRelationType relation_type =
        atspi_relation_get_relation_type(relation.get());
    relations.push_back(RelationTypeToString(relation_type));
  }
  return relations;
}

AtspiNode AtspiNode::getTargetForRelationAtIndex(int relation_index,
                                                 int target_index) const {
  ScopedGError error;
  GError* error_ptr = error.get();
  ScopedGArray relation_array(
      atspi_accessible_get_relation_set(accessible_.get(), &error_ptr));
  if (error_ptr) {
    std::string err_msg = error->message;
    throw std::runtime_error(err_msg);
  }

  if (static_cast<uint>(relation_index) >= relation_array->len) {
    std::string msg = "Relation index " + std::to_string(relation_index) +
                      " exceeds relation count " +
                      std::to_string(relation_array->len);
    throw std::runtime_error(msg);
  }

  AtspiRelation* relation =
      g_array_index(relation_array.get(), AtspiRelation*, relation_index);
  AtspiAccessible* target = atspi_relation_get_target(relation, target_index);
  if (!target) {
    throw std::runtime_error("Target is null");
  }

  return AtspiNode(target);
}

std::vector<std::string> AtspiNode::getStates() const {
  ScopedGObjectPtr<AtspiStateSet> atspi_states(
      atspi_accessible_get_state_set(accessible_.get()));
  ScopedGArray state_array(atspi_state_set_get_states(atspi_states.get()));

  std::vector<std::string> states;
  for (unsigned i = 0; i < state_array->len; i++) {
    AtspiStateType state_type = g_array_index(state_array, AtspiStateType, i);
    states.push_back(StateTypeToString(state_type));
  }

  return states;
}

int AtspiNode::getChildCount() const {
  ScopedGError error;
  GError* error_ptr = error.get();
  gint count = atspi_accessible_get_child_count(accessible_.get(), &error_ptr);
  if (error_ptr) {
    std::string err_msg = error->message;
    throw std::runtime_error(err_msg);
  }
  return (int)count;
}

AtspiNode AtspiNode::getChildAtIndex(int index) const {
  ScopedGError error;
  GError* error_ptr = error.get();
  AtspiAccessible* child =
      atspi_accessible_get_child_at_index(accessible_.get(), index, &error_ptr);
  if (error_ptr) {
    std::string err_msg = error->message;
    throw std::runtime_error(err_msg);
  }
  return AtspiNode(child);
}

std::vector<AtspiNode> AtspiNode::getChildren() const {
  std::vector<AtspiNode> result;

  ScopedGError error;
  GError* error_ptr = error.get();
  gint child_count =
      atspi_accessible_get_child_count(accessible_.get(), &error_ptr);
  if (error_ptr) {
    std::string err_msg = error->message;
    throw std::runtime_error(err_msg);
  }

  result.resize(child_count);

  for (auto i = 0; i < child_count; i++) {
    AtspiNode child_node = getChildAtIndex(i);
    if (!child_node.isNull())
      result[i] = child_node;
  }

  return result;
}

// N.B. Because GObject does not allow you to add an interface after the class
// initialization, all possible interfaces must be added to AtspiAccessible
// unconditionally. As a result, the ATSPI_IS_* macros return true even when the
// interface is not implemented on the object. In addition, the function that
// determines whether or not an object implements an interface is private
// (_atspi_accessible_is_a). The creation of one or more public functions for
// determining implemented interfaces at run time has been requested. In the
// meantime, the only option we have is to get (and immediately unref) the
// interface. See https://gitlab.gnome.org/GNOME/at-spi2-core/-/issues/167 for
// details.
AtspiActionInterface AtspiNode::queryAction() const {
  ScopedGObjectPtr<AtspiAction> iface(
      atspi_accessible_get_action_iface(accessible_.get()));
  if (iface.get()) {
    return AtspiActionInterface(iface.release());
  }

  return AtspiActionInterface();
}

AtspiComponentInterface AtspiNode::queryComponent() const {
  ScopedGObjectPtr<AtspiComponent> iface(
      atspi_accessible_get_component_iface(accessible_.get()));
  if (iface.get()) {
    return AtspiComponentInterface(iface.release());
  }

  return AtspiComponentInterface();
}

AtspiDocumentInterface AtspiNode::queryDocument() const {
  ScopedGObjectPtr<AtspiDocument> iface(
      atspi_accessible_get_document_iface(accessible_.get()));
  if (iface.get()) {
    return AtspiDocumentInterface(iface.release());
  }

  return AtspiDocumentInterface();
}

AtspiHyperlinkInterface AtspiNode::queryHyperlink() const {
  ScopedGObjectPtr<AtspiHyperlink> iface(
      atspi_accessible_get_hyperlink(accessible_.get()));
  if (iface.get()) {
    return AtspiHyperlinkInterface(iface.release());
  }

  return AtspiHyperlinkInterface();
}

AtspiTableInterface AtspiNode::queryTable() const {
  ScopedGObjectPtr<AtspiTable> iface(
      atspi_accessible_get_table_iface(accessible_.get()));
  if (iface.get()) {
    return AtspiTableInterface(iface.release());
  }

  return AtspiTableInterface();
}

AtspiTableCellInterface AtspiNode::queryTableCell() const {
  ScopedGObjectPtr<AtspiTableCell> iface(
      atspi_accessible_get_table_cell(accessible_.get()));
  if (iface.get()) {
    return AtspiTableCellInterface(iface.release());
  }

  return AtspiTableCellInterface();
}

AtspiTextInterface AtspiNode::queryText() const {
  ScopedGObjectPtr<AtspiText> iface(
      atspi_accessible_get_text_iface(accessible_.get()));
  if (iface.get()) {
    return AtspiTextInterface(iface.release());
  }

  return AtspiTextInterface();
}

AtspiValueInterface AtspiNode::queryValue() const {
  ScopedGObjectPtr<AtspiValue> iface(
      atspi_accessible_get_value_iface(accessible_.get()));
  if (iface.get()) {
    return AtspiValueInterface(iface.release());
  }

  return AtspiValueInterface();
}

}  // namespace acacia
