#include <iostream>
#include <ostream>
#include <string>
#include <lib/atspi/atspi_node.h>

// TODO: Discuss naming convention for these functions.
// I wanted "atspi_accessible_get_role_name" to be as close to the API
// as possible, but I get a compilation error.
std::string AtspiNode::accessible_get_role_name() {
  GError* error = nullptr;
  char* role_name = atspi_accessible_get_role_name(accessible_, &error);
  if (error) {
    std::cerr << error->message;
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
