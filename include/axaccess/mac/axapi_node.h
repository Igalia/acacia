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
AXAPINode findRootAXAPINodeForName(std::string name);

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

  bool isNull() const;

  std::vector<std::string> getAttributeNames() const;

  bool hasAttribute(const std::string& attribute) const;

  ValueType getValueType(const std::string& attribute) const;

  ValueType getListElementType(const std::string& attribute) const;

  int getListElementCount(const std::string& attribute) const;

  bool getBooleanAttribute(const std::string& attribute) const;

  int getIntAttribute(const std::string& attribute) const;

  float getFloatAttribute(const std::string& attribute) const;

  std::string getStringAttribute(const std::string& attribute) const;

  std::string getURLAttribute(const std::string& attribute) const;

  AXAPINode getNodeAttribute(const std::string& attribute) const;

  Point getPointAttribute(const std::string& attribute) const;

  Size getSizeAttribute(const std::string& attribute) const;

  Rect getRectAttribute(const std::string& attribute) const;

  Range getRangeAttribute(const std::string& attribute) const;

  std::vector<AXAPINode> getNodeListAttribute(
      const std::string& attribute) const;

  AXAPINode getNodeListAttribute(const std::string& attribute, int index) const;

  std::vector<std::string> getStringListAttribute(std::string& attribute) const;

  std::string getStringListAttribute(std::string& attribute, int index) const;

  std::vector<Range> getRangeListAttribute(std::string& attribute) const;

  Range getRangeListAttribute(std::string& attribute, int index) const;

  std::vector<Dictionary> getDictionaryListAttribute(
      std::string& attribute) const;

  Dictionary getDictionaryListAttribute(std::string& attribute,
                                        int index) const;

  friend AXAPINode findRootAXAPINodeForPID(int pid);
  friend AXAPINode findRootAXAPINodeForName(std::string name);

 private:
  explicit AXAPINode(AXUIElementRef ax_element);
  explicit AXAPINode(ScopedCFTypeRef<AXUIElementRef> ax_element);

  template <typename T>
  ScopedCFTypeRef<T> GetRawValue(const std::string& attribute,
                                 ValueType expected_type) const;

  ScopedCFTypeRef<CFArrayRef> GetRawArrayValue(
      const std::string& attribute) const;

  template <typename T>
  ScopedCFTypeRef<T> GetRawArrayValueAtIndex(const std::string& attribute,
                                             int index,
                                             ValueType expected_type) const;

  AXUIElementRef ax_ui_element_{NULL};

  friend class AXAPIContextImpl;
  friend class Dictionary;
};

}  // namespace mac_inspect

#endif  // LIB_MAC_AXAPI_NODE_H_
