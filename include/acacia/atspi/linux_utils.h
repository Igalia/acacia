#ifndef LIB_ATSPI_LINUX_UTILS_H_
#define LIB_ATSPI_LINUX_UTILS_H_

#include <memory>
#include <string>

#include "atspi_node.h"

/** @defgroup atspi AT-SPI (Linux)
 *  AT-SPI based API for Linux
 *  @{
 */
/** @} */  // end of atspi group

/**
 * Returns the root node of the accessible tree of a running application
 * referenced by pid.
 * @ingroup atspi
 *
 * @param pid: The process id of the running application.
 *
 * @returns An @ref AtspiNode representing the root accessibility object for the
 * application with the given PID, or a null AtspiNode if no such application
 * exists.
 */
AtspiNode findRootAtspiNodeForPID(const int pid);

/**
 * Returns the root node of the accessible tree of a running application
 * referenced by the application's accessible name.
 * @ingroup atspi
 *
 * @param name: The accessible name (or substring thereof) to search for.
 * @param pid: Optional. The process id to search for.
 *
 * @returns An @ref AtspiNode representing the root accessibility object for the
 * application with the given name, or a null AtspiNode if no such application
 * exists.
 */
AtspiNode findRootAtspiNodeForName(const std::string& name, const int pid = 0);

#endif  // LIB_ATSPI_LINUX_UTILS_H_
