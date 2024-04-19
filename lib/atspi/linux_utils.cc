#include <iostream>
#include <ostream>
#include <string>

#include <acacia/atspi/linux_utils.h>

#include "../utils.h"
#include "scoped_g_lib_ptr.h"

namespace acacia {

using ScopedCStr = ScopedGLibPtr<char>;
using ScopedGError = ScopedGTypePtr<GError, &g_error_free>;

AtspiNode findRootAtspiNodeForPID(const int pid) {
  ScopedGObjectPtr<AtspiAccessible> desktop(atspi_get_desktop(0));

  ScopedGError error;
  GError* error_ptr = error.get();
  int child_count = atspi_accessible_get_child_count(desktop.get(), &error_ptr);
  if (error_ptr) {
    std::string err_msg = error->message;
    throw std::runtime_error(err_msg);
  }

  for (int i = 0; i < child_count; i++) {
    ScopedGObjectPtr<AtspiAccessible> child(
        atspi_accessible_get_child_at_index(desktop.get(), i, &error_ptr));
    if (error_ptr) {
      std::string err_msg = error->message;
      throw std::runtime_error(err_msg);
    }

    pid_t application_pid =
        atspi_accessible_get_process_id(child.get(), &error_ptr);
    if (error_ptr) {
      std::string err_msg = error->message;
      throw std::runtime_error(err_msg);
    }

    if (pid == application_pid) {
      return AtspiNode(child.release());
    }
  }
  return AtspiNode();
}

AtspiNode findRootAtspiNodeForName(const std::string& name, const int pid) {
  ScopedGObjectPtr<AtspiAccessible> desktop(atspi_get_desktop(0));
  std::string lower_name = lower(name);

  ScopedGError error;
  GError* error_ptr = error.get();
  int child_count = atspi_accessible_get_child_count(desktop.get(), &error_ptr);
  if (error_ptr) {
    std::string err_msg = error->message;
    throw std::runtime_error(err_msg);
  }

  for (int i = 0; i < child_count; i++) {
    ScopedGObjectPtr<AtspiAccessible> child(
        atspi_accessible_get_child_at_index(desktop.get(), i, &error_ptr));
    if (error_ptr) {
      std::string err_msg = error->message;
      throw std::runtime_error(err_msg);
    }

    ScopedCStr child_name(atspi_accessible_get_name(child.get(), &error_ptr));
    if (error_ptr) {
      std::string err_msg = error->message;
      throw std::runtime_error(err_msg);
    }

    std::string app_name = lower(std::string(child_name.get()));
    if (app_name.find(lower_name) != std::string::npos) {
      if (!pid) {
        return AtspiNode(child.release());
      }

      pid_t application_pid =
          atspi_accessible_get_process_id(child.get(), &error_ptr);
      if (error_ptr) {
        std::string err_msg = error->message;
        throw std::runtime_error(err_msg);
      }

      if (pid == application_pid) {
        return AtspiNode(child.release());
      }
    }
  }
  return AtspiNode();
}
}  // namespace acacia
