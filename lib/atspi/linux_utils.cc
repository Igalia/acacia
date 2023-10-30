#include <iostream>
#include <ostream>
#include <string>

#include <lib/atspi/linux_utils.h>

#define CHECK_ATSPI_ERROR_NULLPTR(error) \
  if (error) {                           \
    std::cerr << error->message;         \
    g_clear_error(&error);               \
    return nullptr;                      \
  }

AtspiNodePtr find_root_accessible_from_pid(const int pid) {
  AtspiAccessible* desktop = atspi_get_desktop(0);

  GError* error = nullptr;
  int child_count = atspi_accessible_get_child_count(desktop, &error);
  CHECK_ATSPI_ERROR_NULLPTR(error);

  for (int i = 0; i < child_count; i++) {
    AtspiAccessible* child =
        atspi_accessible_get_child_at_index(desktop, i, &error);
    CHECK_ATSPI_ERROR_NULLPTR(error);

    uint application_pid = atspi_accessible_get_process_id(child, &error);
    CHECK_ATSPI_ERROR_NULLPTR(error)
    if (pid == application_pid) {
      return std::make_unique<AtspiNode>(AtspiNode(child));
    }
  }
  return nullptr;
}
