#ifndef LIB_IA2_IA_TABLE_CELL_H_
#define LIB_IA2_IA_TABLE_CELL_H_

#include <string>

#include <wrl/client.h>

#include "axaccess/export.h"
#include "third_party/ia2/include/ia2/ia2_api_all.h"

class AXA_EXPORT IATableCell {
 public:
  IATableCell(Microsoft::WRL::ComPtr<IAccessibleTableCell> iface)
      : iface_(iface) {}
  ~IATableCell(){};

  bool IsNull() { return !iface_; }
  std::string GetProperties();
  long get_columnExtent();
  long get_columnIndex();
  long get_rowExtent();
  long get_rowIndex();

 private:
  Microsoft::WRL::ComPtr<IAccessibleTableCell> iface_;
};

#endif  // LIB_IA2_IA_TABLE_CELL_H_
