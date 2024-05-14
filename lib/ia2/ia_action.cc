#include "acacia/ia2/ia_action.h"

#include <stdexcept>

#include "lib/ia2/win_utils.h"
#include "lib/utils.h"

namespace acacia {

std::string IAAction::toString() {
  if (isNull()) {
    return "Action: Not implemented";
  }
  std::string actions = exceptionToString([this]() {
    std::string action_list;
    long count = this->nActions();
    for (int i = 0; i < count; ++i) {
      std::string name = this->getName(i);
      action_list += " " + name;
    }
    return action_list;
  });

  return "Actions:" + actions;
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
