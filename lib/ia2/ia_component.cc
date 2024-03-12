#include "axaccess/ia2/ia_component.h"

#include <sstream>

namespace {
std::string ColorToString(IA2Color color) {
  std::stringstream ss;
  ss << std::hex << color;
  return ss.str();
}
}  // namespace

IAComponent::IAComponent(IANode node) {
  if (auto service_provider = node.GetServiceProvider()) {
    service_provider->QueryService(IID_IAccessible, IID_PPV_ARGS(&iface_));
  }
}

std::string IAComponent::GetProperties() {
  if (IsNull()) {
    return "Component: Not implemented";
  }

  std::string result = "Component:";
  std::pair<long, long> location = get_locationInParent();
  result += " x:" + std::to_string(location.first) +
            " y:" + std::to_string(location.second);
  result += " foreground:" + get_foreground();
  result += " background:" + get_background();

  return result;
}

std::string IAComponent::get_background() {
  if (iface_) {
    IA2Color color;
    if (SUCCEEDED(iface_->get_background(&color))) {
      return ColorToString(color);
    }
  }
  return std::string();
}

std::string IAComponent::get_foreground() {
  if (iface_) {
    IA2Color color;
    if (SUCCEEDED(iface_->get_foreground(&color))) {
      return ColorToString(color);
    }
  }
  return std::string();
}

std::pair<long, long> IAComponent::get_locationInParent() {
  if (iface_) {
    LONG x, y;
    if (SUCCEEDED(iface_->get_locationInParent(&x, &y))) {
      return std::make_pair(x, y);
    }
  }
  return std::make_pair(-1, -1);
}
