#include <axaccess/atspi/atspi_node.h>

#include <assert.h>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>

namespace {
static const std::string state_type_to_string(const AtspiStateType state) {
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

static const std::string relation_type_to_string(
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

}  // Namespace

bool AtspiNode::is_null() const {
  return accessible_ == NULL;
}

std::string AtspiNode::get_role_name() const {
  GError* error = nullptr;
  char* role_name = atspi_accessible_get_role_name(accessible_, &error);
  if (error) {
    std::string err_msg = error->message;
    g_error_free(error);
    throw std::runtime_error(err_msg);
    return "";
  }
  std::string result(role_name);
  g_free(role_name);
  return result;
}

std::string AtspiNode::get_name() const {
  GError* error = nullptr;
  char* name = atspi_accessible_get_name(accessible_, &error);
  if (error) {
    std::string err_msg = error->message;
    g_error_free(error);
    throw std::runtime_error(err_msg);
  }
  std::string result(name);
  g_free(name);
  return result;
}

std::string AtspiNode::get_description() const {
  GError* error = nullptr;
  char* description = atspi_accessible_get_description(accessible_, &error);
  if (error) {
    std::string err_msg = error->message;
    g_error_free(error);
    throw std::runtime_error(err_msg);
  }
  std::string result(description);
  g_free(description);
  return result;
}

std::vector<std::string> AtspiNode::get_attributes() const {
  GError* error = nullptr;
  GHashTable* attributes_hash =
      atspi_accessible_get_attributes(accessible_, &error);
  std::vector<std::string> attributes;
  if (error) {
    std::string err_msg = error->message;
    g_error_free(error);
    throw std::runtime_error(err_msg);
  }

  GHashTableIter iter;
  gpointer key, value;
  g_hash_table_iter_init(&iter, attributes_hash);
  while (g_hash_table_iter_next(&iter, &key, &value)) {
    std::string attr_entry =
        static_cast<char*>(key) + std::string(":") + static_cast<char*>(value);
    attributes.push_back(attr_entry);
  }

  g_hash_table_destroy(attributes_hash);
  return attributes;
}

std::vector<std::string> AtspiNode::get_interfaces() const {
  GArray* interface_array = atspi_accessible_get_interfaces(accessible_);
  std::vector<std::string> interfaces;
  for (unsigned i = 0; i < interface_array->len; i++) {
    char* interface = g_array_index(interface_array, char*, i);
    interfaces.push_back(interface);
    g_free(interface);
  }
  g_array_free(interface_array, TRUE);
  return interfaces;
}

std::vector<std::string> AtspiNode::get_relations() const {
  GError* error = nullptr;
  GArray* relation_array =
      atspi_accessible_get_relation_set(accessible_, &error);
  if (error) {
    std::string err_msg = error->message;
    g_error_free(error);
    throw std::runtime_error(err_msg);
  }

  std::vector<std::string> relations;
  for (unsigned i = 0; i < relation_array->len; i++) {
    AtspiRelation* relation = g_array_index(relation_array, AtspiRelation*, i);
    AtspiRelationType relation_type =
        atspi_relation_get_relation_type(relation);
    relations.push_back(relation_type_to_string(relation_type));
    g_free(relation);
  }
  g_array_free(relation_array, TRUE);
  return relations;
}

std::vector<std::string> AtspiNode::get_states() const {
  AtspiStateSet* atspi_states = atspi_accessible_get_state_set(accessible_);
  GArray* state_array = atspi_state_set_get_states(atspi_states);
  std::vector<std::string> states;
  for (unsigned i = 0; i < state_array->len; i++) {
    AtspiStateType state_type = g_array_index(state_array, AtspiStateType, i);
    states.push_back(state_type_to_string(state_type));
  }
  g_array_free(state_array, TRUE);
  g_object_unref(atspi_states);
  return states;
}

int AtspiNode::get_child_count() const {
  GError* error = nullptr;
  gint count = atspi_accessible_get_child_count(accessible_, &error);
  if (error) {
    std::string err_msg = error->message;
    g_error_free(error);
    throw std::runtime_error(err_msg);
  }
  return (int)count;
}

AtspiNode AtspiNode::get_child_at_index(int index) const {
  GError* error = nullptr;
  AtspiAccessible* child =
      atspi_accessible_get_child_at_index(accessible_, index, &error);
  if (error) {
    std::string err_msg = error->message;
    g_error_free(error);
    throw std::runtime_error(err_msg);
  }
  return AtspiNode(child);
}

std::vector<AtspiNode> AtspiNode::get_children() const {
  std::vector<AtspiNode> result;

  GError* error = nullptr;
  gint child_count = atspi_accessible_get_child_count(accessible_, &error);
  if (error) {
    std::string err_msg = error->message;
    g_error_free(error);
    throw std::runtime_error(err_msg);
  }

  result.resize(child_count);

  for (auto i = 0; i < child_count; i++) {
    AtspiNode child_node = get_child_at_index(i);
    if (!child_node.is_null())
      result[i] = child_node;
  }

  return result;
}

AtspiComponentInterface AtspiNode::query_component() const {
  if (ATSPI_IS_COMPONENT(accessible_)) {
    return AtspiComponentInterface(ATSPI_COMPONENT(accessible_));
  }

  return AtspiComponentInterface();
}
