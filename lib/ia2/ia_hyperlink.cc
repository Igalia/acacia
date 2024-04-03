#include "acacia/ia2/ia_hyperlink.h"

#include <stdexcept>

#include "acacia/ia2/win_utils.h"

std::string IAHyperlink::toString() {
  if (isNull()) {
    return "Hyperlink: Not implemented";
  }

  // Typically there is one target, at least in the Linux equivalent API.
  // The maximum index is, according to the documentation, the number of
  // actions returned via IAccessibleAction. For now, assume one target.
  std::string result = "Hyperlink: '" + getAnchorTarget(0) +
                       "' startIndex=" + std::to_string(getStartIndex());
  return result;
}

long IAHyperlink::getStartIndex() {
  if (iface_) {
    long index;
    HRESULT hr = iface_->get_startIndex(&index);
    if (FAILED(hr)) {
      throw std::runtime_error("ERROR: get_startIndex failed: " +
                               HResultErrorToString(hr));
    }
    return index;
  }
  return -1;
}

long IAHyperlink::getEndIndex() {
  if (iface_) {
    long index;
    HRESULT hr = iface_->get_endIndex(&index);
    if (FAILED(hr)) {
      throw std::runtime_error("ERROR: get_endIndex failed: " +
                               HResultErrorToString(hr));
    }
    return index;
  }
  return -1;
}

std::string IAHyperlink::getAnchorTarget(long index) {
  if (iface_) {
    VARIANT variant_result;
    HRESULT hr = iface_->get_anchorTarget(index, &variant_result);
    if (FAILED(hr)) {
      throw std::runtime_error("ERROR: get_anchorTarget failed: " +
                               HResultErrorToString(hr));
    }
    std::string str_result = VariantToString(variant_result);
    VariantClear(&variant_result);
    return str_result;
  }
  return std::string();
}
