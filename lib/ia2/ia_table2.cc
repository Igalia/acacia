#include "axaccess/ia2/ia_table2.h"

std::string IATable2::GetProperties() {
  if (!QueryInterface()) {
    return std::string();
  }

  std::string result = "Table: rows=" + std::to_string(get_nRows()) +
                       " columns=" + std::to_string(get_nColumns());
  return result;
}

long IATable2::get_nColumns() {
  if (auto iface = QueryInterface()) {
    long count = 0;
    if (SUCCEEDED(iface->get_nColumns(&count))) {
      return count;
    }
  }
  return 0;
}

long IATable2::get_nRows() {
  if (auto iface = QueryInterface()) {
    long count = 0;
    if (SUCCEEDED(iface->get_nRows(&count))) {
      return count;
    }
  }
  return 0;
}

Microsoft::WRL::ComPtr<IAccessibleTable2> IATable2::QueryInterface() {
  if (node_.IsNull() || !node_.GetIAccessible()) {
    return nullptr;
  }

  Microsoft::WRL::ComPtr<IAccessibleTable2> iface;
  Microsoft::WRL::ComPtr<IServiceProvider> service_provider;
  HRESULT hr =
      node_.GetIAccessible()->QueryInterface(IID_PPV_ARGS(&service_provider));
  return SUCCEEDED(service_provider->QueryService(IID_IAccessible,
                                                  IID_PPV_ARGS(&iface)))
             ? iface
             : nullptr;
}
