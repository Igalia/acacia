#include "acacia/ia2/win_utils.h"

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

#include "third_party/ia2/include/ia2/ia2_api_all.h"

struct WindowSearchCriteria {
  std::optional<std::string> name;
  std::optional<DWORD> pid;
  HWND match = nullptr;
};

class CCoInitialize {
 public:
  CCoInitialize() { hr_ = CoInitialize(NULL); }
  ~CCoInitialize() {
    if (SUCCEEDED(hr_))
      CoUninitialize();
  }
  HRESULT result() const { return hr_; }
  HRESULT hr_;
};

CCoInitialize init;

std::string NameFromHwnd(HWND hwnd) {
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

BOOL CALLBACK FindWindow(HWND hwnd, LPARAM lparam) {
  WindowSearchCriteria* criteria =
      reinterpret_cast<WindowSearchCriteria*>(lparam);

  bool has_name = criteria->name.has_value() && !criteria->name.value().empty();
  bool has_pid = criteria->pid.has_value() && criteria->pid.value();
  if (!has_name && !has_pid) {
    std::cerr << "ERROR: FindWindow requires a name and/or PID" << std::endl;
    return FALSE;
  }

  DWORD window_pid;
  GetWindowThreadProcessId(hwnd, &window_pid);
  if (has_pid && window_pid != criteria->pid.value()) {
    return TRUE;
  }

  std::string title = lower(NameFromHwnd(hwnd));
  if (has_name) {
    std::string name = lower(criteria->name.value());
    if (title.find(name) == std::string::npos) {
      return TRUE;
    }
  }

  std::cout << "Window found: " << NameFromHwnd(hwnd);
  if (has_pid) {
    std::cout << " - PID: " << criteria->pid.value();
  }
  std::cout << std::endl;
  criteria->match = hwnd;
  return FALSE;
}

Microsoft::WRL::ComPtr<IAccessible> GetAccessibleRoot(const std::string& name,
                                                      DWORD dwProcessID) {
  if (FAILED(init.result())) {
    throw std::runtime_error(
        "Could not initialize the COM library, CoInitialize returned: " +
        HResultErrorToString(init.result()));
  }
  Microsoft::WRL::ComPtr<IAccessible> root;
  WindowSearchCriteria criteria;
  criteria.name = name;
  criteria.pid = dwProcessID;
  EnumWindows(FindWindow, reinterpret_cast<LPARAM>(&criteria));
  if (criteria.match == nullptr) {
    return root;
  }
  HRESULT hr = ::AccessibleObjectFromWindow(criteria.match, OBJID_WINDOW,
                                            IID_PPV_ARGS(&root));
  // TODO: Should we throw here?
  if (FAILED(hr)) {
    std::cout << "Could not get accessible\n";
  }
  return root;
}

IANode findRootIANodeForName(const std::string& name, const int pid) {
  Microsoft::WRL::ComPtr<IAccessible> root = GetAccessibleRoot(name, pid);
  return IANode(root);
}

IANode findRootIANodeForPID(const int pid) {
  Microsoft::WRL::ComPtr<IAccessible> root = GetAccessibleRoot("", pid);
  return IANode(root);
}

std::string BstrToString(BSTR bstr) {
  if (SysStringLen(bstr) == 0)
    return "";
  std::wstring wstr(bstr);
  int size = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0,
                                 nullptr, nullptr);
  std::string str(size, '\0');
  WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], size, nullptr,
                      nullptr);
  str.resize(size - 1);
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
    case DISP_E_MEMBERNOTFOUND:
      return "DISP_E_MEMBERNOTFOUND";
    default:
      return std::to_string(err);
  }
}

std::string VariantToString(VARIANT variant) {
  switch (variant.vt) {
    case VT_EMPTY:
      return "";
    case VT_BSTR:
      return BstrToString(variant.bstrVal);
    case VT_I1:
    case VT_I2:
    case VT_I4:
    case VT_I8:
      return std::to_string(variant.lVal);
    case VT_UI1:
    case VT_UI2:
    case VT_UI4:
    case VT_UI8:
      return std::to_string(variant.ulVal);
    case VT_R4:
      return std::to_string(variant.fltVal);
    case VT_R8:
      return std::to_string(variant.dblVal);
    case VT_BOOL:
      return variant.boolVal == VARIANT_TRUE ? "true" : "false";
    case VT_ERROR:
      return "Error code: " + std::to_string(variant.scode);
    default:
      return "Unsupported type: " + std::to_string(variant.vt);
  }
}
