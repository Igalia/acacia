#ifndef LIB_IA2_IA_NODE_H_
#define LIB_IA2_IA_NODE_H_

#include <memory>
#include <string>
#include <vector>

#include <oleacc.h>
#include <wrl/client.h>

#include "axaccess/export.h"
#include "axaccess/ia2/ia_2.h"
#include "axaccess/ia2/ia_action.h"
#include "axaccess/ia2/ia_component.h"
#include "axaccess/ia2/ia_hyperlink.h"
#include "axaccess/ia2/ia_table2.h"
#include "axaccess/ia2/ia_table_cell.h"
#include "axaccess/ia2/ia_text.h"
#include "axaccess/ia2/ia_value.h"

/** @defgroup ia2 IA2 API (Windows)
 *  IA2 Accessiblity API for Windows
 *  @{
 */
/** @} */  // end of axapi group

/**
 * Represents a node in the MSAA with IAccessible2 accessibility tree. This
 * object wraps an [MSAA/IAccessible
 * Interface](https://learn.microsoft.com/en-us/windows/win32/api/oleacc/nn-oleacc-iaccessible)
 * pointer.
 * @ingroup ia2
 */
class AXA_EXPORT IANode {
 public:
  IANode(){};
  IANode(Microsoft::WRL::ComPtr<IAccessible> root, VARIANT child_id)
      : root_(root), child_id_(child_id){};
  IANode(Microsoft::WRL::ComPtr<IAccessible> root) : root_(root) {
    child_id_.intVal = CHILDID_SELF;
    child_id_.vt = VT_I4;
  };
  ~IANode(){};

  /**
   * Wraps QueryInterface and QueryService to retrieve the IAccessible2
   * interface for this node.
   * @ingroup ia2
   *
   * @returns An @ref IA2.
   */
  IA2 QueryIA2();

  /**
   * Wraps QueryInterface and QueryService to retrieve the IAccessibleAction
   * interface for this node.
   * @ingroup ia2
   *
   * @returns An @ref IAAction.
   */
  IAAction QueryAction();

  /**
   * Wraps QueryInterface and QueryService to retrieve the IAccessibleComponent
   * interface for this node.
   * @ingroup ia2
   *
   * @returns An @ref IAComponent.
   */
  IAComponent QueryComponent();

  /**
   * Wraps QueryInterface and QueryService to retrieve the IAccessibleHyperlink
   * interface for this node.
   * @ingroup ia2
   *
   * @returns An @ref IAHyperlink.
   */
  IAHyperlink QueryHyperlink();

  /**
   * Wraps QueryInterface and QueryService to retrieve the IAccessibleTableCell
   * interface for this node.
   * @ingroup ia2
   *
   * @returns An @ref IATableCell.
   */
  IATableCell QueryTableCell();

  /**
   * Wraps QueryInterface and QueryService to retrieve the IAccessibleTable2
   * interface for this node.
   * @ingroup ia2
   *
   * @returns An @ref IATable2.
   */
  IATable2 QueryTable2();

  /**
   * Wraps QueryInterface and QueryService to retrieve the IAccessibleText
   * interface for this node.
   * @ingroup ia2
   *
   * @returns An @ref IAText.
   */
  IAText QueryText();

  /**
   * Wraps QueryInterface and QueryService to retrieve the IAccessibleValue
   * interface for this node.
   * @ingroup ia2
   *
   * @returns An @ref IAValue.
   */
  IAValue QueryValue();

  /**
   * Tests whether the underlying IAccessible pointer is the null pointer.
   * An IANode with an null IAccessible pointer will be created if the
   * wrapped API returned a nullptr with no error codes.
   * @ingroup ia2
   */
  bool isNull();

  /**
   * Wraps
   * [get_accRole](https://learn.microsoft.com/en-us/windows/win32/api/oleacc/nf-oleacc-iaccessible-get_accrole).
   * @ingroup ia2
   */
  std::string getAccRole();

  /**
   * Wraps
   * [get_accName](https://learn.microsoft.com/en-us/windows/win32/api/oleacc/nf-oleacc-iaccessible-get_accname).
   * @ingroup ia2
   */
  std::string getAccName();

  /**
   * Wraps
   * [get_accDescription](https://learn.microsoft.com/en-us/windows/win32/api/oleacc/nf-oleacc-iaccessible-get_accdescription).
   * @ingroup ia2
   */
  std::string getAccDescription();

  /**
   * Wraps
   * [get_accChildCount](https://learn.microsoft.com/en-us/windows/win32/api/oleacc/nf-oleacc-iaccessible-get_accchildcount).
   * @ingroup ia2
   */
  long getAccChildCount();

  /**
   * Helper function which uses
   * [AccessibleChildren](https://learn.microsoft.com/en-us/windows/win32/api/oleacc/nf-oleacc-accessiblechildren)
   * to query accessible children, and returns the child specified by the index.
   * Some children returned by the AccessibleChildAt are not accessible objects
   * with their own IAccessible interface, but partial children with no
   * interfaces. For these partial children, only a role and a name are
   * available.
   * @ingroup ia2
   *
   * @param index
   *
   * @returns An @ref IANode.
   */
  IANode AccessibleChildAt(int index);

  /**
   * Wraps
   * [get_accState](https://learn.microsoft.com/en-us/windows/win32/api/oleacc/nf-oleacc-iaccessible-get_accstate).
   * @ingroup ia2
   */
  long getAccState();

  /**
   * Helper function to convert the state bit vector to strings indicating the
   * [state
   * constants](https://learn.microsoft.com/en-us/windows/win32/winauto/object-state-constants).
   * @ingroup ia2
   */
  std::vector<std::string> getStateStrings();

 private:
  Microsoft::WRL::ComPtr<IServiceProvider> GetServiceProvider();

  Microsoft::WRL::ComPtr<IAccessible> root_;
  // This variant is used to recieve IAccessible
  // information about either the accessible object itself,
  // or its partial child.
  // TODO: Create own type for partial children. #95
  VARIANT child_id_;
};

#endif  // LIB_IA2_IA_NODE_H_
