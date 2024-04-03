#include "acacia/ia2/ia_component.h"

#include <sstream>
#include <stdexcept>

#include "acacia/ia2/win_utils.h"

namespace {
std::string ColorToString(IA2Color color) {
  std::stringstream ss;
  ss << std::hex << color;
  return ss.str();
}
}  // namespace

std::string IAComponent::toString() {
  if (isNull()) {
    return "Component: Not implemented";
  }

  std::string result = "Component:";
  std::pair<long, long> location = getLocationInParent();
  result += " x:" + std::to_string(location.first) +
            " y:" + std::to_string(location.second);
  result += " foreground:" + getForeground();
  result += " background:" + getBackground();

  return result;
}

std::string IAComponent::getBackground() {
  if (iface_) {
    IA2Color color;
    HRESULT hr = iface_->get_background(&color);
    if (FAILED(hr)) {
      throw std::runtime_error("ERROR: get_background failed: " +
                               HResultErrorToString(hr));
    }
    return ColorToString(color);
  }
  return std::string();
}

std::string IAComponent::getForeground() {
  if (iface_) {
    IA2Color color;
    HRESULT hr = iface_->get_foreground(&color);
    if (FAILED(hr)) {
      throw std::runtime_error("ERROR: get_foreground failed: " +
                               HResultErrorToString(hr));
    }
    return ColorToString(color);
  }
  return std::string();
}

std::pair<long, long> IAComponent::getLocationInParent() {
  if (iface_) {
    LONG x, y;
    HRESULT hr = iface_->get_locationInParent(&x, &y);
    if (FAILED(hr)) {
      throw std::runtime_error("ERROR: get_locationInParent failed: " +
                               HResultErrorToString(hr));
    }
    return std::make_pair(x, y);
  }
  return std::make_pair(-1, -1);
}
