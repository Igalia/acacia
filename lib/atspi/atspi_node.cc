#include <axaccess/atspi/atspi_node.h>

#include <assert.h>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>

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
  return role_name;
}

std::string AtspiNode::get_name() const {
  GError* error = nullptr;
  char* name = atspi_accessible_get_name(accessible_, &error);
  if (error) {
    std::string err_msg = error->message;
    g_error_free(error);
    throw std::runtime_error(err_msg);
  }
  return name;
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
