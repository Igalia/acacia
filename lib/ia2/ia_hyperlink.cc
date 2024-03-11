#include "axaccess/ia2/ia_hyperlink.h"

#include "axaccess/ia2/win_utils.h"

using namespace win_utils;

std::string IAHyperlink::GetProperties() {
  auto iface = QueryInterface();
  if (!iface) {
    return std::string();
  }

  // Typically there is one target, at least in the Linux equivalent API.
  // The maximum index is, according to the documentation, the number of
  // actions returned via IAccessibleAction. For now, assume one target.
  std::string result = "Hyperlink: '" + get_anchorTarget(0) +
                       "' startIndex=" + std::to_string(get_startIndex());
  return result;
}

long IAHyperlink::get_startIndex() {
  if (auto iface = QueryInterface()) {
    long index;
    if (SUCCEEDED(iface->get_startIndex(&index))) {
      return index;
    }
  }
  return -1;
}

long IAHyperlink::get_endIndex() {
  if (auto iface = QueryInterface()) {
    long index;
    if (SUCCEEDED(iface->get_endIndex(&index))) {
      return index;
    }
  }
  return -1;
}

std::string IAHyperlink::get_anchorTarget(long index) {
  if (auto iface = QueryInterface()) {
    VARIANT variant_result;
    if (SUCCEEDED(iface->get_anchorTarget(index, &variant_result))) {
      std::string str_result = VariantToString(variant_result);
      VariantClear(&variant_result);
      return str_result;
    }
  }
  return std::string();
}

Microsoft::WRL::ComPtr<IAccessibleHyperlink> IAHyperlink::QueryInterface() {
  if (node_.IsNull() || !node_.GetIAccessible()) {
    return nullptr;
  }

  Microsoft::WRL::ComPtr<IAccessibleHyperlink> iface;
  Microsoft::WRL::ComPtr<IServiceProvider> service_provider;
  HRESULT hr =
      node_.GetIAccessible()->QueryInterface(IID_PPV_ARGS(&service_provider));
  return SUCCEEDED(service_provider->QueryService(IID_IAccessible,
                                                  IID_PPV_ARGS(&iface)))
             ? iface
             : nullptr;
}
