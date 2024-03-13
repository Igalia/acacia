#ifndef LIB_IA2_WIN_UTILS_H_
#define LIB_IA2_WIN_UTILS_H_

#include <memory>
#include <string>

#include <oleacc.h>
#include <wrl/client.h>

#include "axaccess/export.h"

namespace win_utils {

/**
 * Returns the root node of the accessiblity tree of a running
 * application referenced by name and process ID.
 * @ingroup ia2
 *
 * @param name: The name of the application.
 * @param dwProcessID: process ID.
 *
 * @returns Pointer to the node.
 */
AXA_EXPORT Microsoft::WRL::ComPtr<IAccessible> GetAccessibleRoot(
    const std::string& name,
    DWORD dwProcessID);

AXA_EXPORT std::string nameFromHwnd(HWND hwnd);

AXA_EXPORT std::string BstrToString(BSTR bstr);

AXA_EXPORT std::string VariantToString(VARIANT variant);

AXA_EXPORT std::string HResultErrorToString(HRESULT err);

}  // namespace win_utils

#endif  // LIB_IA2_WIN_UTILS_H_
