#ifndef LIB_ATSPI_ATSPI_TABLE_CELL_H_
#define LIB_ATSPI_ATSPI_TABLE_CELL_H_

#include <string>

#include <atspi/atspi.h>

/**
 * This object wraps an
 * [AtspiTableCell](https://docs.gtk.org/atspi2/iface.TableCell.html) pointer.
 * It can be retrieved from an accessible object which implements this interface
 * using AtspiNode::queryTableCell().
 * @ingroup atspi
 */
class AtspiTableCellInterface {
  AtspiTableCell* interface_;

 public:
  AtspiTableCellInterface(AtspiTableCell* interface) : interface_(interface){};
  AtspiTableCellInterface() : interface_(nullptr){};
  ~AtspiTableCellInterface(){};

  /**
   * Test whether the underlaying AtspiTableCell pointer is the null pointer. An
   * AtspiTableCellInterface with an null AtspiTableCell pointer will be created
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

#endif  // LIB_ATSPI_ATSPI_TABLE_CELL_H_
