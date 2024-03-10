#ifndef LIB_IA2_IA_ACTION_H_
#define LIB_IA2_IA_ACTION_H_

#include <string>

#include "axaccess/export.h"
#include "axaccess/ia2/ia_node.h"
#include "third_party/ia2/include/ia2/ia2_api_all.h"

class AXA_EXPORT IAAction {
 public:
  IAAction(IANode node) : node_(node){};
  ~IAAction(){};

  std::string GetProperties();
  long nActions();
  std::string get_description(int index);
  std::string get_name(int index);

 private:
  Microsoft::WRL::ComPtr<IAccessibleAction> QueryInterface();
  IANode node_;
};

#endif  // LIB_IA2_IA_ACTION_H_
