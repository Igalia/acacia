#ifndef INCLUDE_ACACIA_ATSPI_ATSPI_TABLE_CELL_INTERFACE_H_
#define INCLUDE_ACACIA_ATSPI_ATSPI_TABLE_CELL_INTERFACE_H_

#include "acacia/atspi/atspi_interface.h"

#include <string>

#include <atspi/atspi.h>

namespace acacia {

/**
 * This object wraps an
 * [AtspiTableCell](https://docs.gtk.org/atspi2/iface.TableCell.html) pointer.
 * It can be retrieved from an accessible object which implements this interface
 * using AtspiNode::queryTableCell().
 * @ingroup atspi
 */
class AtspiTableCellInterface : public AtspiInterface<AtspiTableCell> {
 public:
  using AtspiInterface<AtspiTableCell>::AtspiInterface;

  /**
   * Helper function to print commonly needed values associated with this
   * interface.
   * @ingroup atspi
   */
  std::string toString() const override;

  /**
   * Wraps
   * [atspi_table_cell_get_position](https://docs.gtk.org/atspi2/method.TableCell.get_position.html).
   * @ingroup atspi
   *
   * @returns An tuple in the form (row, column).
   */
  std::pair<int, int> getPosition() const;

  /**
   * Wraps
   * [atspi_table_cell_get_column_index](https://docs.gtk.org/atspi2/method.TableCell.get_column_index.html).
   * @ingroup atspi
   */
  int getColumnIndex() const;

  /**
   * Wraps
   * [atspi_table_cell_get_column_span](https://docs.gtk.org/atspi2/method.TableCell.get_column_span.html).
   * @ingroup atspi
   */
  int getColumnSpan() const;

  /**
   * Wraps
   * [atspi_table_cell_get_row_index](https://docs.gtk.org/atspi2/method.TableCell.get_row_index.html).
   * @ingroup atspi
   */
  int getRowIndex() const;

  /**
   * Wraps
   * [atspi_table_cell_get_row_span](https://docs.gtk.org/atspi2/method.TableCell.get_row_span.html).
   * @ingroup atspi
   */
  int getRowSpan() const;
};

}  // namespace acacia

#endif  // INCLUDE_ACACIA_ATSPI_ATSPI_TABLE_CELL_INTERFACE_H_
