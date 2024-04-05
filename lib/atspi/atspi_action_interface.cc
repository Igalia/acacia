#include <acacia/atspi/atspi_action_interface.h>

#include <assert.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "../utils.h"

namespace acacia {

std::string AtspiActionInterface::toString() const {
  if (isNull())
    return "Not implemented";

  std::vector<std::string> result;
  int count = getNActions();
  for (int i = 0; i < count; ++i) {
    result.push_back(getName(i));
  }
  return StringVectorToString(result);
}

int AtspiActionInterface::getNActions() const {
  if (isNull())
    return 0;

  GError* error = nullptr;
  int result = atspi_action_get_n_actions(interface_, &error);
  if (error) {
    std::string err_msg = error->message;
    g_error_free(error);
    throw std::runtime_error(err_msg);
  }
  return result;
}

std::string AtspiActionInterface::getName(int index) const {
  if (isNull())
    std::string();

  GError* error = nullptr;
  char* name = atspi_action_get_name(interface_, index, &error);
  if (error) {
    std::string err_msg = error->message;
    g_error_free(error);
    throw std::runtime_error(err_msg);
  }
  std::string result(name);
  g_free(name);
  return result;
}

std::string AtspiActionInterface::getDescription(int index) const {
  if (isNull())
    std::string();

  GError* error = nullptr;
  char* description = atspi_action_get_description(interface_, index, &error);
  if (error) {
    std::string err_msg = error->message;
    g_error_free(error);
    throw std::runtime_error(err_msg);
  }
  std::string result(description);
  g_free(description);
  return result;
}

}  // namespace acacia
