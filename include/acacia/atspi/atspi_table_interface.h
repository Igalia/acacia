#ifndef INCLUDE_ACACIA_ATSPI_ATSPI_TABLE_INTERFACE_H_
#define INCLUDE_ACACIA_ATSPI_ATSPI_TABLE_INTERFACE_H_

#include "acacia/atspi/atspi_interface.h"

#include <string>

#include <atspi/atspi.h>

namespace acacia {

/**
 * This object wraps an
 * [AtspiTable](https://docs.gtk.org/atspi2/iface.Table.html) pointer. It can be
 * retrieved from an accessible object which implements this interface using
 * AtspiNode::queryTable().
 * @ingroup atspi
 */
class AtspiTableInterface : public AtspiInterface<AtspiTable> {
 public:
  using AtspiInterface<AtspiTable>::AtspiInterface;

  /**
   * Helper function to print commonly needed values associated with this
   * interface.
   * @ingroup atspi
   */
  std::string toString() const override;

  /**
   * Wraps
   * [atspi_table_get_n_columns](https://docs.gtk.org/atspi2/method.Table.get_n_columns.html).
   * @ingroup atspi
   */
  int getNColumns() const;

  /**
   * Wraps
   * [atspi_table_get_n_rows](https://docs.gtk.org/atspi2/method.Table.get_n_rows.html).
   * @ingroup atspi
   */
  int getNRows() const;
};

}  // namespace acacia

#endif  // INCLUDE_ACACIA_ATSPI_ATSPI_TABLE_INTERFACE_H_
