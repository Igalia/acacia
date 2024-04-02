#ifndef LIB_ATSPI_ATSPI_COMPONENT_H_
#define LIB_ATSPI_ATSPI_COMPONENT_H_

#include <string>

#include <atspi/atspi.h>

/**
 * This object wraps an
 * [AtspiComponent](https://docs.gtk.org/atspi2/iface.Component.html) pointer.
 * It can be retrieved from an accessible object which implements this interface
 * using AtspiNode::queryComponent().
 * @ingroup atspi
 */
class AtspiComponentInterface {
  AtspiComponent* interface_;

 public:
  AtspiComponentInterface(AtspiComponent* interface) : interface_(interface){};
  AtspiComponentInterface() : interface_(nullptr){};
  ~AtspiComponentInterface(){};

  /**
   * Test whether the underlaying AtspiComponent pointer is the null pointer. An
   * AtspiComponentInterface with an null AtspiComponent pointer will be created
   * if the wrapped API returned a nullptr with no error codes.
   * @ingroup atspi
   */
  bool isNull() const { return !interface_; }

  /**
   * Helper function.
   * @ingroup atspi
   */
  std::string toString() const;

  /**
   * Wraps
   * [atspi_component_get_position](https://docs.gtk.org/atspi2/method.Component.get_position.html).
   * @ingroup atspi
   *
   * @returns An tuple in the form (x,y).
   */
  std::pair<int, int> getPosition() const;

  /**
   * Wraps
   * [atspi_component_get_size](https://docs.gtk.org/atspi2/method.Component.get_size.html).
   * @ingroup atspi
   *
   * @returns An tuple in the form (x,y).
   */
  std::pair<int, int> getSize() const;
};

#endif  // LIB_ATSPI_ATSPI_COMPONENT_H_
