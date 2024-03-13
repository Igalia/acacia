#include <iostream>
#include <ostream>
#include <string>

#include <axaccess/atspi/linux_utils.h>

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
  if (error)
    goto handle_gerror;

  for (int i = 0; i < child_count; i++) {
    AtspiAccessible* child =
      atspi_accessible_get_child_at_index(desktop, i, &error);
    if (error)
      goto handle_gerror;

    pid_t application_pid = atspi_accessible_get_process_id(child, &error);
    if (error)
      goto handle_gerror;

    if (pid == application_pid) {
      return std::make_unique<AtspiNode>(AtspiNode(child));
    }

    g_object_unref(child);
  }
  return nullptr;

 handle_gerror:
  std::string err_msg = error->message;
  g_error_free(error);
  throw std::runtime_error(err_msg);
  return nullptr;
}
