#include "axaccess/ia2/ia_table_cell.h"

IATableCell::IATableCell(IANode node) {
  if (auto service_provider = node.GetServiceProvider()) {
    service_provider->QueryService(IID_IAccessible, IID_PPV_ARGS(&iface_));
  }
}

std::string IATableCell::GetProperties() {
  if (!iface_) {
    return std::string();
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
    if (SUCCEEDED(iface_->get_columnExtent(&span))) {
      return span;
    }
  }
  return 0;
}

long IATableCell::get_columnIndex() {
  if (iface_) {
    long index = 0;
    if (SUCCEEDED(iface_->get_columnIndex(&index))) {
      return index;
    }
  }
  return -1;
}

long IATableCell::get_rowExtent() {
  if (iface_) {
    long span = 0;
    if (SUCCEEDED(iface_->get_rowExtent(&span))) {
      return span;
    }
  }
  return 0;
}

long IATableCell::get_rowIndex() {
  if (iface_) {
    long index = 0;
    if (SUCCEEDED(iface_->get_rowIndex(&index))) {
      return index;
    }
  }
  return -1;
}
