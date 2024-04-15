#ifndef INCLUDE_ACACIA_ATSPI_ATSPI_VALUE_INTERFACE_H_
#define INCLUDE_ACACIA_ATSPI_ATSPI_VALUE_INTERFACE_H_

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
class AtspiValueInterface {
  AtspiValue* interface_;

 public:
  AtspiValueInterface(AtspiValue* interface) : interface_(interface){};
  AtspiValueInterface() : interface_(nullptr){};
  ~AtspiValueInterface(){};

  /**
   * Tests whether the underlying AtspiValue pointer is the null pointer. An
   * AtspiValueInterface with an null AtspiValue pointer will be created if the
   * wrapped API returned a nullptr with no error codes.
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
