#include <iostream>
#include <ostream>
#include <string>

#include <axaccess/atspi/linux_utils.h>

#include "../utils.h"

AtspiNode findRootAtspiNodeFromPID(const int pid) {
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
      return AtspiNode(child);
    }

    g_object_unref(child);
  }
  return AtspiNode();

handle_gerror:
  std::string err_msg = error->message;
  g_error_free(error);
  throw std::runtime_error(err_msg);
}

AtspiNode findRootAtspiNodeFromName(const std::string& name, const int pid) {
  AtspiAccessible* desktop = atspi_get_desktop(0);
  std::string lower_name = lower(name);

  GError* error = nullptr;
  int child_count = atspi_accessible_get_child_count(desktop, &error);
  if (error)
    goto handle_gerror;

  for (int i = 0; i < child_count; i++) {
    AtspiAccessible* child =
        atspi_accessible_get_child_at_index(desktop, i, &error);
    if (error)
      goto handle_gerror;

    char* child_name = atspi_accessible_get_name(child, &error);
    if (error)
      goto handle_gerror;

    std::string app_name = lower(child_name);
    g_free(child_name);
    if (app_name.find(lower_name) != std::string::npos) {
      if (!pid) {
        return AtspiNode(child);
      }

      pid_t application_pid = atspi_accessible_get_process_id(child, &error);
      if (error)
        goto handle_gerror;

      if (pid == application_pid) {
        return AtspiNode(child);
      }
    }

    g_object_unref(child);
  }
  return AtspiNode();

handle_gerror:
  std::string err_msg = error->message;
  g_error_free(error);
  throw std::runtime_error(err_msg);
}
