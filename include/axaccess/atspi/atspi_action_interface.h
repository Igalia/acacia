#ifndef LIB_ATSPI_ATSPI_ACTION_H_
#define LIB_ATSPI_ATSPI_ACTION_H_

#include <string>

#include <atspi/atspi.h>

/**
 * This object wraps an
 * [AtspiAction](https://docs.gtk.org/atspi2/iface.Action.html) pointer. It can
 * be retrieved from an accessible object which implements this interface using
 * AtspiNode::queryValue().
 * @ingroup atspi
 */
class AtspiActionInterface {
  AtspiAction* interface_;

 public:
  AtspiActionInterface(AtspiAction* interface) : interface_(interface){};
  AtspiActionInterface() : interface_(nullptr){};
  ~AtspiActionInterface(){};

  /**
   * Test whether the underlaying AtspiAction pointer is the null pointer. An
   * AtspiActionInterface with an null AtspiAction pointer will be created if
   * the wrapped API returned a nullptr with no error codes.
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

#endif  // LIB_ATSPI_ATSPI_ACTION_H_
