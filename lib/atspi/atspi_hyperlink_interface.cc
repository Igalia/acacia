#include <acacia/atspi/atspi_hyperlink_interface.h>

#include <assert.h>
#include <iostream>
#include <stdexcept>
#include <string>

namespace acacia {

std::string AtspiHyperlinkInterface::toString() const {
  if (isNull()) {
    return "Not implemented";
  }

  return "'" + getURI(0) + "' chars " + std::to_string(getStartIndex()) + "-" +
         std::to_string(getEndIndex());
}

int AtspiHyperlinkInterface::getStartIndex() const {
  if (isNull()) {
    return -1;
  }

  GError* error = nullptr;
  double result = atspi_hyperlink_get_start_index(interface_.get(), &error);
  if (error) {
    std::string err_msg = error->message;
    g_error_free(error);
    throw std::runtime_error(err_msg);
  }
  return result;
}

int AtspiHyperlinkInterface::getEndIndex() const {
  if (isNull()) {
    return -1;
  }

  GError* error = nullptr;
  double result = atspi_hyperlink_get_end_index(interface_.get(), &error);
  if (error) {
    std::string err_msg = error->message;
    g_error_free(error);
    throw std::runtime_error(err_msg);
  }
  return result;
}

std::string AtspiHyperlinkInterface::getURI(int index) const {
  if (isNull()) {
    return std::string();
  }

  GError* error = nullptr;
  char* uri = atspi_hyperlink_get_uri(interface_.get(), index, &error);
  if (error) {
    std::string err_msg = error->message;
    g_error_free(error);
    throw std::runtime_error(err_msg);
  }
  std::string result(uri);
  g_free(uri);
  return result;
}

}  // namespace acacia
