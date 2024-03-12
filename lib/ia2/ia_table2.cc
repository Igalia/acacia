#include "axaccess/ia2/ia_table2.h"

IATable2::IATable2(IANode node) {
  if (auto service_provider = node.GetServiceProvider()) {
    service_provider->QueryService(IID_IAccessible, IID_PPV_ARGS(&iface_));
  }
}

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
    if (SUCCEEDED(iface_->get_nColumns(&count))) {
      return count;
    }
  }
  return 0;
}

long IATable2::get_nRows() {
  if (iface_) {
    long count = 0;
    if (SUCCEEDED(iface_->get_nRows(&count))) {
      return count;
    }
  }
  return 0;
}
