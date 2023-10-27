#include <iostream>
#include <ostream>
#include <string>
#include <lib/atspi/atspi_wrapper.h>

std::string AtspiWrapper::GetRole() {
  GError* error = nullptr;
  char* role_name = atspi_accessible_get_role_name(accessible_, &error);
  if (error) {
    std::cerr << error->message;
    return "";
  }
  return role_name;
}

std::string AtspiWrapper::GetName() {
  GError* error = nullptr;
  char* name = atspi_accessible_get_name(accessible_, &error);
  if (error) {
    std::cerr << error->message;
    return "";
  }
  return name;
}
