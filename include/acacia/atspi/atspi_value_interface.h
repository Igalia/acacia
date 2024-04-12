#ifndef INCLUDE_ACACIA_ATSPI_ATSPI_VALUE_INTERFACE_H_
#define INCLUDE_ACACIA_ATSPI_ATSPI_VALUE_INTERFACE_H_

#include "acacia/atspi/atspi_interface.h"

#include <string>

#include <atspi/atspi.h>

namespace acacia {

/**
 * This object wraps an
 * [AtspiValue](https://docs.gtk.org/atspi2/iface.Value.html) pointer. It can be
 * retrieved from an accessible object which implements this interface using
 * AtspiNode::queryValue().
 * @ingroup atspi
 */
class AtspiValueInterface : public AtspiInterface<AtspiValue> {
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
   * [atspi_value_get_current_value](https://docs.gtk.org/atspi2/method.Value.get_current_value.html).
   * @ingroup atspi
   */
  double getCurrentValue() const;

  /**
   * Wraps
   * [atspi_value_get_maximum_value](https://docs.gtk.org/atspi2/method.Value.get_maximum_value.html).
   * @ingroup atspi
   */
  double getMaximumValue() const;

  /**
   * Wraps
   * [atspi_value_get_minimum_value](https://docs.gtk.org/atspi2/method.Value.get_minimum_value.html).
   * @ingroup atspi
   */
  double getMinimumValue() const;
};

}  // namespace acacia

#endif  // INCLUDE_ACACIA_ATSPI_ATSPI_VALUE_INTERFACE_H_
