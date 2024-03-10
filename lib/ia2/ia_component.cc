#include "axaccess/ia2/ia_component.h"

#include <sstream>

namespace {
std::string ColorToString(IA2Color color) {
  std::stringstream ss;
  ss << std::hex << color;
  return ss.str();
}
}  // namespace

std::string IAComponent::GetProperties() {
  auto iface = QueryInterface();
  if (!iface) {
    return std::string();
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
  if (auto iface = QueryInterface()) {
    IA2Color color;
    if (SUCCEEDED(iface->get_background(&color))) {
      return ColorToString(color);
    }
  }
  return std::string();
}

std::string IAComponent::get_foreground() {
  if (auto iface = QueryInterface()) {
    IA2Color color;
    if (SUCCEEDED(iface->get_foreground(&color))) {
      return ColorToString(color);
    }
  }
  return std::string();
}

std::pair<long, long> IAComponent::get_locationInParent() {
  if (auto iface = QueryInterface()) {
    LONG x, y;
    if (SUCCEEDED(iface->get_locationInParent(&x, &y))) {
      return std::make_pair(x, y);
    }
  }
  return std::make_pair(-1, -1);
}

Microsoft::WRL::ComPtr<IAccessibleComponent> IAComponent::QueryInterface() {
  if (node_.IsNull() || !node_.GetIAccessible()) {
    return nullptr;
  }

  Microsoft::WRL::ComPtr<IAccessibleComponent> iface;
  Microsoft::WRL::ComPtr<IServiceProvider> service_provider;
  HRESULT hr =
      node_.GetIAccessible()->QueryInterface(IID_PPV_ARGS(&service_provider));
  return SUCCEEDED(service_provider->QueryService(IID_IAccessible,
                                                  IID_PPV_ARGS(&iface)))
             ? iface
             : nullptr;
}
