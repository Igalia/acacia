#ifndef LIB_IA2_IA_TABLE2_H_
#define LIB_IA2_IA_TABLE2_H_

#include <string>

#include <wrl/client.h>

#include "axaccess/export.h"
#include "third_party/ia2/include/ia2/ia2_api_all.h"

/**
 * This object wraps an
 * [IaccessibleTable2](https://accessibility.linuxfoundation.org/a11yspecs/ia2/docs/html/interface_i_accessible_table2.html)
 * pointer. It can be retrieved from an accessible object which implements this
 * interface using IANode::QueryTable2().
 * @ingroup ia2
 */
class AXA_EXPORT IATable2 {
 public:
  IATable2(Microsoft::WRL::ComPtr<IAccessibleTable2> iface) : iface_(iface) {}
  ~IATable2(){};

  /**
   * Test whether the underlaying IAccessibleTable2 pointer is the null pointer.
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
   * [nColumns](https://accessibility.linuxfoundation.org/a11yspecs/ia2/docs/html/interface_i_accessible_table2.html#a1a0546c78d320a32e5c015eedcba8b95).
   * @ingroup ia2
   */
  long getNColumns();

  /**
   * Wraps
   * [nRows](https://accessibility.linuxfoundation.org/a11yspecs/ia2/docs/html/interface_i_accessible_table2.html#a322d0ee21f316f302bbdd70dbc206d8a).
   * @ingroup ia2
   */
  long getNRows();

 private:
  Microsoft::WRL::ComPtr<IAccessibleTable2> iface_;
};

#endif  // LIB_IA2_IA_TABLE2_H_
