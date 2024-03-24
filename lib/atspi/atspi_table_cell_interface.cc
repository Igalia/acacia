#include <axaccess/atspi/atspi_table_cell_interface.h>

#include <assert.h>
#include <iostream>
#include <stdexcept>
#include <string>

std::string AtspiTableCellInterface::toString() const {
  if (isNull()) {
    return "Not implemented";
  }

  return "row=" + std::to_string(getRowIndex()) +
         " column=" + std::to_string(getColumnIndex()) +
         " rowspan=" + std::to_string(getRowSpan()) +
         " colspan=" + std::to_string(getColumnSpan());
}

std::pair<int, int> AtspiTableCellInterface::getPosition() const {
  if (isNull()) {
    return std::make_pair(0, 0);
  }

  GError* error = nullptr;
  int row, column;
  atspi_table_cell_get_position(interface_, &row, &column, &error);
  if (error) {
    std::string err_msg = error->message;
    g_error_free(error);
    throw std::runtime_error(err_msg);
  }
  return std::make_pair(row, column);
}

int AtspiTableCellInterface::getColumnIndex() const {
  if (isNull()) {
    return 0;
  }

  return getPosition().second;
}

int AtspiTableCellInterface::getColumnSpan() const {
  if (isNull()) {
    return 0;
  }

  GError* error = nullptr;
  int result = atspi_table_cell_get_column_span(interface_, &error);
  if (error) {
    std::string err_msg = error->message;
    g_error_free(error);
    throw std::runtime_error(err_msg);
  }
  return result;
}

int AtspiTableCellInterface::getRowIndex() const {
  if (isNull()) {
    return 0;
  }

  return getPosition().first;
}

int AtspiTableCellInterface::getRowSpan() const {
  if (isNull()) {
    return 0;
  }

  GError* error = nullptr;
  int result = atspi_table_cell_get_row_span(interface_, &error);
  if (error) {
    std::string err_msg = error->message;
    g_error_free(error);
    throw std::runtime_error(err_msg);
  }
  return result;
}
