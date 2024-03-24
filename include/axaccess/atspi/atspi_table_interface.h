#ifndef LIB_ATSPI_ATSPI_TABLE_H_
#define LIB_ATSPI_ATSPI_TABLE_H_

#include <string>

#include <atspi/atspi.h>

class AtspiTableInterface {
  AtspiTable* interface_;

 public:
  AtspiTableInterface(AtspiTable* interface) : interface_(interface){};
  AtspiTableInterface() : interface_(nullptr){};
  ~AtspiTableInterface(){};

  bool isNull() const { return !interface_; }
  std::string toString() const;
  int getNColumns() const;
  int getNRows() const;
};

#endif  // LIB_ATSPI_ATSPI_TABLE_H_
