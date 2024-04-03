#ifndef LIB_ATSPI_ATSPI_DOCUMENT_H_
#define LIB_ATSPI_ATSPI_DOCUMENT_H_

#include <string>
#include <vector>

#include <atspi/atspi.h>

/**
 * This object wraps an
 * [AtspiDocument](https://docs.gtk.org/atspi2/iface.Document.html) pointer. It
 * can be retrieved from an accessible object which implements this interface
 * using AtspiNode::queryDocument().
 * @ingroup atspi
 */
class AtspiDocumentInterface {
  AtspiDocument* interface_;

 public:
  AtspiDocumentInterface(AtspiDocument* interface) : interface_(interface){};
  AtspiDocumentInterface() : interface_(nullptr){};
  ~AtspiDocumentInterface(){};

  /**
   * Tests whether the underlying AtspiDocument pointer is the null pointer. An
   * AtspiDocumentInterface with an null AtspiDocument pointer will be created
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
   * [atspi_document_get_locale](https://docs.gtk.org/atspi2/method.Document.get_locale.html).
   * @ingroup atspi
   */
  std::string getLocale() const;

  /**
   * Wraps
   * [atspi_document_get_document_attributes](https://docs.gtk.org/atspi2/method.Document.get_document_attributes.html).
   * @ingroup atspi
   *
   * @returns A vector of strings representing a GHashTable*. Each string in the
   * vector is a key value pair separated by a ":" character, for example,
   * "MimeType:text/html".
   */
  std::vector<std::string> getDocumentAttributes() const;
};

#endif  // LIB_ATSPI_ATSPI_DOCUMENT_H_
