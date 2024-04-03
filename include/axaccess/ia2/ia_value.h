#ifndef LIB_IA2_IA_VALUE_H_
#define LIB_IA2_IA_VALUE_H_

#include <string>

#include <wrl/client.h>

#include "axaccess/export.h"
#include "third_party/ia2/include/ia2/ia2_api_all.h"

/**
 * This object wraps an
 * [IAccessibleValue](https://accessibility.linuxfoundation.org/a11yspecs/ia2/docs/html/interface_i_accessible_value.html)
 * pointer. It can be retrieved from an accessible object which implements this
 * interface using IANode::QueryValue().
 * @ingroup ia2
 */
class AXA_EXPORT IAValue {
 public:
  IAValue(Microsoft::WRL::ComPtr<IAccessibleValue> iface) : iface_(iface) {}
  ~IAValue(){};

  /**
   * Tests whether the underlying IAccessibleValue pointer is the null pointer.
   * @ingroup ia2
   */
  bool isNull() { return !iface_; }

  /**
   * Helper function.
   * @ingroup ia2
   */
  std::string toString();

  /**
   * Wraps
   * [currentValue](https://accessibility.linuxfoundation.org/a11yspecs/ia2/docs/html/interface_i_accessible_value.html#aec9c245ee3c5991d908769bb7cb46508).
   * @ingroup ia2
   */
  std::string getCurrentValue();

  /**
   * Wraps
   * [maximumValue](https://accessibility.linuxfoundation.org/a11yspecs/ia2/docs/html/interface_i_accessible_value.html#a55e179b8a504a0c44049f6d4edd0bc79).
   * @ingroup ia2
   */
  std::string getMaximumValue();

  /**
   * Wraps
   * [minimumValue](https://accessibility.linuxfoundation.org/a11yspecs/ia2/docs/html/interface_i_accessible_value.html#a2ddcf92e3d586400ecb85b4204630b19).
   * @ingroup ia2
   */

  std::string getMinimumValue();

 private:
  Microsoft::WRL::ComPtr<IAccessibleValue> iface_;
};

#endif  // LIB_IA2_IA_VALUE_H_
