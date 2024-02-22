#include <axaccess/atspi/atspi_node.h>

#include <assert.h>
#include <iostream>
#include <ostream>
#include <string>

AtspiNode::~AtspiNode() {
  assert(accessible_);
  g_object_unref(accessible_);
}

// TODO: Discuss naming convention for these functions.
// I wanted "atspi_accessible_get_role_name" to be as close to the API
// as possible, but I get a compilation error.
std::string AtspiNode::accessible_get_role_name() {
  GError* error = nullptr;
  char* role_name = atspi_accessible_get_role_name(accessible_, &error);
  if (error) {
    std::cerr << error->message;
    g_error_free(error);
    return "";
  }
  return role_name;
}

std::string AtspiNode::accessible_get_name() {
  GError* error = nullptr;
  char* name = atspi_accessible_get_name(accessible_, &error);
  if (error) {
    std::cerr << error->message;
    g_error_free(error);
    return "";
  }
  return name;
}

int32_t AtspiNode::accessible_get_child_count() {
  GError* error = nullptr;
  gint count = atspi_accessible_get_child_count(accessible_, &error);
  if (error) {
    std::cerr << error->message;
    g_error_free(error);
    return -1;
  }
  return (int32_t)count;
}

AtspiNodePtr AtspiNode::accessible_get_child_at_index(int32_t index) {
  GError* error = nullptr;
  AtspiAccessible* child =
      atspi_accessible_get_child_at_index(accessible_, index, &error);
  if (error) {
    std::cerr << error->message;
    g_error_free(error);
    return nullptr;
  }
  return std::make_unique<AtspiNode>(AtspiNode(child));
}

std::vector<AtspiNodePtr> AtspiNode::accessible_get_children() {
  std::vector<AtspiNodePtr> result(0);

  GError* error = nullptr;
  gint child_count = atspi_accessible_get_child_count(accessible_, &error);
  if (error) {
    std::cerr << error->message;
    g_error_free(error);
    return result;
  }

  result.resize(child_count);

  for (auto i = 0; i < child_count; i++) {
    AtspiNodePtr child_node = accessible_get_child_at_index(i);
    if (child_node)
      result[i].swap(child_node);
  }

  return result;
}
