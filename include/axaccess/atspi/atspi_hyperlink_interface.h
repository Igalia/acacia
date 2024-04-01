#ifndef LIB_ATSPI_ATSPI_HYPERLINK_H_
#define LIB_ATSPI_ATSPI_HYPERLINK_H_

#include <memory>
#include <string>

#include <atspi/atspi.h>

class AtspiHyperlinkInterface {
 public:
  AtspiHyperlinkInterface(AtspiHyperlink* interface)
      : interface_(interface,
                   [](AtspiHyperlink* iface) { g_object_unref(iface); }){};
  AtspiHyperlinkInterface() : interface_(nullptr){};
  ~AtspiHyperlinkInterface(){};

  bool isNull() const { return !interface_; }
  std::string toString() const;
  int getStartIndex() const;
  int getEndIndex() const;
  std::string getURI(int index = 0) const;

 private:
  std::shared_ptr<AtspiHyperlink> interface_;
};

#endif  // LIB_ATSPI_ATSPI_HYPERLINK_H_
