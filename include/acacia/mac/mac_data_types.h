#ifndef LIB_MAC_AXAPI_DATA_TYPES_H_
#define LIB_MAC_AXAPI_DATA_TYPES_H_

#include <ostream>

#include <ApplicationServices/ApplicationServices.h>

namespace acacia {

class AXAPINode;
template <typename T>
class ScopedCFTypeRef;

/**
 * Represents the types that various polymorphic getters may return.
 * @ingroup axapi
 */
enum class ValueType {
  NOT_PRESENT, /** There is no value for the given parameter on this object. */
  UNKNOWN,     /** The value type couldn't be deduced. */
  LIST,        /** The value is a
                  [CFArrayRef](https://developer.apple.com/documentation/corefoundation/cfarray-s28).
                  Values of this type are converted to a std::vector. */
  BOOLEAN,     /** The value is a boolean. */
  INT,         /** The value is an int. */
  FLOAT,       /** The value is a float. */
  STRING,      /** The value is a
                  [CFStringRef](https://developer.apple.com/documentation/corefoundation/cfstring-rfh).
                  Values of this type are converted to std::string. */
  URL,         /** The value is a
                  [CFURLRef](https://developer.apple.com/documentation/corefoundation/cfurl-rd7).
                  Values of this type are converted to std::string. */
  NODE,        /** The value is an
                  [AXUIElementRef](https://developer.apple.com/documentation/applicationservices/axuielementref?language=objc).
                  Values of this type are converted to an AXAPINode. */
  POINT,       /** The value is a
                  [CGPoint](https://developer.apple.com/documentation/corefoundation/cgpoint).
                  Values of this type are converted to a Point. */
  SIZE,        /** The value is a
                  [CGSize](https://developer.apple.com/documentation/corefoundation/cgsize).
                  Values of this type are converted to a Size. */
  RECT,        /** The value is a
                  [CGRect](https://developer.apple.com/documentation/corefoundation/cgrect).
                  Values of this type are converted to a Rect. */
  RANGE,       /** The value is a
                  [CFRange](https://developer.apple.com/documentation/corefoundation/cfrange/).
                  Values of this type are converted to a Range. */
  DICTIONARY,  /** The value is a
                  [CFDictionary](https://developer.apple.com/documentation/corefoundation/cfdictionaryref/).
                  Values of this type are converted to a Dictionary. */
  DATA,        /** The value is a
                  [CFDataRef](https://developer.apple.com/documentation/corefoundation/cfdata/).
                */
  TEXTMARKER,  /** The value is an
                  [AXTextMarker](https://developer.apple.com/documentation/applicationservices/axtextmarker/).
                */
  TEXTMARKERRANGE, /** The value is an
                      [AXTextMarkerRange](https://developer.apple.com/documentation/applicationservices/axtextmarkerrange).
                    */

};

std::string ValueTypeToString(ValueType value_type);

class Point {
 public:
  Point() {}
  Point(const Point&) = default;
  Point& operator=(const Point&) = default;
  Point& operator=(Point&) = default;

  float x() { return x_; }
  float y() { return y_; }

  std::string ToString();

 private:
  Point(float x, float y) : x_(x), y_(y) {}

  float x_;
  float y_;

  friend class AXAPINode;
  friend class Rect;
};

class Size {
 public:
  Size() {}
  Size(const Size&) = default;
  Size& operator=(const Size&) = default;
  Size& operator=(Size&) = default;

  float width() { return width_; }
  float height() { return height_; }

  std::string ToString();

 private:
  Size(float width, float height) : width_(width), height_(height) {}

  float width_;
  float height_;

  friend class AXAPINode;
  friend class Rect;
};

class Rect {
 public:
  Rect() {}
  Rect(const Rect&) = default;
  Rect& operator=(const Rect&) = default;
  Rect& operator=(Rect&) = default;

  Point& origin() { return origin_; }
  Size& size() { return size_; }

  std::string ToString();

 private:
  Rect(Point origin, Size size) : origin_(origin), size_(size) {}
  Rect(float x, float y, float width, float height)
      : origin_(x, y), size_(width, height) {}

  Point origin_;
  Size size_;

  friend class AXAPINode;
};

class Range {
 public:
  Range() {}
  Range(const Range&) = default;
  Range& operator=(const Range&) = default;
  Range& operator=(Range&) = default;

  int length() { return length_; }
  int location() { return location_; }

  std::string ToString();

 private:
  Range(int length, int location) : length_(length), location_(location) {}
  int length_;
  int location_;

  friend class AXAPINode;
};

class Dictionary {
 public:
  Dictionary() {}
  Dictionary(const Dictionary&) = default;
  Dictionary& operator=(const Dictionary&) = default;
  Dictionary& operator=(Dictionary&) = default;

  ~Dictionary();

  std::vector<std::string> keys();
  ValueType getValueType(const std::string& key);

  std::string getStringValue(const std::string& key);
  AXAPINode getNodeValue(const std::string& node);

 private:
  explicit Dictionary(CFDictionaryRef cf_dictionary);
  explicit Dictionary(ScopedCFTypeRef<CFDictionaryRef> cf_dictionary);

  CFDictionaryRef cf_dictionary_{NULL};

  friend class AXAPINode;
};

}  // namespace acacia

#endif  // LIB_MAC_AXAPI_DATA_TYPES_H_
