#ifndef LIB_IA2_IA_TABLE2_H_
#define LIB_IA2_IA_TABLE2_H_

#include <string>

#include "axaccess/export.h"
#include "axaccess/ia2/ia_node.h"
#include "third_party/ia2/include/ia2/ia2_api_all.h"

class AXA_EXPORT IATable2 {
 public:
  IATable2(IANode node);
  ~IATable2(){};

  std::string GetProperties();
  long get_nColumns();
  long get_nRows();

 private:
  Microsoft::WRL::ComPtr<IAccessibleTable2> iface_;
};

#endif  // LIB_IA2_IA_TABLE2_H_
