#ifndef LIB_IA2_IA2_NODE_H_
#define LIB_IA2_IA2_NODE_H_

#include <memory>
#include <string>
#include <vector>

#include <oleacc.h>
#include <wrl/client.h>

#include "axaccess/export.h"

/** @defgroup ia2 IA2 API (Windows)
 *  IA2 Accessiblity API for Windows
 *  @{
 */
/** @} */ // end of axapi group

/**
 * Represents a node in the accessibility tree.
 * @ingroup ia2
 */
class AXA_EXPORT IA2Node {
 public:
  IA2Node(){};
  IA2Node(Microsoft::WRL::ComPtr<IAccessible> root, VARIANT child_id)
      : root_(root), child_id_(child_id){};
  IA2Node(Microsoft::WRL::ComPtr<IAccessible> root) : root_(root) {
    child_id_.intVal = CHILDID_SELF;
    child_id_.vt = VT_I4;
  };
  ~IA2Node(){};

  static IA2Node CreateRootForName(const std::string& name, const int pid = 0);
  static IA2Node CreateRootForPID(const int pid);

  bool IsNull();

  std::string get_accRole();
  std::string get_accName();

  std::string ia2_role();

  long IA2Node::get_accChildCount();
  IA2Node IA2Node::AccessibleChildAt(int index);

 private:
  Microsoft::WRL::ComPtr<IAccessible> root_;
  // This variant is used to recieve IAccessible
  // information about either the accessible object itself,
  // or its partial child.
  // TODO: Create own type for partial children. #95
  VARIANT child_id_;
};

#endif  // LIB_IA2_IA2_NODE_H_
