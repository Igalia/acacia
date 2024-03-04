#include "axaccess/ia2/win_utils.h"

#include <stdlib.h>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

#include <tlhelp32.h>
#include <windows.h>
#include <winuser.h>

#include "axaccess/ia2/ia2_api_all.h"

namespace win_utils {

struct WindowSearchCriteria {
  std::string name;
  std::optional<DWORD> pid;
  HWND match = nullptr;
};

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

std::string lower(const std::string& str) {
  std::string result = str;
  std::transform(result.begin(), result.end(), result.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  return result;
}

BOOL CALLBACK FindWindowWithName(HWND hwnd, LPARAM lparam) {
  WindowSearchCriteria* criteria =
      reinterpret_cast<WindowSearchCriteria*>(lparam);

  // If a PID is specified and this HWND lacks it, it's not a match.
  if (criteria->pid.has_value() && criteria->pid.value()) {
    DWORD windowPid;
    GetWindowThreadProcessId(hwnd, &windowPid);
    if (windowPid != criteria->pid.value()) {
      return TRUE;
    }
  }

  std::string title = lower(nameFromHwnd(hwnd));
  std::string name = lower(criteria->name);
  if (title.find(name) != std::string::npos) {
    std::cout << "Window found: " << title;
    if (criteria->pid.has_value()) {
      std::cout << " - PID: " << criteria->pid.value();
    }
    std::cout << std::endl;
    criteria->match = hwnd;
    return FALSE;
  }

  return TRUE;
}

Microsoft::WRL::ComPtr<IAccessible> GetAccessibleRoot(const std::string& name,
                                                      DWORD dwProcessID) {
  Microsoft::WRL::ComPtr<IAccessible> root;
  WindowSearchCriteria criteria;
  criteria.name = name;
  criteria.pid = dwProcessID;
  EnumWindows(FindWindowWithName, reinterpret_cast<LPARAM>(&criteria));
  if (criteria.match == nullptr) {
    return root;
  }
  // TODO: Consider using OBJID_CLIENT, but I think we want OBJID_WINDOW
  HRESULT hr = ::AccessibleObjectFromWindow(criteria.match, OBJID_WINDOW,
                                            IID_PPV_ARGS(&root));
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
