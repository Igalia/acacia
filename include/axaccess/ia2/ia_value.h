#ifndef LIB_IA2_IA_VALUE_H_
#define LIB_IA2_IA_VALUE_H_

#include <string>

#include <wrl/client.h>

#include "axaccess/export.h"
#include "third_party/ia2/include/ia2/ia2_api_all.h"

class AXA_EXPORT IAValue {
 public:
  IAValue(Microsoft::WRL::ComPtr<IAccessibleValue> iface) : iface_(iface) {}
  ~IAValue(){};

  bool isNull() { return !iface_; }
  std::string toString();
  std::string getCurrentValue();
  std::string getMaximumValue();
  std::string getMinimumValue();

 private:
  Microsoft::WRL::ComPtr<IAccessibleValue> iface_;
};

#endif  // LIB_IA2_IA_VALUE_H_
