#ifndef LIB_IA2_IA_TABLE2_H_
#define LIB_IA2_IA_TABLE2_H_

#include <string>

#include <wrl/client.h>

#include "acacia/export.h"
#include "third_party/ia2/include/ia2/ia2_api_all.h"

namespace acacia {

/**
 * This object wraps an
 * [IAccessibleTable2](https://accessibility.linuxfoundation.org/a11yspecs/ia2/docs/html/interface_i_accessible_table2.html)
 * pointer. It can be retrieved from an accessible object which implements this
 * interface using IANode::QueryTable2().
 * @ingroup ia2
 */
class ACACIA_EXPORT IATable2 {
 public:
  IATable2(Microsoft::WRL::ComPtr<IAccessibleTable2> iface) : iface_(iface) {}
  ~IATable2(){};

  /**
   * Tests whether the underlying IAccessibleTable2 pointer is the null pointer.
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

}  // namespace acacia

#endif  // LIB_IA2_IA_TABLE2_H_
