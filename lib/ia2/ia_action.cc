#include "axaccess/ia2/ia_action.h"

#include "axaccess/ia2/win_utils.h"

using namespace win_utils;

IAAction::IAAction(IANode node) {
  if (auto service_provider = node.GetServiceProvider()) {
    service_provider->QueryService(IID_IAccessible, IID_PPV_ARGS(&iface_));
  }
}

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
  if (iface_) {
    long count = 0;
    if (SUCCEEDED(iface_->nActions(&count))) {
      return count;
    }
  }
  return 0;
}

std::string IAAction::get_description(int index) {
  if (iface_) {
    BSTR bstr_result;
    if (SUCCEEDED(iface_->get_description(index, &bstr_result))) {
      std::string str_result = BstrToString(bstr_result);
      SysFreeString(bstr_result);
      return str_result;
    }
  }
  return std::string();
}

std::string IAAction::get_name(int index) {
  if (iface_) {
    BSTR bstr_result;
    if (SUCCEEDED(iface_->get_name(index, &bstr_result))) {
      std::string str_result = BstrToString(bstr_result);
      SysFreeString(bstr_result);
      return str_result;
    }
  }
  return std::string();
}
