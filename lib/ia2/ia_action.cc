#include "acacia/ia2/ia_action.h"

#include <stdexcept>

#include "lib/ia2/win_utils.h"

namespace acacia {

std::string IAAction::toString() {
  if (isNull()) {
    return "Action: Not implemented";
  }

  long count = nActions();
  std::string result = "Action:";
  for (int i = 0; i < count; ++i) {
    std::string name = getName(i);
    result += " " + name;
  }
  return result;
}

long IAAction::nActions() {
  if (iface_) {
    long count = 0;
    HRESULT hr = iface_->nActions(&count);
    if (FAILED(hr)) {
      throw std::runtime_error("ERROR: nActions failed: " +
                               HResultErrorToString(hr));
    }
    return count;
  }
  return 0;
}

std::string IAAction::getDescription(int index) {
  if (iface_) {
    BSTR bstr_result;
    HRESULT hr = iface_->get_description(index, &bstr_result);
    if (FAILED(hr)) {
      throw std::runtime_error("ERROR: get_description failed: " +
                               HResultErrorToString(hr));
    }
    std::string str_result = BstrToString(bstr_result);
    SysFreeString(bstr_result);
    return str_result;
  }
  return std::string();
}

std::string IAAction::getName(int index) {
  if (iface_) {
    BSTR bstr_result;
    HRESULT hr = iface_->get_name(index, &bstr_result);
    if (FAILED(hr)) {
      throw std::runtime_error("ERROR: get_name failed: " +
                               HResultErrorToString(hr));
    }
    std::string str_result = BstrToString(bstr_result);
    SysFreeString(bstr_result);
    return str_result;
  }
  return std::string();
}

}  // namespace acacia
