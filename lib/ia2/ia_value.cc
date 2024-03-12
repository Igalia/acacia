#include "axaccess/ia2/ia_value.h"

#include "axaccess/ia2/win_utils.h"

using namespace win_utils;

IAValue::IAValue(IANode node) {
  if (auto service_provider = node.GetServiceProvider()) {
    service_provider->QueryService(IID_IAccessible, IID_PPV_ARGS(&iface_));
  }
}

std::string IAValue::GetProperties() {
  if (!iface_) {
    return std::string();
  }

  std::string result = "Value: " + get_currentValue() +
                       " min: " + get_minimumValue() +
                       " max: " + get_maximumValue();
  return result;
}

std::string IAValue::get_currentValue() {
  if (iface_) {
    VARIANT variant_result;
    if (SUCCEEDED(iface_->get_currentValue(&variant_result))) {
      std::string str_result = VariantToString(variant_result);
      VariantClear(&variant_result);
      return str_result;
    }
  }
  return std::string();
}

std::string IAValue::get_maximumValue() {
  if (iface_) {
    VARIANT variant_result;
    if (SUCCEEDED(iface_->get_maximumValue(&variant_result))) {
      std::string str_result = VariantToString(variant_result);
      VariantClear(&variant_result);
      return str_result;
    }
  }
  return std::string();
}

std::string IAValue::get_minimumValue() {
  if (iface_) {
    VARIANT variant_result;
    if (SUCCEEDED(iface_->get_minimumValue(&variant_result))) {
      std::string str_result = VariantToString(variant_result);
      VariantClear(&variant_result);
      return str_result;
    }
  }
  return std::string();
}
