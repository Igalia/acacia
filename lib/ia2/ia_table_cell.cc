#include "axaccess/ia2/ia_table_cell.h"

std::string IATableCell::GetProperties() {
  if (!QueryInterface()) {
    return std::string();
  }

  std::string result = "Table Cell: row=" + std::to_string(get_rowIndex()) +
                       " column=" + std::to_string(get_columnIndex()) +
                       " rowspan=" + std::to_string(get_rowExtent()) +
                       " colspan=" + std::to_string(get_columnExtent());
  return result;
}

long IATableCell::get_columnExtent() {
  if (auto iface = QueryInterface()) {
    long span = 0;
    if (SUCCEEDED(iface->get_columnExtent(&span))) {
      return span;
    }
  }
  return 0;
}

long IATableCell::get_columnIndex() {
  if (auto iface = QueryInterface()) {
    long index = 0;
    if (SUCCEEDED(iface->get_columnIndex(&index))) {
      return index;
    }
  }
  return -1;
}

long IATableCell::get_rowExtent() {
  if (auto iface = QueryInterface()) {
    long span = 0;
    if (SUCCEEDED(iface->get_rowExtent(&span))) {
      return span;
    }
  }
  return 0;
}

long IATableCell::get_rowIndex() {
  if (auto iface = QueryInterface()) {
    long index = 0;
    if (SUCCEEDED(iface->get_rowIndex(&index))) {
      return index;
    }
  }
  return -1;
}

Microsoft::WRL::ComPtr<IAccessibleTableCell> IATableCell::QueryInterface() {
  if (node_.IsNull() || !node_.GetIAccessible()) {
    return nullptr;
  }

  Microsoft::WRL::ComPtr<IAccessibleTableCell> iface;
  Microsoft::WRL::ComPtr<IServiceProvider> service_provider;
  HRESULT hr =
      node_.GetIAccessible()->QueryInterface(IID_PPV_ARGS(&service_provider));
  return SUCCEEDED(service_provider->QueryService(IID_IAccessible,
                                                  IID_PPV_ARGS(&iface)))
             ? iface
             : nullptr;
}
