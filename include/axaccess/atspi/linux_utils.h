#ifndef LIB_ATSPI_LINUX_UTILS_H_
#define LIB_ATSPI_LINUX_UTILS_H_

#include <memory>
#include <string>

#include "atspi_node.h"

/** @defgroup atspi AT-SPI (Linux)
 *  AT-SPI based API for Linux
 *  @{
 */
/** @} */ // end of atspi group

/**
 * Returns the root node of the accessible tree of a running application
 * referenced by pid.
 * @ingroup atspi
 *
 * @param pid: The process id of the running application.
 *
 * @returns A unique pointer wrapping an AtspiNode.
 */
AtspiNodePtr find_root_accessible_from_pid(const int pid);

#endif  // LIB_ATSPI_LINUX_UTILS_H_
