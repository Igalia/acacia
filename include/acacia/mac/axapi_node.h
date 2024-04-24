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

/**
 * Returns the root node of the tree of a running application with the given
 * PID.
 *
 * @ingroup axapi
 *
 * @return An AXAPINode representing the root accessibility object for the
 * application with the given PID, or a null AXAPINode if no such application
 * exists.
 */
AXAPINode findRootAXAPINodeForPID(int pid);

/**
 * Returns the root node of the tree of a running application with the given
 * name.
 *
 * @ingroup axapi
 *
 * @return An AXAPINode representing the root accessibility object for an
 * application whose name matches the given name, or a null AXAPINode if no such
 * application exists.
 */
AXAPINode findRootAXAPINodeForName(const std::string& name);

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
   * @ingroup axapi
   */
  AXAPINode();

  AXAPINode(const AXAPINode& other);
  ~AXAPINode();

  AXAPINode& operator=(AXAPINode other);

  /**
   * Checks whether this AXAPINode wraps a valid AXUIElementRef.
   * @ingroup axapi
   *
   * @return true if this AXAPINode doesn't have a valid AXUIElementRef.
   */
  bool isNull() const;

  /**
   * Wraps
   * [`AXUIElementCopyAttributeNames()`](https://developer.apple.com/documentation/applicationservices/1459475-axuielementcopyattributenames?language=objc).
   * @ingroup axapi
   *
   * @return The list of attributes supported by this accessibility object. Note
   * that it's not always the case that an attribute being supported indicates
   * that the attribute is present.
   */
  std::vector<std::string> getAttributeNames() const;

  /**
   * Checks whether the given attribute is present on this accessibility object.
   * @ingroup axapi
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
   * @ingroup axapi
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
   * @ingroup axapi
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
   * @ingroup axapi
   */
  int getListElementCount(const std::string& attribute) const;

  /**
   * Wraps
   * [AXUIElementCopyAttributeValue](https://developer.apple.com/documentation/applicationservices/1462085-axuielementcopyattributevalue?language=objc).
   *
   * Gets the value for an attribute whose value is a ValueType::BOOLEAN.
   * @ingroup axapi
   */
  bool getBooleanValue(const std::string& attribute) const;

  /**
   * Wraps
   * [AXUIElementCopyAttributeValue](https://developer.apple.com/documentation/applicationservices/1462085-axuielementcopyattributevalue?language=objc).
   *
   * Gets the value for an attribute whose value is a ValueType::INT.
   * @ingroup axapi
   */
  int getIntValue(const std::string& attribute) const;

  /**
   * Wraps
   * [AXUIElementCopyAttributeValue](https://developer.apple.com/documentation/applicationservices/1462085-axuielementcopyattributevalue?language=objc).
   *
   * Gets the value for an attribute whose value is a ValueType::FLOAT.
   * @ingroup axapi
   */
  float getFloatValue(const std::string& attribute) const;

  /**
   * Wraps
   * [AXUIElementCopyAttributeValue](https://developer.apple.com/documentation/applicationservices/1462085-axuielementcopyattributevalue?language=objc).
   *
   * Gets the value for an attribute whose value is a ValueType::STRING.
   * @ingroup axapi
   */
  std::string getStringValue(const std::string& attribute) const;

  /**
   * Wraps
   * [AXUIElementCopyAttributeValue](https://developer.apple.com/documentation/applicationservices/1462085-axuielementcopyattributevalue?language=objc).
   *
   * Gets the value for an attribute whose value is a ValueType::URL.
   * @ingroup axapi
   */
  std::string getURLValue(const std::string& attribute) const;

  /**
   * Wraps
   * [AXUIElementCopyAttributeValue](https://developer.apple.com/documentation/applicationservices/1462085-axuielementcopyattributevalue?language=objc).
   *
   * Gets the value for an attribute whose value is a ValueType::NODE.
   * @ingroup axapi
   */
  AXAPINode getNodeValue(const std::string& attribute) const;

  /**
   * Wraps
   * [AXUIElementCopyAttributeValue](https://developer.apple.com/documentation/applicationservices/1462085-axuielementcopyattributevalue?language=objc).
   *
   * Gets the value for an attribute whose value is a ValueType::POINT.
   * @ingroup axapi
   */
  Point getPointValue(const std::string& attribute) const;

  /**
   * Wraps
   * [AXUIElementCopyAttributeValue](https://developer.apple.com/documentation/applicationservices/1462085-axuielementcopyattributevalue?language=objc).
   *
   * Gets the value for an attribute whose value is a ValueType::SIZE.
   * @ingroup axapi
   */
  Size getSizeValue(const std::string& attribute) const;

  /**
   * Wraps
   * [AXUIElementCopyAttributeValue](https://developer.apple.com/documentation/applicationservices/1462085-axuielementcopyattributevalue?language=objc).
   *
   * Gets the value for an attribute whose value is a ValueType::RECT.
   * @ingroup axapi
   */
  Rect getRectValue(const std::string& attribute) const;

  /**
   * Wraps
   * [AXUIElementCopyAttributeValue](https://developer.apple.com/documentation/applicationservices/1462085-axuielementcopyattributevalue?language=objc).
   *
   * Gets the value for an attribute whose value is a ValueType::RANGE.
   * @ingroup axapi
   */
  Range getRangeValue(const std::string& attribute) const;

  /**
   * Wraps
   * [AXUIElementCopyAttributeValues](https://developer.apple.com/documentation/applicationservices/1462060-axuielementcopyattributevalues?language=objc).
   *
   * Gets the values for an attribute whose value is a ValueType::LIST whose
   * elements are ValueType::NODE values.
   * @ingroup axapi
   */
  std::vector<AXAPINode> getNodeListValue(const std::string& attribute) const;

  /**
   * Wraps
   * [AXUIElementCopyAttributeValues](https://developer.apple.com/documentation/applicationservices/1462060-axuielementcopyattributevalues?language=objc).
   *
   * Gets the individual value at the given index for an attribute whose value
   * is a ValueType::LIST whose elements are ValueType::NODE values.
   * @ingroup axapi
   */
  AXAPINode getNodeListValueAtIndex(const std::string& attribute,
                                    int index) const;

  /**
   * Wraps
   * [AXUIElementCopyAttributeValues](https://developer.apple.com/documentation/applicationservices/1462060-axuielementcopyattributevalues?language=objc).
   *
   * Gets the values for an attribute whose value is a ValueType::LIST whose
   * elements are ValueType::STRING values.
   * @ingroup axapi
   */
  std::vector<std::string> getStringListValue(
      const std::string& attribute) const;

  /**
   * Wraps
   * [AXUIElementCopyAttributeValues](https://developer.apple.com/documentation/applicationservices/1462060-axuielementcopyattributevalues?language=objc).
   *
   * Gets the individual value at the given index for an attribute whose value
   * is a ValueType::LIST whose elements are ValueType::STRING values.
   * @ingroup axapi
   */
  std::string getStringListValueAtIndex(const std::string& attribute,
                                        int index) const;

  /**
   * Wraps
   * [AXUIElementCopyAttributeValue](https://developer.apple.com/documentation/applicationservices/1462085-axuielementcopyattributevalue?language=objc).
   *
   * Gets the values for an attribute whose value is a ValueType::LIST whose
   * elements are ValueType::RANGE values.
   * @ingroup axapi
   */
  std::vector<Range> getRangeListValue(const std::string& attribute) const;

  /**
   * Wraps
   * [AXUIElementCopyAttributeValues](https://developer.apple.com/documentation/applicationservices/1462060-axuielementcopyattributevalues?language=objc).
   *
   * Gets the individual value at the given index for an attribute whose value
   * is a ValueType::LIST whose elements are ValueType::RANGE values.
   * @ingroup axapi
   */
  Range getRangeListValueAtIndex(const std::string& attribute, int index) const;

  /**
   * Wraps
   * [AXUIElementCopyAttributeValue](https://developer.apple.com/documentation/applicationservices/1462085-axuielementcopyattributevalue?language=objc).
   *
   * Gets the values for an attribute whose value is a ValueType::LIST whose
   * elements are ValueType::DICTIONARY values.
   * @ingroup axapi
   */
  std::vector<Dictionary> getDictionaryListValue(
      const std::string& attribute) const;

  /**
   * Wraps
   * [AXUIElementCopyAttributeValues](https://developer.apple.com/documentation/applicationservices/1462060-axuielementcopyattributevalues?language=objc).
   *
   * Gets the individual value at the given index for an attribute whose value
   * is a ValueType::LIST whose elements are ValueType::DICTIONARY values.
   * @ingroup axapi
   */
  Dictionary getDictionaryListValueAtIndex(const std::string& attribute,
                                           int index) const;

  friend AXAPINode findRootAXAPINodeForPID(int pid);
  friend AXAPINode findRootAXAPINodeForName(const std::string& name);

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
