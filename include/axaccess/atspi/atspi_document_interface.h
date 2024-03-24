#ifndef LIB_ATSPI_ATSPI_DOCUMENT_H_
#define LIB_ATSPI_ATSPI_DOCUMENT_H_

#include <string>
#include <vector>

#include <atspi/atspi.h>

class AtspiDocumentInterface {
  AtspiDocument* interface_;

 public:
  AtspiDocumentInterface(AtspiDocument* interface) : interface_(interface){};
  AtspiDocumentInterface() : interface_(nullptr){};
  ~AtspiDocumentInterface(){};

  bool isNull() const { return !interface_; }
  std::string toString() const;
  std::string getLocale() const;
  std::vector<std::string> getDocumentAttributes() const;
};

#endif  // LIB_ATSPI_ATSPI_DOCUMENT_H_
