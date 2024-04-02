#ifndef LIB_IA2_IA_2_H_
#define LIB_IA2_IA_2_H_

#include <string>
#include <vector>

#include <wrl/client.h>

#include "axaccess/export.h"
#include "third_party/ia2/include/ia2/ia2_api_all.h"

/**
 * This object represents the information returned by @ref getGroupPosition.
 * @ingroup ia2
 */
struct GroupPosition {
  long level;
  long setsize;
  long position;

  GroupPosition(){};
  GroupPosition(long level, long setsize, long position)
      : level(level), setsize(setsize), position(position) {}

  bool IsEmpty() { return level == 0 && setsize == 0 && position == 0; }
};

/**
 * This object wraps an
 * [Iaccessible2
 * Interface](https://accessibility.linuxfoundation.org/a11yspecs/ia2/docs/html/interface_i_accessible2.html)
 * pointer. It can be retrieved from an accessible object which implements this
 * interface using IANode::QueryIA2().
 * @ingroup ia2
 */
class AXA_EXPORT IA2 {
 public:
  IA2(Microsoft::WRL::ComPtr<IAccessible2> iface) : iface_(iface) {}
  ~IA2(){};

  /**
   * Test whether the underlaying IAccessible2 pointer is the null pointer.
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
   * [attributes](https://accessibility.linuxfoundation.org/a11yspecs/ia2/docs/html/interface_i_accessible2.html#a0d51b0c189a000ee3b6ddf7f68da2009).
   * @ingroup ia2
   */
  std::string getAttributes();

  /**
   * Wraps
   * [groupPosition](https://accessibility.linuxfoundation.org/a11yspecs/ia2/docs/html/interface_i_accessible2.html#a94d4d84e000ef2fa3f2abf1148779941).
   * @ingroup ia2
   *
   * @returns A @ref GroupPosition object with `level`, `setsize` and `position`
   * members.
   */
  GroupPosition getGroupPosition();

  /**
   * A helper function which returns a list of relations.
   * @ingroup ia2
   *
   * @returns A list of strings with all relations.
   */
  std::vector<std::string> getRelations();

  /**
   * Wraps
   * [role](https://accessibility.linuxfoundation.org/a11yspecs/ia2/docs/html/interface_i_accessible2.html#a9395d15b0397139ac33800e0878d1788).
   * @ingroup ia2
   */
  std::string role();

  /**
   * Wraps
   * [role](https://accessibility.linuxfoundation.org/a11yspecs/ia2/docs/html/interface_i_accessible2.html#a801f0db3054d4dd8b71882e8cbe84541).
   * @ingroup ia2
   */
  long getStates();

  /**
   * Helper function to convert the state bit vector to strings indicating the
   * [state bit
   * constants](https://accessibility.linuxfoundation.org/a11yspecs/ia2/docs/html/_accessible_states_8idl.html).
   * @ingroup ia2
   */
  std::vector<std::string> getStateStrings();

 private:
  Microsoft::WRL::ComPtr<IAccessible2> iface_;
};

#endif  // LIB_IA2_IA_2_H_
