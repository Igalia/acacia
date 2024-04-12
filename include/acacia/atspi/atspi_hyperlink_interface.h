#ifndef INCLUDE_ACACIA_ATSPI_ATSPI_HYPERLINK_INTERFACE_H_
#define INCLUDE_ACACIA_ATSPI_ATSPI_HYPERLINK_INTERFACE_H_

#include "acacia/atspi/atspi_interface.h"

#include <memory>
#include <string>

namespace acacia {

/**
 * This object wraps an
 * [AtspiHyperlink](https://docs.gtk.org/atspi2/iface.Hyperlink.html) pointer.
 * It can be retrieved from an accessible object which implements this interface
 * using AtspiNode::queryHyperlink().
 * @ingroup atspi
 */
class AtspiHyperlinkInterface : public AtspiInterface<AtspiHyperlink> {
 public:
  using AtspiInterface::AtspiInterface;
  using AtspiInterface::operator=;

  /**
   * Helper function to print commonly needed values associated with this
   * interface.
   * @ingroup atspi
   */
  std::string toString() const override;

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
};

}  // namespace acacia

#endif  // INCLUDE_ACACIA_ATSPI_ATSPI_HYPERLINK_INTERFACE_H_
