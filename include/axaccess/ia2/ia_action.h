#ifndef LIB_IA2_IA_ACTION_H_
#define LIB_IA2_IA_ACTION_H_

#include <string>

#include <wrl/client.h>

#include "axaccess/export.h"
#include "third_party/ia2/include/ia2/ia2_api_all.h"

class AXA_EXPORT IAAction {
 public:
  IAAction(Microsoft::WRL::ComPtr<IAccessibleAction> iface) : iface_(iface) {}
  ~IAAction(){};

  bool IsNull() { return !iface_; }
  std::string GetProperties();
  long nActions();
  std::string get_description(int index);
  std::string get_name(int index);

 private:
  Microsoft::WRL::ComPtr<IAccessibleAction> iface_;
};

#endif  // LIB_IA2_IA_ACTION_H_
