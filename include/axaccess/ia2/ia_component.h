#ifndef LIB_IA2_IA_COMPONENT_H_
#define LIB_IA2_IA_COMPONENT_H_

#include <string>

#include <wrl/client.h>

#include "axaccess/export.h"
#include "third_party/ia2/include/ia2/ia2_api_all.h"

/**
 * This object wraps an
 * [IAccessible2Component](https://accessibility.linuxfoundation.org/a11yspecs/ia2/docs/html/interface_i_accessible_component.html)
 * pointer. It can be retrieved from an accessible object which implements this
 * interface using IANode::QueryComponent().
 * @ingroup ia2
 */
class AXA_EXPORT IAComponent {
 public:
  IAComponent(Microsoft::WRL::ComPtr<IAccessibleComponent> iface)
      : iface_(iface) {}
  ~IAComponent(){};

  /**
   * Tests whether the underlying IAccessibleComponent pointer is the null
   * pointer.
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
   * [getBackground](https://accessibility.linuxfoundation.org/a11yspecs/ia2/docs/html/interface_i_accessible_component.html#a218cb4f2806cc095cb10802531761878).
   * @ingroup ia2
   */
  std::string getBackground();

  /**
   * Wraps
   * [getForeground](https://accessibility.linuxfoundation.org/a11yspecs/ia2/docs/html/interface_i_accessible_component.html#ab610ac1ef9306b0d2123dc11850157ad).
   * @ingroup ia2
   */
  std::string getForeground();

  /**
   * Wraps
   * [getLocationInParent](https://accessibility.linuxfoundation.org/a11yspecs/ia2/docs/html/interface_i_accessible_component.html#a8709fdbf3f51ae079af274854a8bffd4).
   * @ingroup ia2
   *
   * @returns A tuple in the form (x,y).
   */
  std::pair<long, long> getLocationInParent();

 private:
  Microsoft::WRL::ComPtr<IAccessibleComponent> iface_;
};

#endif  // LIB_IA2_IA_COMPONENT_H_
