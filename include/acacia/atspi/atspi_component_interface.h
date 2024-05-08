#ifndef INCLUDE_ACACIA_ATSPI_ATSPI_COMPONENT_INTERFACE_H_
#define INCLUDE_ACACIA_ATSPI_ATSPI_COMPONENT_INTERFACE_H_

#include "acacia/atspi/atspi_interface.h"

#include <string>

#include <atspi/atspi.h>

namespace acacia {

/**
 * This object wraps an
 * [AtspiComponent](https://docs.gtk.org/atspi2/iface.Component.html) pointer.
 * It can be retrieved from an accessible object which implements this interface
 * using AtspiNode::queryComponent().
 * @ingroup atspi
 */
class AtspiComponentInterface : public AtspiInterface<AtspiComponent> {
 public:
  using AtspiInterface::AtspiInterface;

  /**
   * Helper function to print commonly needed values associated with this
   * interface.
   * @ingroup atspi
   */
  std::string toString() const override;

  /**
   * Wraps
   * [atspi_component_get_position](https://docs.gtk.org/atspi2/method.Component.get_position.html).
   * @ingroup atspi
   *
   * @returns A tuple in the form (x,y).
   */
  std::pair<int, int> getPosition() const;

  /**
   * Wraps
   * [atspi_component_get_size](https://docs.gtk.org/atspi2/method.Component.get_size.html).
   * @ingroup atspi
   *
   * @returns An tuple in the form (width, height).
   */
  std::pair<int, int> getSize() const;
};

}  // namespace acacia

#endif  // INCLUDE_ACACIA_ATSPI_ATSPI_COMPONENT_INTERFACE_H_
