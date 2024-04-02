#include "axaccess/ia2/ia_table_cell.h"

#include <stdexcept>

#include "axaccess/ia2/win_utils.h"

std::string IATableCell::toString() {
  if (isNull()) {
    return "Table Cell: Not implemented";
  }

  std::string result = "Table Cell: row=" + std::to_string(getRowIndex()) +
                       " column=" + std::to_string(getColumnIndex()) +
                       " rowspan=" + std::to_string(getRowExtent()) +
                       " colspan=" + std::to_string(getColumnExtent());
  return result;
}

long IATableCell::getColumnExtent() {
  if (iface_) {
    long span = 0;
    HRESULT hr = iface_->get_columnExtent(&span);
    if (FAILED(hr)) {
      throw std::runtime_error("ERROR: get_columnExtent failed: " +
                               HResultErrorToString(hr));
    }
    return span;
  }
  return 0;
}

long IATableCell::getColumnIndex() {
  if (iface_) {
    long index = 0;
    HRESULT hr = iface_->get_columnIndex(&index);
    if (FAILED(hr)) {
      throw std::runtime_error("ERROR: get_columnIndex failed: " +
                               HResultErrorToString(hr));
    }
    return index;
  }
  return -1;
}

long IATableCell::getRowExtent() {
  if (iface_) {
    long span = 0;
    HRESULT hr = iface_->get_rowExtent(&span);
    if (FAILED(hr)) {
      throw std::runtime_error("ERROR: get_rowExtent failed: " +
                               HResultErrorToString(hr));
    }
    return span;
  }
  return 0;
}

long IATableCell::getRowIndex() {
  if (iface_) {
    long index = 0;
    HRESULT hr = iface_->get_rowIndex(&index);
    if (FAILED(hr)) {
      throw std::runtime_error("ERROR: get_rowIndex failed: " +
                               HResultErrorToString(hr));
    }
    return index;
  }
  return -1;
}
