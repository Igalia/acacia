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

class AXAPINode;
class Dictionary;
class Point;
class Size;
class Rect;
class Range;

enum class ValueType;

AXAPINode findRootAXAPINodeForPID(int pid);

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

  bool isNull();

  std::vector<std::string> getAttributeNames() const;

  bool hasAttribute(const std::string& attribute) const;

  ValueType getValueType(const std::string& attribute) const;

  ValueType getListElementType(const std::string& attribute) const;

  int getListElementCount(const std::string& attribute) const;

  bool getBooleanValue(const std::string& attribute) const;

  int getIntValue(const std::string& attribute) const;

  float getFloatValue(const std::string& attribute) const;

  std::string getStringValue(const std::string& attribute) const;

  std::string getURLValue(const std::string& attribute) const;

  AXAPINode getNodeValue(const std::string& attribute) const;

  Point getPointValue(const std::string& attribute) const;

  Size getSizeValue(const std::string& attribute) const;

  Rect getRectValue(const std::string& attribute) const;

  Range getRangeValue(const std::string& attribute) const;

  std::vector<AXAPINode> getNodeListValue(const std::string& attribute) const;

  AXAPINode getNodeListValueAtIndex(const std::string& attribute,
                                    int index) const;

  std::vector<std::string> getStringListValue(std::string& attribute) const;

  std::string getStringListValueAtIndex(std::string& attribute,
                                        int index) const;

  std::vector<Range> getRangeListValue(std::string& attribute) const;

  Range getRangeListValueAtIndex(std::string& attribute, int index) const;

  std::vector<Dictionary> getDictionaryListValue(std::string& attribute) const;

  Dictionary getDictionaryListValueAtIndex(std::string& attribute,
                                           int index) const;

  friend AXAPINode findRootAXAPINodeForPID(int pid);

 private:
  explicit AXAPINode(AXUIElementRef ax_element);

  ScopedCFTypeRef<CFTypeRef> GetRawValue(const std::string& attribute,
                                         ValueType expected_type) const;
  ScopedCFTypeRef<CFArrayRef> GetRawArrayValue(
      const std::string& attribute) const;
  ScopedCFTypeRef<CFTypeRef> GetRawArrayValueAtIndex(
      const std::string& attribute,
      int index,
      ValueType expected_type) const;

  AXUIElementRef ax_ui_element_{NULL};

  friend class AXAPIContextImpl;
  friend class Dictionary;
};

}  // namespace mac_inspect

#endif  // LIB_MAC_AXAPI_NODE_H_
