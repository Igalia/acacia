#ifndef LIB_IA2_IA_VALUE_H_
#define LIB_IA2_IA_VALUE_H_

#include <string>

#include "axaccess/export.h"
#include "axaccess/ia2/ia_node.h"
#include "third_party/ia2/include/ia2/ia2_api_all.h"

class AXA_EXPORT IAValue {
 public:
  IAValue(IANode node);
  ~IAValue(){};

  bool IsNull() { return !iface_; }
  std::string GetProperties();
  std::string get_currentValue();
  std::string get_maximumValue();
  std::string get_minimumValue();

 private:
  Microsoft::WRL::ComPtr<IAccessibleValue> iface_;
};

#endif  // LIB_IA2_IA_VALUE_H_
