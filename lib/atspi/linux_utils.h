#include <memory>
#include <string>

#include <lib/atspi/atspi_wrapper.h>

using AtspiWrapperPtr = std::unique_ptr<AtspiWrapper>;

AtspiWrapperPtr find_root_accessible_from_pid(const int pid);

