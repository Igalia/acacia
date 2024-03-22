#ifndef LIB_MAC_MAC_HELPER_FUNCTIONS_H_
#define LIB_MAC_MAC_HELPER_FUNCTIONS_H_

#include <string>

#include <ApplicationServices/ApplicationServices.h>
#include <Foundation/Foundation.h>

#include "include/axaccess/mac/mac_data_types.h"

namespace mac_inspect {

template <typename T>
class ScopedCFTypeRef;

const std::string CFStringRefToStdString(CFStringRef cf_string);

// This returns a ScopedCFTypeRef since the CFStringRef is obtained using
// CFStringCreateWithCString, meaning we own the CFStringRef and are responsible
// for releasing it.
ScopedCFTypeRef<CFStringRef> StdStringToCFStringRef(
    const std::string& std_string);

std::string AXErrorToString(AXError err);

// Pass attribute name to enable debug logging
ValueType DeduceValueType(CFTypeRef cf_value,
                          const std::string& attribute = "");

}  // namespace mac_inspect

#endif  // LIB_MAC_MAC_HELPER_FUNCTIONS_H_
