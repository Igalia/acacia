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

  bool isNull() { return !iface_; }
  std::string toString();
  long nActions();
  std::string getDescription(int index);
  std::string getName(int index);

 private:
  Microsoft::WRL::ComPtr<IAccessibleAction> iface_;
};

#endif  // LIB_IA2_IA_ACTION_H_
