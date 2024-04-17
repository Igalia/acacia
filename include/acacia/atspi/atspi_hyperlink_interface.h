#ifndef LIB_ATSPI_ATSPI_HYPERLINK_H_
#define LIB_ATSPI_ATSPI_HYPERLINK_H_

#include <memory>
#include <string>

#include <atspi/atspi.h>

namespace acacia {

/**
 * This object wraps an
 * [AtspiHyperlink](https://docs.gtk.org/atspi2/iface.Hyperlink.html) pointer.
 * It can be retrieved from an accessible object which implements this interface
 * using AtspiNode::queryHyperlink().
 * @ingroup atspi
 */
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

  /**
   * Tests whether the underlying AtspiHyperlink pointer is the null pointer.
   * @ingroup atspi
   */
  bool isNull() const { return !interface_; }

  /**
   * Helper function to print commonly needed values associated with this
   * interface.
   * @ingroup atspi
   */
  std::string toString() const;

  /**
   * Wraps
   * [atspi_hyperlink_get_start_index](https://docs.gtk.org/atspi2/method.Hyperlink.get_start_index.html).
   * @ingroup atspi
   */
  int getStartIndex() const;

  /**
   * Wraps
   * [atspi_hyperlink_get_end_index](https://docs.gtk.org/atspi2/method.Hyperlink.get_end_index.html).
   * @ingroup atspi
   */
  int getEndIndex() const;

  /**
   * Wraps
   * [atspi_hyperlink_get_uri](https://docs.gtk.org/atspi2/method.Hyperlink.get_uri.html).
   * @ingroup atspi
   *
   * @param index: Indiciates which hyperlink anchor to query.
   */
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

}  // namespace acacia

#endif  // LIB_ATSPI_ATSPI_HYPERLINK_H_
