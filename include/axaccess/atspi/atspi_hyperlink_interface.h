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
  AtspiHyperlinkInterface()
      : interface_(nullptr, [](AtspiHyperlink* iface) {}){};
  ~AtspiHyperlinkInterface(){};

  AtspiHyperlinkInterface(const AtspiHyperlinkInterface&) = delete;
  AtspiHyperlinkInterface& operator=(const AtspiHyperlinkInterface&) = delete;

  AtspiHyperlinkInterface(AtspiHyperlinkInterface&&) = default;

  bool isNull() const { return !interface_; }
  std::string toString() const;
  int getStartIndex() const;
  int getEndIndex() const;
  std::string getURI(int index = 0) const;

 private:
  // We use a smart pointer here: `atspi_accessible_get_hyperlink` returns a
  // new hyperlink object rather than increasing the ref count and casting the
  // the AtspiAccessible as the interface. Keeping this as a raw pointer and
  // then unrefing it in the destructor works with C++ but results in a double-
  // free with both python and node.
  // TODO: Find a way to use a raw pointer by modifying something in SWIG.
  std::unique_ptr<AtspiHyperlink, void (*)(AtspiHyperlink*)> interface_;
};

#endif  // LIB_ATSPI_ATSPI_HYPERLINK_H_
