#ifndef LIB_IA2_WIN_UTILS_H_
#define LIB_IA2_WIN_UTILS_H_

#include <memory>
#include <string>
#include <oleacc.h>
#include <wrl/client.h>

#include "axaccess/export.h"

AXA_EXPORT Microsoft::WRL::ComPtr<IAccessible> GetAccessibleFromProcessID(DWORD dwProcessID);

AXA_EXPORT std::string nameFromHwnd(HWND hwnd);

AXA_EXPORT std::string BstrToString(BSTR bstr);


#endif  // LIB_IA2_WIN_UTILS_H_
