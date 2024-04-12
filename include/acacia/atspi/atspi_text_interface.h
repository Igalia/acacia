#ifndef INCLUDE_ACACIA_ATSPI_ATSPI_TEXT_INTERFACE_H_
#define INCLUDE_ACACIA_ATSPI_ATSPI_TEXT_INTERFACE_H_

#include "acacia/atspi/atspi_interface.h"

#include <string>

#include <atspi/atspi.h>

namespace acacia {

/**
 * This object wraps an
 * [AtspiText](https://docs.gtk.org/atspi2/iface.Text.html) pointer. It can be
 * retrieved from an accessible object which implements this interface using
 * AtspiNode::queryText().
 * @ingroup atspi
 */
class AtspiTextInterface : public AtspiInterface<AtspiText> {
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
   * [atspi_text_get_caret_offset](https://docs.gtk.org/atspi2/method.Text.get_caret_offset.html).
   * @ingroup atspi
   */
  int getCaretOffset() const;

  /**
   * Wraps
   * [atspi_text_get_character_count](https://docs.gtk.org/atspi2/method.Text.get_character_count.html).
   * @ingroup atspi
   */
  int getCharacterCount() const;

  /**
   * Wraps
   * [atspi_text_get_text](https://docs.gtk.org/atspi2/method.Text.get_text.html).
   * @ingroup atspi
   *
   * @param start_offset
   * @param end_offset
   */
  std::string getText(int start_offset, int end_offset) const;
};

}  // namespace acacia

#endif  // INCLUDE_ACACIA_ATSPI_ATSPI_TEXT_INTERFACE_H_
