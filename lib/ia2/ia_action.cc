#include "axaccess/ia2/ia_action.h"

#include "axaccess/ia2/win_utils.h"

using namespace win_utils;

std::string IAAction::GetProperties() {
  long count = nActions();
  if (!count) {
    return std::string();
  }

  std::string result = "Action:";
  for (int i = 0; i < count; ++i) {
    std::string name = get_name(i);
    result += " " + name;
  }
  return result;
}

long IAAction::nActions() {
  if (auto iface = QueryInterface()) {
    long count = 0;
    if (SUCCEEDED(iface->nActions(&count))) {
      return count;
    }
  }
  return 0;
}

std::string IAAction::get_description(int index) {
  if (auto iface = QueryInterface()) {
    BSTR bstr_result;
    if (SUCCEEDED(iface->get_description(index, &bstr_result))) {
      std::string str_result = BstrToString(bstr_result);
      SysFreeString(bstr_result);
      return str_result;
    }
  }
  return std::string();
}

std::string IAAction::get_name(int index) {
  if (auto iface = QueryInterface()) {
    BSTR bstr_result;
    if (SUCCEEDED(iface->get_name(index, &bstr_result))) {
      std::string str_result = BstrToString(bstr_result);
      SysFreeString(bstr_result);
      return str_result;
    }
  }
  return std::string();
}

Microsoft::WRL::ComPtr<IAccessibleAction> IAAction::QueryInterface() {
  if (node_.IsNull() || !node_.GetIAccessible()) {
    return nullptr;
  }

  Microsoft::WRL::ComPtr<IAccessibleAction> iface;
  Microsoft::WRL::ComPtr<IServiceProvider> service_provider;
  HRESULT hr =
      node_.GetIAccessible()->QueryInterface(IID_PPV_ARGS(&service_provider));
  return SUCCEEDED(service_provider->QueryService(IID_IAccessible,
                                                  IID_PPV_ARGS(&iface)))
             ? iface
             : nullptr;
}
