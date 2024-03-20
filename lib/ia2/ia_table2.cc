#include "axaccess/ia2/ia_table2.h"

#include <stdexcept>

#include "axaccess/ia2/win_utils.h"

using namespace win_utils;

std::string IATable2::GetProperties() {
  if (IsNull()) {
    return "Table2: Not implemented";
  }

  std::string result = "Table: rows=" + std::to_string(get_nRows()) +
                       " columns=" + std::to_string(get_nColumns());
  return result;
}

long IATable2::get_nColumns() {
  if (iface_) {
    long count = 0;
    HRESULT hr = iface_->get_nColumns(&count);
    if (FAILED(hr)) {
      throw std::runtime_error("ERROR: get_nColumns failed: " +
                               HResultErrorToString(hr));
    }
    return count;
  }
  return 0;
}

long IATable2::get_nRows() {
  if (iface_) {
    long count = 0;
    HRESULT hr = iface_->get_nRows(&count);
    if (FAILED(hr)) {
      throw std::runtime_error("ERROR: get_nRows failed: " +
                               HResultErrorToString(hr));
    }
    return count;
  }
  return 0;
}