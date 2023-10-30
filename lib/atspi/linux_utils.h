#ifndef LIB_ATSPI_LINUX_UTILS_H_
#define LIB_ATSPI_LINUX_UTILS_H_

#include <memory>
#include <string>

#include <lib/atspi/atspi_node.h>

using AtspiNodePtr = std::unique_ptr<AtspiNode>;

AtspiNodePtr find_root_accessible_from_pid(const int pid);

#endif // LIB_ATSPI_LINUX_UTILS_H_
