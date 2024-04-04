#ifndef LIB_MAC_AXAPI_NODE_H_
#define LIB_MAC_AXAPI_NODE_H_

#include <ApplicationServices/ApplicationServices.h>

#include <memory>
#include <string>
#include <vector>

/** @defgroup axapi AX API (MacOS)
 *  Accessiblity API for MacOS
 *  @{
 */
/** @} */  // end of axapi group

namespace acacia {

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
 * Represents a node in the macOS (AX API) accessibility tree.
 *
 * Each valid AXAPINode wraps a single
 * [AXUIElementRef](https://developer.apple.com/documentation/applicationservices/axuielementref?language=objc).
 * @ingroup axapi
 */
class AXAPINode {
 public:
  /**
   * Constructs a null AXAPINode.
   *
   * Note: This is required for SWIG bindings to compile, but creates a node
   * which doesn't wrap an AXUIElementRef, and will cause a crash when any of
   * the accessor methods which depend on a valid AXUIElementRef are called.
   */
  AXAPINode();

  AXAPINode(const AXAPINode& other);
  ~AXAPINode();

  AXAPINode& operator=(AXAPINode other);

  /**
   * Checks whether this AXAPINode wraps a valid AXUIElementRef.
   *
   * @return true if this AXAPINode doesn't have a valid AXUIElementRef.
   */
  bool isNull() const;

  /**
   * Wraps
   * [`AXUIElementCopyAttributeNames()`](https://developer.apple.com/documentation/applicationservices/1459475-axuielementcopyattributenames?language=objc).
   *
   * @return The list of attributes supported by this accessibility object. Note
   * that it's not always the case that an attribute being supported indicates
   * that the attribute is present.
   */
  std::vector<std::string> getAttributeNames() const;

  /**
   * Checks whether the given attribute is present on this accessibility object.
   *
   * @return true if the attribute is present.
   */
  bool hasAttribute(const std::string& attribute) const;

  /**
   * Deduces the type of the given attribute's value on this accessibility
   * object. This can be used to call the correct getter.
   *
   * Note: Some attributes, such as `"AXValue"`, have values of different types
   * depending on the role of the accessibility object.
   *
   * @return
   * - ValueType::NOT_PRESENT if the attribute is unsupported or not present on
   * this object;
   * - ValueType::UNKNOWN if the type was not one of the known types;
   * - otherwise, the ValueType corresponding to the type of the attribute's
   * value.
   */
  ValueType getValueType(const std::string& attribute) const;

  /**
   * For attributes whose value is a ValueType::LIST, deduces the type of the
   * list elements.
   *
   * @return
   * - ValueType::NOT_PRESENT if the attribute is unsupported or not present on
   * this object;
   * - ValueType::UNKNOWN if the list has no elements, or the type of the
   * elements couldn't be determined;
   * - otherwise, the ValueType corresponding to the type of the attribute's
   * value's list elements.
   */
  ValueType getListElementType(const std::string& attribute) const;

  /**
   * Wraps
   * [AXUIElementGetAttributeValueCount](https://developer.apple.com/documentation/applicationservices/1459066-axuielementgetattributevaluecoun?language=objc).
   *
   * For attributes whose value is a ValueType::LIST, gets the number of
   * list elements.
   */
  int getListElementCount(const std::string& attribute) const;

  /**
   * Wraps
   * [AXUIElementCopyAttributeValue](https://developer.apple.com/documentation/applicationservices/1462085-axuielementcopyattributevalue?language=objc).
   *
   * Gets the value for an attribute whose value is a ValueType::BOOLEAN.
   */
  bool getBooleanValue(const std::string& attribute) const;

  /**
   * Wraps
   * [AXUIElementCopyAttributeValue](https://developer.apple.com/documentation/applicationservices/1462085-axuielementcopyattributevalue?language=objc).
   *
   * Gets the value for an attribute whose value is a ValueType::INT.
   */
  int getIntValue(const std::string& attribute) const;

  /**
   * Wraps
   * [AXUIElementCopyAttributeValue](https://developer.apple.com/documentation/applicationservices/1462085-axuielementcopyattributevalue?language=objc).
   *
   * Gets the value for an attribute whose value is a ValueType::FLOAT.
   */
  float getFloatValue(const std::string& attribute) const;

  /**
   * Wraps
   * [AXUIElementCopyAttributeValue](https://developer.apple.com/documentation/applicationservices/1462085-axuielementcopyattributevalue?language=objc).
   *
   * Gets the value for an attribute whose value is a ValueType::STRING.
   */
  std::string getStringValue(const std::string& attribute) const;

  /**
   * Wraps
   * [AXUIElementCopyAttributeValue](https://developer.apple.com/documentation/applicationservices/1462085-axuielementcopyattributevalue?language=objc).
   *
   * Gets the value for an attribute whose value is a ValueType::URL.
   */
  std::string getURLValue(const std::string& attribute) const;

  /**
   * Wraps
   * [AXUIElementCopyAttributeValue](https://developer.apple.com/documentation/applicationservices/1462085-axuielementcopyattributevalue?language=objc).
   *
   * Gets the value for an attribute whose value is a ValueType::NODE.
   */
  AXAPINode getNodeValue(const std::string& attribute) const;

  /**
   * Wraps
   * [AXUIElementCopyAttributeValue](https://developer.apple.com/documentation/applicationservices/1462085-axuielementcopyattributevalue?language=objc).
   *
   * Gets the value for an attribute whose value is a ValueType::POINT.
   */
  Point getPointValue(const std::string& attribute) const;

  /**
   * Wraps
   * [AXUIElementCopyAttributeValue](https://developer.apple.com/documentation/applicationservices/1462085-axuielementcopyattributevalue?language=objc).
   *
   * Gets the value for an attribute whose value is a ValueType::SIZE.
   */
  Size getSizeValue(const std::string& attribute) const;

  /**
   * Wraps
   * [AXUIElementCopyAttributeValue](https://developer.apple.com/documentation/applicationservices/1462085-axuielementcopyattributevalue?language=objc).
   *
   * Gets the value for an attribute whose value is a ValueType::RECT.
   */
  Rect getRectValue(const std::string& attribute) const;

  /**
   * Wraps
   * [AXUIElementCopyAttributeValue](https://developer.apple.com/documentation/applicationservices/1462085-axuielementcopyattributevalue?language=objc).
   *
   * Gets the value for an attribute whose value is a ValueType::RANGE.
   */
  Range getRangeValue(const std::string& attribute) const;

  /**
   * Wraps
   * [AXUIElementCopyAttributeValues](https://developer.apple.com/documentation/applicationservices/1462060-axuielementcopyattributevalues?language=objc).
   *
   * Gets the values for an attribute whose value is a ValueType::LIST whose
   * elements are ValueType::NODE values.
   */
  std::vector<AXAPINode> getNodeListValue(const std::string& attribute) const;

  /**
   * Wraps
   * [AXUIElementCopyAttributeValues](https://developer.apple.com/documentation/applicationservices/1462060-axuielementcopyattributevalues?language=objc).
   *
   * Gets the individual value at the given index for an attribute whose value
   * is a ValueType::LIST whose elements are ValueType::NODE values.
   */
  AXAPINode getNodeListValueAtIndex(const std::string& attribute,
                                    int index) const;

  /**
   * Wraps
   * [AXUIElementCopyAttributeValues](https://developer.apple.com/documentation/applicationservices/1462060-axuielementcopyattributevalues?language=objc).
   *
   * Gets the values for an attribute whose value is a ValueType::LIST whose
   * elements are ValueType::STRING values.
   */
  std::vector<std::string> getStringListValue(std::string& attribute) const;

  /**
   * Wraps
   * [AXUIElementCopyAttributeValues](https://developer.apple.com/documentation/applicationservices/1462060-axuielementcopyattributevalues?language=objc).
   *
   * Gets the individual value at the given index for an attribute whose value
   * is a ValueType::LIST whose elements are ValueType::STRING values.
   */
  std::string getStringListValueAtIndex(std::string& attribute,
                                        int index) const;

  /**
   * Wraps
   * [AXUIElementCopyAttributeValue](https://developer.apple.com/documentation/applicationservices/1462085-axuielementcopyattributevalue?language=objc).
   *
   * Gets the values for an attribute whose value is a ValueType::LIST whose
   * elements are ValueType::RANGE values.
   */
  std::vector<Range> getRangeListValue(std::string& attribute) const;

  /**
   * Wraps
   * [AXUIElementCopyAttributeValues](https://developer.apple.com/documentation/applicationservices/1462060-axuielementcopyattributevalues?language=objc).
   *
   * Gets the individual value at the given index for an attribute whose value
   * is a ValueType::LIST whose elements are ValueType::RANGE values.
   */
  Range getRangeListValueAtIndex(std::string& attribute, int index) const;

  /**
   * Wraps
   * [AXUIElementCopyAttributeValue](https://developer.apple.com/documentation/applicationservices/1462085-axuielementcopyattributevalue?language=objc).
   *
   * Gets the values for an attribute whose value is a ValueType::LIST whose
   * elements are ValueType::DICTIONARY values.
   */
  std::vector<Dictionary> getDictionaryListValue(std::string& attribute) const;

  /**
   * Wraps
   * [AXUIElementCopyAttributeValues](https://developer.apple.com/documentation/applicationservices/1462060-axuielementcopyattributevalues?language=objc).
   *
   * Gets the individual value at the given index for an attribute whose value
   * is a ValueType::LIST whose elements are ValueType::DICTIONARY values.
   */
  Dictionary getDictionaryListValueAtIndex(std::string& attribute,
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

}  // namespace acacia

#endif  // LIB_MAC_AXAPI_NODE_H_
