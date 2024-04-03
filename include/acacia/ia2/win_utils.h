#ifndef LIB_IA2_WIN_UTILS_H_
#define LIB_IA2_WIN_UTILS_H_

#include <memory>
#include <string>

#include <oleacc.h>
#include <wrl/client.h>

#include "acacia/export.h"
#include "ia_node.h"

/**
 * Returns the root node of the accessible tree of a running application
 * referenced by the application's accessible name.
 * @ingroup ia2
 *
 * @param name: The accessible name (or substring thereof) to search for.
 * @param pid: Optional. The process id to search for.
 *
 * @returns An @ref IANode.
 */
ACACIA_EXPORT IANode findRootIANodeForName(const std::string& name,
                                           const int pid = 0);

/**
 * Returns the root node of the accessiblity tree of a running application
 * referenced by pid.
 * @ingroup ia2
 *
 * @param pid: The process id of the running application.
 *
 * @returns An @ref IANode.
 */
ACACIA_EXPORT IANode findRootIANodeForPID(const int pid);

// The remaining functions are not exposed to the SWIG generated interfaces

ACACIA_EXPORT Microsoft::WRL::ComPtr<IAccessible> GetAccessibleRoot(
    const std::string& name,
    DWORD dwProcessID);

ACACIA_EXPORT std::string NameFromHwnd(HWND hwnd);

ACACIA_EXPORT std::string BstrToString(BSTR bstr);

ACACIA_EXPORT std::string VariantToString(VARIANT variant);

ACACIA_EXPORT std::string HResultErrorToString(HRESULT err);

#endif  // LIB_IA2_WIN_UTILS_H_