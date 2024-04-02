#ifndef LIB_ATSPI_ATSPI_TABLE_H_
#define LIB_ATSPI_ATSPI_TABLE_H_

#include <string>

#include <atspi/atspi.h>

/**
 * This object wraps an
 * [AtspiTable](https://docs.gtk.org/atspi2/iface.Table.html) pointer. It can be
 * retrieved from an accessible object which implements this interface using
 * AtspiNode::queryTable().
 * @ingroup atspi
 */
class AtspiTableInterface {
  AtspiTable* interface_;

 public:
  AtspiTableInterface(AtspiTable* interface) : interface_(interface){};
  AtspiTableInterface() : interface_(nullptr){};
  ~AtspiTableInterface(){};

  /**
   * Test whether the underlaying AtspiTable pointer is the null pointer. An
   * AtspiTableInterface with an null AtspiTable pointer will be created if the
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

#endif  // LIB_ATSPI_ATSPI_TABLE_H_
