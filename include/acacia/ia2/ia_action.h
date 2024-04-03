#ifndef LIB_IA2_IA_ACTION_H_
#define LIB_IA2_IA_ACTION_H_

#include <string>

#include <wrl/client.h>

#include "acacia/export.h"
#include "third_party/ia2/include/ia2/ia2_api_all.h"

/**
 * This object wraps an
 * [IAccessibleAction](https://accessibility.linuxfoundation.org/a11yspecs/ia2/docs/html/interface_i_accessible_action.html)
 * pointer. It can be retrieved from an accessible object which implements this
 * interface using IANode::QueryAction().
 * @ingroup ia2
 */
class AXA_EXPORT IAAction {
 public:
  IAAction(Microsoft::WRL::ComPtr<IAccessibleAction> iface) : iface_(iface) {}
  ~IAAction(){};

  /**
   * Tests whether the underlying IAccessibleAction pointer is the null pointer.
   * @ingroup ia2
   */
  bool isNull() { return !iface_; }

  /**
   * Helper function to print commonly needed values associated with this
   * interface.
   * @ingroup ia2
   */
  std::string toString();

  /**
   * Wraps
   * [nActions](https://accessibility.linuxfoundation.org/a11yspecs/ia2/docs/html/interface_i_accessible_action.html#aa690059888d580119092caef859f4fea).
   * @ingroup ia2
   */
  long nActions();

  /**
   * Wraps
   * [getDescription](https://accessibility.linuxfoundation.org/a11yspecs/ia2/docs/html/interface_i_accessible_action.html#a7c8d49908df62d2ca14794b7ee2977d5).
   * @ingroup ia2
   *
   * @param index: Index of the action.
   */
  std::string getDescription(int index);

  /**
   * Wraps
   * [getName](https://accessibility.linuxfoundation.org/a11yspecs/ia2/docs/html/interface_i_accessible_action.html#a3be5d5fd7ce55e48de5a7c0cc856758f).
   * @ingroup ia2
   *
   * @param index: Index of the action.
   */
  std::string getName(int index);

 private:
  Microsoft::WRL::ComPtr<IAccessibleAction> iface_;
};

#endif  // LIB_IA2_IA_ACTION_H_
