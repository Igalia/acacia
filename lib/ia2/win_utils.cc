#include "axaccess/ia2/win_utils.h"

#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

#include <tlhelp32.h>
#include <windows.h>
#include <winuser.h>

#include "axaccess/ia2/ia2_api_all.h"

namespace win_utils {

std::string nameFromHwnd(HWND hwnd) {
  int length = ::GetWindowTextLength(hwnd);
  if (length == 0) {
    return "";
  }
  std::string title(length + 1, '\0');
  int actual_length = ::GetWindowText(hwnd, (LPSTR)title.data(), title.size());
  if (length > actual_length)
    title.erase(actual_length);
  return title;
}

// TODO: This is not the right API -- probably we should copy chrome code
// and find a hwnd by titla alone. Right now this only returns a Google Chrome
// HWND. But if I don't include PID, then I get other processess with google
// chrome in name
Microsoft::WRL::ComPtr<IAccessible> GetAccessibleFromProcessID(
    DWORD dwProcessID) {
  Microsoft::WRL::ComPtr<IAccessible> root;
  HWND hwnd = nullptr;
  do {
    hwnd = FindWindowEx(nullptr, hwnd, nullptr, nullptr);

    DWORD checkProcessID = 0;
    GetWindowThreadProcessId(hwnd, &checkProcessID);
    if (checkProcessID == dwProcessID) {
      std::string title = nameFromHwnd(hwnd);
      if (title.find("Google Chrome") != std::string::npos) {
        break;
      }
    }
  } while (hwnd != nullptr);

  if (hwnd == nullptr) {
    std::cout << "Could not find hwnd\n";
    return root;
  }
  // TODO: Consider using OBJID_CLIENT, but I think we want OBJID_WINDOW
  HRESULT hr =
      ::AccessibleObjectFromWindow(hwnd, OBJID_WINDOW, IID_PPV_ARGS(&root));
  if (FAILED(hr)) {
    std::cout << "Could not get accessible\n";
  }
  return root;
}

std::string BstrToString(BSTR bstr) {
  if (SysStringLen(bstr) == 0)
    return "";
  std::wstring wstr(bstr, SysStringLen(bstr));
  int size = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0,
                                 nullptr, nullptr);
  std::string str(size, '\0');
  WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], size, nullptr,
                      nullptr);
  return str;
}

std::string HResultErrorToString(HRESULT err) {
  switch (err) {
    case E_NOTIMPL:
      return "E_NOTIMPL";
    case E_NOINTERFACE:
      return "E_NOINTERFACE";
    case E_POINTER:
      return "E_POINTER";
    case E_ABORT:
      return "E_ABORT";
    case E_FAIL:
      return "E_FAIL";
    case E_UNEXPECTED:
      return "E_UNEXPECTED";
    case E_ACCESSDENIED:
      return "E_ACCESSDENIED";
    case E_HANDLE:
      return "E_HANDLE";
    case E_OUTOFMEMORY:
      return "E_OUTOFMEMORY";
    case E_INVALIDARG:
      return "E_INVALIDARG";
    // TODO: test this
    default:
      return std::to_string(err);
  }
}
}  // namespace win_utils
