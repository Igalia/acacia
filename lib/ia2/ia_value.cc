#include "axaccess/ia2/ia_value.h"

#include <stdexcept>

#include "axaccess/ia2/win_utils.h"

using namespace win_utils;

std::string IAValue::GetProperties() {
  if (IsNull()) {
    return "Value: Not implemented";
  }

  std::string result = "Value: " + get_currentValue() +
                       " min: " + get_minimumValue() +
                       " max: " + get_maximumValue();
  return result;
}

std::string IAValue::get_currentValue() {
  if (iface_) {
    VARIANT variant_result;
    HRESULT hr = iface_->get_currentValue(&variant_result);
    if (FAILED(hr)) {
      throw std::runtime_error("ERROR: get_currentValue failed: " +
                               HResultErrorToString(hr));
    }
    std::string str_result = VariantToString(variant_result);
    VariantClear(&variant_result);
    return str_result;
  }
  return std::string();
}

std::string IAValue::get_maximumValue() {
  if (iface_) {
    VARIANT variant_result;
    HRESULT hr = iface_->get_maximumValue(&variant_result);
    if (FAILED(hr)) {
      throw std::runtime_error("ERROR: get_maximumValue failed: " +
                               HResultErrorToString(hr));
    }
    std::string str_result = VariantToString(variant_result);
    VariantClear(&variant_result);
    return str_result;
  }
  return std::string();
}

std::string IAValue::get_minimumValue() {
  if (iface_) {
    VARIANT variant_result;
    HRESULT hr = iface_->get_minimumValue(&variant_result);
    if (FAILED(hr)) {
      throw std::runtime_error("ERROR: get_minimumValue failed: " +
                               HResultErrorToString(hr));
    }
    std::string str_result = VariantToString(variant_result);
    VariantClear(&variant_result);
    return str_result;
  }
  return std::string();
}
