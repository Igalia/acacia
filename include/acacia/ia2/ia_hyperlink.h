#ifndef LIB_IA2_IA_HYPERLINK_H_
#define LIB_IA2_IA_HYPERLINK_H_

#include <string>

#include <wrl/client.h>

#include "acacia/export.h"
#include "third_party/ia2/include/ia2/ia2_api_all.h"

namespace acacia {

/**
 * This object wraps an
 * [IAccessibleHyperlink](https://accessibility.linuxfoundation.org/a11yspecs/ia2/docs/html/interface_i_accessible_action.html)
 * pointer. It can be retrieved from an accessible object which implements this
 * interface using IANode::QueryHyperlink().
 * @ingroup ia2
 */
class ACACIA_EXPORT IAHyperlink {
 public:
  IAHyperlink(Microsoft::WRL::ComPtr<IAccessibleHyperlink> iface)
      : iface_(iface) {}
  ~IAHyperlink(){};

  /**
   * Tests whether the underlying IAccessibleHyperlink pointer is the null
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
   * [startIndex](https://accessibility.linuxfoundation.org/a11yspecs/ia2/docs/html/interface_i_accessible_hyperlink.html#a1348351c5a5ad3adcec1a2e86c40d533).
   * @ingroup ia2
   */
  long getStartIndex();

  /**
   * Wraps
   * [endIndex](https://accessibility.linuxfoundation.org/a11yspecs/ia2/docs/html/interface_i_accessible_hyperlink.html#a7008e8f6422e75212eacbff8554cec00).
   * @ingroup ia2
   */
  long getEndIndex();

  /**
   * Wraps
   * [anchorTarget](https://accessibility.linuxfoundation.org/a11yspecs/ia2/docs/html/interface_i_accessible_hyperlink.html#a88ee9258c44095ea1a179867d6c05e77).
   * @ingroup ia2
   *
   * @param index:
   */
  std::string getAnchorTarget(long index);

 private:
  Microsoft::WRL::ComPtr<IAccessibleHyperlink> iface_;
};

}  // namespace acacia

#endif  // LIB_IA2_IA_HYPERLINK_H_
