#ifndef LIB_ATSPI_ATSPI_TEXT_H_
#define LIB_ATSPI_ATSPI_TEXT_H_

#include <string>

#include <atspi/atspi.h>

/**
 * This object wraps an
 * [AtspiText](https://docs.gtk.org/atspi2/iface.Text.html) pointer. It can be
 * retrieved from an accessible object which implements this interface using
 * AtspiNode::queryText().
 * @ingroup atspi
 */
class AtspiTextInterface {
  AtspiText* interface_;

 public:
  AtspiTextInterface(AtspiText* interface) : interface_(interface){};
  AtspiTextInterface() : interface_(nullptr){};
  ~AtspiTextInterface(){};

  /**
   * Tests whether the underlying AtspiText pointer is the null pointer. An
   * AtspiTextInterface with an null AtspiText pointer will be created if the
   * wrapped API returned a nullptr with no error codes.
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

#endif  // LIB_ATSPI_ATSPI_TEXT_H_
