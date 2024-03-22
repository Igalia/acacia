#ifndef LIB_ATSPI_ATSPI_COMPONENT_H_
#define LIB_ATSPI_ATSPI_COMPONENT_H_

#include <string>

#include <atspi/atspi.h>

class AtspiComponentInterface {
  AtspiComponent* interface_;

 public:
  AtspiComponentInterface(AtspiComponent* interface) : interface_(interface){};
  AtspiComponentInterface() : interface_(nullptr){};
  ~AtspiComponentInterface(){};

  bool isNull() const { return !interface_; }
  std::string toString() const;
  std::pair<int, int> getPosition() const;
  std::pair<int, int> getSize() const;
};

#endif  // LIB_ATSPI_ATSPI_COMPONENT_H_
