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

  bool is_null() const { return !interface_; }
  std::string to_string() const;
  std::pair<int, int> get_position() const;
  std::pair<int, int> get_size() const;
};

#endif  // LIB_ATSPI_ATSPI_COMPONENT_H_
