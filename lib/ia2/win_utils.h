#ifndef LIB_ACACIA_IA2_WIN_UTILS_H_
#define LIB_ACACIA_IA2_WIN_UTILS_H_

#include <string>

#include <oleacc.h>
#include <wrl/client.h>

namespace acacia {

Microsoft::WRL::ComPtr<IAccessible> GetAccessibleRoot(const std::string& name,
                                                      DWORD dwProcessID);

std::string NameFromHwnd(HWND hwnd);

std::string BstrToString(BSTR bstr);

std::string VariantToString(VARIANT variant);

std::string HResultErrorToString(HRESULT err);

}  // namespace acacia

#endif  // LIB_ACACIA_IA2_WIN_UTILS_H_
