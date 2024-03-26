#ifndef LIB_ATSPI_ATSPI_TEXT_H_
#define LIB_ATSPI_ATSPI_TEXT_H_

#include <string>

#include <atspi/atspi.h>

class AtspiTextInterface {
  AtspiText* interface_;

 public:
  AtspiTextInterface(AtspiText* interface) : interface_(interface){};
  AtspiTextInterface() : interface_(nullptr){};
  ~AtspiTextInterface(){};

  bool isNull() const { return !interface_; }
  std::string toString() const;
  int getCaretOffset() const;
  int getCharacterCount() const;
  std::string getText(int start_offset, int end_offset) const;
};

#endif  // LIB_ATSPI_ATSPI_TEXT_H_
