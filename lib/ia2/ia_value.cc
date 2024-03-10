#include "axaccess/ia2/ia_value.h"

#include "axaccess/ia2/win_utils.h"

using namespace win_utils;

std::string IAValue::GetProperties() {
  auto iface = QueryInterface();
  if (!iface) {
    return std::string();
  }

  std::string result = "Value: " + get_currentValue() +
                       " min: " + get_minimumValue() +
                       " max: " + get_maximumValue();
  return result;
}

std::string IAValue::get_currentValue() {
  if (auto iface = QueryInterface()) {
    VARIANT variant_result;
    if (SUCCEEDED(iface->get_currentValue(&variant_result))) {
      std::string str_result = VariantToString(variant_result);
      VariantClear(&variant_result);
      return str_result;
    }
  }
  return std::string();
}

std::string IAValue::get_maximumValue() {
  if (auto iface = QueryInterface()) {
    VARIANT variant_result;
    if (SUCCEEDED(iface->get_maximumValue(&variant_result))) {
      std::string str_result = VariantToString(variant_result);
      VariantClear(&variant_result);
      return str_result;
    }
  }
  return std::string();
}

std::string IAValue::get_minimumValue() {
  if (auto iface = QueryInterface()) {
    VARIANT variant_result;
    if (SUCCEEDED(iface->get_minimumValue(&variant_result))) {
      std::string str_result = VariantToString(variant_result);
      VariantClear(&variant_result);
      return str_result;
    }
  }
  return std::string();
}

Microsoft::WRL::ComPtr<IAccessibleValue> IAValue::QueryInterface() {
  if (node_.IsNull() || !node_.GetIAccessible()) {
    return nullptr;
  }

  Microsoft::WRL::ComPtr<IAccessibleValue> iface;
  Microsoft::WRL::ComPtr<IServiceProvider> service_provider;
  HRESULT hr =
      node_.GetIAccessible()->QueryInterface(IID_PPV_ARGS(&service_provider));
  return SUCCEEDED(service_provider->QueryService(IID_IAccessible,
                                                  IID_PPV_ARGS(&iface)))
             ? iface
             : nullptr;
}
