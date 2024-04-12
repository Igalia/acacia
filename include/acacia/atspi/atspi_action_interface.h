#ifndef INCLUDE_ACACIA_ATSPI_ATSPI_ACTION_INTERFACE_H_
#define INCLUDE_ACACIA_ATSPI_ATSPI_ACTION_INTERFACE_H_

#include "acacia/atspi/atspi_interface.h"

#include <string>

#include <atspi/atspi.h>

namespace acacia {

/**
 * This object wraps an
 * [AtspiAction](https://docs.gtk.org/atspi2/iface.Action.html) pointer. It can
 * be retrieved from an accessible object which implements this interface using
 * AtspiNode::queryAction().
 * @ingroup atspi
 */
class AtspiActionInterface : public AtspiInterface<AtspiAction> {
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
   * [atspi_action_get_n_actions](https://docs.gtk.org/atspi2/method.Action.get_n_actions.html).
   * @ingroup atspi
   */
  int getNActions() const;

  /**
   * Wraps
   * [atspi_action_get_name](https://docs.gtk.org/atspi2/method.Action.get_name.html).
   * @ingroup atspi
   *
   * @param index: Index of the action.
   */
  std::string getName(int index) const;

  /**
   * Wraps
   * [atspi_action_get_description](https://docs.gtk.org/atspi2/method.Action.get_description.html).
   * @ingroup atspi
   *
   * @param index: Index of the action.
   */
  std::string getDescription(int index) const;
};

}  // namespace acacia

#endif  // INCLUDE_ACACIA_ATSPI_ATSPI_ACTION_INTERFACE_H_
