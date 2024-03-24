#ifndef LIB_ATSPI_ATSPI_VALUE_H_
#define LIB_ATSPI_ATSPI_VALUE_H_

#include <string>

#include <atspi/atspi.h>

class AtspiValueInterface {
  AtspiValue* interface_;

 public:
  AtspiValueInterface(AtspiValue* interface) : interface_(interface){};
  AtspiValueInterface() : interface_(nullptr){};
  ~AtspiValueInterface(){};

  bool isNull() const { return !interface_; }
  std::string toString() const;
  double getCurrentValue() const;
  double getMaximumValue() const;
  double getMinimumValue() const;
};

#endif  // LIB_ATSPI_ATSPI_VALUE_H_
