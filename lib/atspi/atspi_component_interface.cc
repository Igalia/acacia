#include <axaccess/atspi/atspi_component_interface.h>

#include <assert.h>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>

std::string AtspiComponentInterface::to_string() const {
  if (is_null()) {
    return "Not implemented";
  }

  std::pair<int, int> position = get_position();
  std::pair<int, int> size = get_size();
  std::string result = "x:" + std::to_string(position.first) + ", " +
                       "y:" + std::to_string(position.second) + ", " +
                       "width:" + std::to_string(size.first) + ", " +
                       "height:" + std::to_string(size.second);
  return result;
}

std::pair<int, int> AtspiComponentInterface::get_position() const {
  if (is_null()) {
    return std::make_pair(0, 0);
  }

  // N.B. We always ask for WINDOW coordinates because in Wayland we cannot get
  // the SCREEN coordinates. And some implementations (e.g. GTK4) don't
  // implement support for SCREEN coordinates even in X11.
  GError* error = nullptr;
  AtspiPoint* position =
      atspi_component_get_position(interface_, ATSPI_COORD_TYPE_WINDOW, &error);
  if (error) {
    std::string err_msg = error->message;
    g_error_free(error);
    throw std::runtime_error(err_msg);
  }
  std::pair<int, int> result = std::make_pair(position->x, position->y);
  g_free(position);
  return result;
}

std::pair<int, int> AtspiComponentInterface::get_size() const {
  if (is_null()) {
    return std::make_pair(0, 0);
  }

  GError* error = nullptr;
  AtspiPoint* size = atspi_component_get_size(interface_, &error);
  if (error) {
    std::string err_msg = error->message;
    g_error_free(error);
    throw std::runtime_error(err_msg);
  }

  // In the context of size, x holds width; y height.
  std::pair<int, int> result = std::make_pair(size->x, size->y);
  g_free(size);
  return result;
}
