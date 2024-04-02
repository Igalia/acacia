#ifndef LIB_IA2_WIN_UTILS_H_
#define LIB_IA2_WIN_UTILS_H_

#include <memory>
#include <string>

#include <oleacc.h>
#include <wrl/client.h>

#include "axaccess/export.h"
#include "ia_node.h"

/**
 * Returns the root node of the accessible tree of a running application
 * referenced by pid.
 * @ingroup ia2
 *
 * @param pid: The process id of the running application.
 *
 * @returns An @ref IANode.
 */
AXA_EXPORT IANode findRootIANodeForName(const std::string& name,
                                        const int pid = 0);

/**
 * Returns the root node of the accessible tree of a running application
 * referenced by pid.
 * @ingroup ia2
 *
 * @param pid: The process id of the running application.
 *
 * @returns An @ref IANode.
 */
AXA_EXPORT IANode findRootIANodeForPID(const int pid);

// The remaining functions are not exposed to the SWIG generated interfaces

AXA_EXPORT Microsoft::WRL::ComPtr<IAccessible> GetAccessibleRoot(
    const std::string& name,
    DWORD dwProcessID);

AXA_EXPORT std::string NameFromHwnd(HWND hwnd);

AXA_EXPORT std::string BstrToString(BSTR bstr);

AXA_EXPORT std::string VariantToString(VARIANT variant);

AXA_EXPORT std::string HResultErrorToString(HRESULT err);

#endif  // LIB_IA2_WIN_UTILS_H_
