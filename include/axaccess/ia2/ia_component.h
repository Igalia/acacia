#ifndef LIB_IA2_IA_COMPONENT_H_
#define LIB_IA2_IA_COMPONENT_H_

#include <string>

#include <wrl/client.h>

#include "axaccess/export.h"
#include "third_party/ia2/include/ia2/ia2_api_all.h"

class AXA_EXPORT IAComponent {
 public:
  IAComponent(Microsoft::WRL::ComPtr<IAccessibleComponent> iface)
      : iface_(iface) {}
  ~IAComponent(){};

  bool isNull() { return !iface_; }
  std::string toString();
  std::string getBackground();
  std::string getForeground();
  std::pair<long, long> getLocationInParent();

 private:
  Microsoft::WRL::ComPtr<IAccessibleComponent> iface_;
};

#endif  // LIB_IA2_IA_COMPONENT_H_
