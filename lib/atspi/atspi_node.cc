#include <assert.h>
#include <iostream>
#include <ostream>
#include <string>
#include <axaccess/atspi/atspi_node.h>

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
    return "";
  }
  return name;
}
