#include "axaccess/ia2/ia_hyperlink.h"

#include "axaccess/ia2/win_utils.h"

using namespace win_utils;

IAHyperlink::IAHyperlink(IANode node) {
  if (auto service_provider = node.GetServiceProvider()) {
    service_provider->QueryService(IID_IAccessible, IID_PPV_ARGS(&iface_));
  }
}

std::string IAHyperlink::GetProperties() {
  if (!iface_) {
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
  if (iface_) {
    long index;
    if (SUCCEEDED(iface_->get_startIndex(&index))) {
      return index;
    }
  }
  return -1;
}

long IAHyperlink::get_endIndex() {
  if (iface_) {
    long index;
    if (SUCCEEDED(iface_->get_endIndex(&index))) {
      return index;
    }
  }
  return -1;
}

std::string IAHyperlink::get_anchorTarget(long index) {
  if (iface_) {
    VARIANT variant_result;
    if (SUCCEEDED(iface_->get_anchorTarget(index, &variant_result))) {
      std::string str_result = VariantToString(variant_result);
      VariantClear(&variant_result);
      return str_result;
    }
  }
  return std::string();
}
