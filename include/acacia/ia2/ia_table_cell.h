#ifndef LIB_IA2_IA_TABLE_CELL_H_
#define LIB_IA2_IA_TABLE_CELL_H_

#include <string>

#include <wrl/client.h>

#include "acacia/export.h"
#include "third_party/ia2/include/ia2/ia2_api_all.h"

namespace acacia {

class ACACIA_EXPORT IATableCell {
 public:
  IATableCell(Microsoft::WRL::ComPtr<IAccessibleTableCell> iface)
      : iface_(iface) {}
  ~IATableCell(){};

  bool isNull() { return !iface_; }
  std::string toString();
  long getColumnExtent();
  long getColumnIndex();
  long getRowExtent();
  long getRowIndex();

 private:
  Microsoft::WRL::ComPtr<IAccessibleTableCell> iface_;
};

}  // namespace acacia

#endif  // LIB_IA2_IA_TABLE_CELL_H_
