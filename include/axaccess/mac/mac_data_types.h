#ifndef LIB_MAC_AXAPI_DATA_TYPES_H_
#define LIB_MAC_AXAPI_DATA_TYPES_H_

#include <ostream>

namespace mac_inspect {

class AXAPINode;

class Point {
 public:
  Point(Point& other) : x_(other.x_), y_(other.y_) {}

  float x() { return x_; }
  float y() { return y_; }

  std::string ToString() {
    return "(" + std::to_string(x_) + ", " + std::to_string(y_) + ")";
  }

 private:
  Point(float x, float y) : x_(x), y_(y) {}

  float x_;
  float y_;

  friend class AXAPINode;
  friend class Rect;
};

class Size {
 public:
  Size(Size& other) : width_(other.width_), height_(other.height_) {}

  float width() { return width_; }
  float height() { return height_; }

  std::string ToString() {
    return "[" + std::to_string(width_) + ", " + std::to_string(height_) + "]";
  }

 private:
  Size(float width, float height) : width_(width), height_(height) {}

  float width_;
  float height_;

  friend class AXAPINode;
  friend class Rect;
};

class Rect {
 public:
  Rect(Rect& other) : origin_(other.origin_), size_(other.size_) {}

  Point& origin() { return origin_; }
  Size& size() { return size_; }

  std::string ToString() { return origin_.ToString() + "/" + size_.ToString(); }

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
  Range(Range& other) : length_(other.length_), location_(other.location_) {}

  int length() { return length_; }
  int location() { return location_; }

  std::string ToString() {
    return "[" + std::to_string(length_) + ", " + std::to_string(location_) +
           "]";
  }

 private:
  Range(int length, int location) : length_(length), location_(location) {}
  int length_;
  int location_;

  friend class AXAPINode;
};

}  // namespace mac_inspect

#endif  // LIB_MAC_AXAPI_DATA_TYPES_H_
