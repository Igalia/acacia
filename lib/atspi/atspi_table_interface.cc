#include <acacia/atspi/atspi_table_interface.h>

#include <assert.h>
#include <iostream>
#include <stdexcept>
#include <string>

std::string AtspiTableInterface::toString() const {
  if (isNull())
    return "Not implemented";

  return "rows=" + std::to_string(getNRows()) +
         " columns=" + std::to_string(getNColumns());
}

int AtspiTableInterface::getNColumns() const {
  if (isNull())
    return 0;

  GError* error = nullptr;
  int result = atspi_table_get_n_columns(interface_, &error);
  if (error) {
    std::string err_msg = error->message;
    g_error_free(error);
    throw std::runtime_error(err_msg);
  }
  return result;
}

int AtspiTableInterface::getNRows() const {
  if (isNull())
    return 0;

  GError* error = nullptr;
  int result = atspi_table_get_n_rows(interface_, &error);
  if (error) {
    std::string err_msg = error->message;
    g_error_free(error);
    throw std::runtime_error(err_msg);
  }
  return result;
}
