#ifndef LIB_IA2_IA2_NODE_H_
#define LIB_IA2_IA2_NODE_H_

#include <memory>
#include <string>
#include <vector>

#include <oleacc.h>
#include <wrl/client.h>

#include "axaccess/export.h"

class IA2Node;
typedef std::unique_ptr<IA2Node> IA2NodePtr;

class AXA_EXPORT IA2Node {
 public:
  IA2Node(Microsoft::WRL::ComPtr<IAccessible> root, VARIANT child_id)
      : root_(root), child_id_(child_id){};
  IA2Node(Microsoft::WRL::ComPtr<IAccessible> root) : root_(root) {
    child_id_.intVal = CHILDID_SELF;
    child_id_.vt = VT_I4;
  };
  ~IA2Node(){};

  static IA2NodePtr CreateForPID(const int pid);
  // testing
  static void DumpRoleTree(const int pid);

  std::string get_accRole();
  std::string get_accName();

  std::string ia2_role();

  long IA2Node::get_accChildCount();
  IA2NodePtr IA2Node::AccessibleChildAt(int index);

 private:
  Microsoft::WRL::ComPtr<IAccessible> root_;
  // This variant is used to recieve IAccessible
  // information about either the accessible object itself,
  // or its partial child.
  // TODO: Create own type for partial children. #95
  VARIANT child_id_;
};

#endif  // LIB_IA2_IA2_NODE_H_
