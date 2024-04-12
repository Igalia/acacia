#include "acacia/ia2/ia_table2.h"

#include <stdexcept>

#include "lib/ia2/win_utils.h"

namespace acacia {

std::string IATable2::toString() {
  if (isNull()) {
    return "Table2: Not implemented";
  }

  std::string result = "Table: rows=" + std::to_string(getNRows()) +
                       " columns=" + std::to_string(getNColumns());
  return result;
}

long IATable2::getNColumns() {
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

long IATable2::getNRows() {
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

}  // namespace acacia
