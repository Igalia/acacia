#ifndef LIB_IA2_IA_NODE_H_
#define LIB_IA2_IA_NODE_H_

#include <memory>
#include <string>
#include <vector>

#include <oleacc.h>
#include <wrl/client.h>

#include "axaccess/export.h"
#include "axaccess/ia2/ia_2.h"
#include "axaccess/ia2/ia_action.h"
#include "axaccess/ia2/ia_component.h"
#include "axaccess/ia2/ia_hyperlink.h"
#include "axaccess/ia2/ia_table2.h"
#include "axaccess/ia2/ia_table_cell.h"
#include "axaccess/ia2/ia_text.h"
#include "axaccess/ia2/ia_value.h"

class AXA_EXPORT IANode {
 public:
  IANode(){};
  IANode(Microsoft::WRL::ComPtr<IAccessible> root, VARIANT child_id)
      : root_(root), child_id_(child_id){};
  IANode(Microsoft::WRL::ComPtr<IAccessible> root) : root_(root) {
    child_id_.intVal = CHILDID_SELF;
    child_id_.vt = VT_I4;
  };
  ~IANode(){};

  static IANode CreateRootForName(const std::string& name, const int pid = 0);
  static IANode CreateRootForPID(const int pid);

  IA2 QueryIA2();
  IAAction QueryAction();
  IAComponent QueryComponent();
  IAHyperlink QueryHyperlink();
  IATableCell QueryTableCell();
  IATable2 QueryTable2();
  IAText QueryText();
  IAValue QueryValue();

  bool IsNull();

  std::string get_accRole();
  std::string get_accName();
  std::string get_accDescription();

  long get_accChildCount();
  IANode AccessibleChildAt(int index);

  long get_accState();
  std::vector<std::string> GetStates();

  Microsoft::WRL::ComPtr<IServiceProvider> GetServiceProvider();

 private:
  Microsoft::WRL::ComPtr<IAccessible> root_;
  // This variant is used to recieve IAccessible
  // information about either the accessible object itself,
  // or its partial child.
  // TODO: Create own type for partial children. #95
  VARIANT child_id_;
};

#endif  // LIB_IA2_IA_NODE_H_
