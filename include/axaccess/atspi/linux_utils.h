#ifndef LIB_ATSPI_LINUX_UTILS_H_
#define LIB_ATSPI_LINUX_UTILS_H_

#include <memory>
#include <string>

#include "atspi_node.h"

AtspiNodePtr find_root_accessible_from_pid(const int pid);

#endif // LIB_ATSPI_LINUX_UTILS_H_
