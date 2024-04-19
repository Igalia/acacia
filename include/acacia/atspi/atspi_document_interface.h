#ifndef INCLUDE_ACACIA_ATSPI_ATSPI_DOCUMENT_INTERFACE_H_
#define INCLUDE_ACACIA_ATSPI_ATSPI_DOCUMENT_INTERFACE_H_

#include "acacia/atspi/atspi_interface.h"

#include <string>
#include <vector>

#include <atspi/atspi.h>

namespace acacia {

/**
 * This object wraps an
 * [AtspiDocument](https://docs.gtk.org/atspi2/iface.Document.html) pointer. It
 * can be retrieved from an accessible object which implements this interface
 * using AtspiNode::queryDocument().
 * @ingroup atspi
 */
class AtspiDocumentInterface : public AtspiInterface<AtspiDocument> {
 public:
  using AtspiInterface<AtspiDocument>::AtspiInterface;

  /**
   * Helper function to print commonly needed values associated with this
   * interface.
   * @ingroup atspi
   */
  std::string toString() const override;

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

}  // namespace acacia

#endif  // INCLUDE_ACACIA_ATSPI_ATSPI_DOCUMENT_INTERFACE_H_
