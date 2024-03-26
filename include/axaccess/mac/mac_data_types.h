#ifndef LIB_MAC_AXAPI_DATA_TYPES_H_
#define LIB_MAC_AXAPI_DATA_TYPES_H_

#include <ostream>

#include <ApplicationServices/ApplicationServices.h>

namespace mac_inspect {

class AXAPINode;

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
  Dictionary(const CFDictionaryRef cf_dictionary)
      : cf_dictionary_(cf_dictionary) {}

  CFDictionaryRef cf_dictionary_{NULL};

  friend class AXAPINode;
};

}  // namespace mac_inspect

#endif  // LIB_MAC_AXAPI_DATA_TYPES_H_
