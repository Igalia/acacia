#include <axaccess/atspi/atspi_value_interface.h>

#include <assert.h>
#include <iostream>
#include <stdexcept>
#include <string>

std::string AtspiValueInterface::toString() const {
  if (isNull()) {
    return "Not implemented";
  }

  return "current=" + std::to_string(getCurrentValue()) +
         " min=" + std::to_string(getMinimumValue()) +
         " max=" + std::to_string(getMaximumValue());
}

double AtspiValueInterface::getCurrentValue() const {
  if (isNull()) {
    return 0.0;
  }

  GError* error = nullptr;
  double result = atspi_value_get_current_value(interface_, &error);
  if (error) {
    std::string err_msg = error->message;
    g_error_free(error);
    throw std::runtime_error(err_msg);
  }
  return result;
}

double AtspiValueInterface::getMaximumValue() const {
  if (isNull()) {
    return 0.0;
  }

  GError* error = nullptr;
  double result = atspi_value_get_maximum_value(interface_, &error);
  if (error) {
    std::string err_msg = error->message;
    g_error_free(error);
    throw std::runtime_error(err_msg);
  }
  return result;
}

double AtspiValueInterface::getMinimumValue() const {
  if (isNull()) {
    return 0.0;
  }

  GError* error = nullptr;
  double result = atspi_value_get_minimum_value(interface_, &error);
  if (error) {
    std::string err_msg = error->message;
    g_error_free(error);
    throw std::runtime_error(err_msg);
  }
  return result;
}
