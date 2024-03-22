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

template <typename T>
class ScopedCFTypeRef;

class Point;
class Size;
class Rect;
class Range;

enum class ValueType {
  NOT_PRESENT,
  UNKNOWN,
  LIST,
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
  DICTIONARY,
  DATA,
  TEXTMARKER,
  TEXTMARKERRANGE,
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

  int GetListAttributeValueCount(const std::string& attribute) const;

  bool CopyBooleanAttributeValue(const std::string& attribute) const;

  int CopyIntAttributeValue(const std::string& attribute) const;

  float CopyFloatAttributeValue(const std::string& attribute) const;

  std::string CopyStringAttributeValue(const std::string& attribute) const;

  std::string CopyURLAttributeValue(const std::string& attribute) const;

  AXAPINode CopyNodeAttributeValue(const std::string& attribute) const;

  Point CopyPointAttributeValue(const std::string& attribute) const;

  Size CopySizeAttributeValue(const std::string& attribute) const;

  Rect CopyRectAttributeValue(const std::string& attribute) const;

  Range CopyRangeAttributeValue(const std::string& attribute) const;

  std::vector<AXAPINode> CopyNodeListAttributeValue(
      const std::string& attribute) const;

  AXAPINode CopyNodeListAttributeValueAtIndex(const std::string& attribute,
                                              int index) const;

  std::vector<std::string> CopyStringListAttributeValue(
      std::string& attribute) const;

  std::string CopyStringListAttributeValueAtIndex(std::string& attribute,
                                                  int index) const;

 private:
  explicit AXAPINode(AXUIElementRef ax_element);

  ScopedCFTypeRef<CFTypeRef> CopyRawAttributeValue(
      const std::string& attribute,
      ValueType expected_type) const;
  ScopedCFTypeRef<CFArrayRef> CopyRawArrayAttributeValue(
      const std::string& attribute) const;
  ScopedCFTypeRef<CFTypeRef> CopyRawArrayAttributeValueAtIndex(
      const std::string& attribute,
      int index,
      ValueType expected_type) const;

  AXUIElementRef ax_ui_element_{NULL};

  friend class AXAPIContextImpl;
};

}  // namespace mac_inspect

#endif  // LIB_MAC_AXAPI_NODE_H_
