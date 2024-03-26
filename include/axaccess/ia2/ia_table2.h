#ifndef LIB_IA2_IA_TABLE2_H_
#define LIB_IA2_IA_TABLE2_H_

#include <string>

#include <wrl/client.h>

#include "axaccess/export.h"
#include "third_party/ia2/include/ia2/ia2_api_all.h"

class AXA_EXPORT IATable2 {
 public:
  IATable2(Microsoft::WRL::ComPtr<IAccessibleTable2> iface) : iface_(iface) {}
  ~IATable2(){};

  bool isNull() { return !iface_; }
  std::string toString();
  long getNColumns();
  long getNRows();

 private:
  Microsoft::WRL::ComPtr<IAccessibleTable2> iface_;
};

#endif  // LIB_IA2_IA_TABLE2_H_
