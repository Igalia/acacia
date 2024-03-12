#include "axaccess/ia2/ia_table_cell.h"

#include <stdexcept>

#include "axaccess/ia2/win_utils.h"

using namespace win_utils;

IATableCell::IATableCell(IANode node) {
  if (auto service_provider = node.GetServiceProvider()) {
    service_provider->QueryService(IID_IAccessible, IID_PPV_ARGS(&iface_));
  }
}

std::string IATableCell::GetProperties() {
  if (IsNull()) {
    return "Table Cell: Not implemented";
  }

  std::string result = "Table Cell: row=" + std::to_string(get_rowIndex()) +
                       " column=" + std::to_string(get_columnIndex()) +
                       " rowspan=" + std::to_string(get_rowExtent()) +
                       " colspan=" + std::to_string(get_columnExtent());
  return result;
}

long IATableCell::get_columnExtent() {
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

long IATableCell::get_columnIndex() {
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

long IATableCell::get_rowExtent() {
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

long IATableCell::get_rowIndex() {
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
