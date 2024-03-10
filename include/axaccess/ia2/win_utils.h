#ifndef LIB_IA2_WIN_UTILS_H_
#define LIB_IA2_WIN_UTILS_H_

#include <memory>
#include <string>

#include <oleacc.h>
#include <wrl/client.h>

#include "axaccess/export.h"

namespace win_utils {

AXA_EXPORT Microsoft::WRL::ComPtr<IAccessible> GetAccessibleRoot(
    const std::string& name,
    DWORD dwProcessID);

AXA_EXPORT std::string nameFromHwnd(HWND hwnd);

AXA_EXPORT std::string BstrToString(BSTR bstr);

AXA_EXPORT std::string VariantToString(VARIANT variant);

AXA_EXPORT std::string HResultErrorToString(HRESULT err);

}  // namespace win_utils

#endif  // LIB_IA2_WIN_UTILS_H_
