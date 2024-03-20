#ifndef LIB_MAC_AXAPI_NODE_H_
#define LIB_MAC_AXAPI_NODE_H_

#include <ApplicationServices/ApplicationServices.h>

#include <memory>
#include <string>
#include <vector>

/** @defgroup axapi AX-API (MacOS)
 *  Accessiblity API for MacOS
 *  @{
 */
/** @} */  // end of axapi group

namespace mac_inspect {

class AXAPIContextImpl;

enum class ValueType {
  NOT_PRESENT,
  UNKNOWN,
  BOOLEAN,
  INT,
  FLOAT,
  STRING,
  URL,
  NODE,
  POINT,
  SIZE,
  RECT,
  RANGE,
  LIST
};

std::string ValueTypeToString(ValueType value_type);

/**
 * Represents a node in the accessibility tree.
 * @ingroup axapi
 */
class AXAPINode {
 public:
  AXAPINode();
  AXAPINode(const AXAPINode& other);
  ~AXAPINode();

  AXAPINode& operator=(AXAPINode other);

  static AXAPINode CreateForPID(int pid);

  bool IsNull();

  std::vector<std::string> CopyAttributeNames() const;

  bool HasAttribute(const std::string& attribute) const;

  ValueType GetAttributeValueType(const std::string& attribute) const;

  ValueType GetListAttributeElementType(const std::string& attribute) const;

  std::string CopyStringAttributeValue(const std::string& attribute) const;

  int GetListAttributeValueCount(const std::string& attribute) const;

  std::vector<AXAPINode> CopyNodeListAttributeValue(
      const std::string& attribute) const;

  AXAPINode CopyNodeListAttributeValueAtIndex(const std::string& attribute,
                                              int index) const;

 private:
  explicit AXAPINode(AXUIElementRef ax_element);
  AXUIElementRef ax_ui_element_{NULL};

  bool HasAttribute(const CFStringRef attribute) const;

  friend class AXAPIContextImpl;
};

}  // namespace mac_inspect

#endif  // LIB_MAC_AXAPI_NODE_H_
