#ifndef LIB_ATSPI_ATSPI_TABLE_CELL_H_
#define LIB_ATSPI_ATSPI_TABLE_CELL_H_

#include <string>

#include <atspi/atspi.h>

class AtspiTableCellInterface {
  AtspiTableCell* interface_;

 public:
  AtspiTableCellInterface(AtspiTableCell* interface) : interface_(interface){};
  AtspiTableCellInterface() : interface_(nullptr){};
  ~AtspiTableCellInterface(){};

  bool isNull() const { return !interface_; }
  std::string toString() const;
  std::pair<int, int> getPosition() const;
  int getColumnIndex() const;
  int getColumnSpan() const;
  int getRowIndex() const;
  int getRowSpan() const;
};

#endif  // LIB_ATSPI_ATSPI_TABLE_CELL_H_
