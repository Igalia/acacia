#ifndef LIB_ATSPI_ATSPI_ACTION_H_
#define LIB_ATSPI_ATSPI_ACTION_H_

#include <string>

#include <atspi/atspi.h>

class AtspiActionInterface {
  AtspiAction* interface_;

 public:
  AtspiActionInterface(AtspiAction* interface) : interface_(interface){};
  AtspiActionInterface() : interface_(nullptr){};
  ~AtspiActionInterface(){};

  bool isNull() const { return !interface_; }
  std::string toString() const;
  int getNActions() const;
  std::string getName(int index) const;
  std::string getDescription(int index) const;
};

#endif  // LIB_ATSPI_ATSPI_ACTION_H_
