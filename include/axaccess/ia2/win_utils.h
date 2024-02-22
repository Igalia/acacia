#ifndef LIB_IA2_WIN_UTILS_H_
#define LIB_IA2_WIN_UTILS_H_

#include <memory>
#include <string>
#include "axaccess/export.h"

#include "ia2_node.h"

AXA_EXPORT IA2NodePtr find_root_accessible_from_pid(const int pid);

#endif  // LIB_IA2_WIN_UTILS_H_
