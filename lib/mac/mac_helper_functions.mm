#include "lib/mac/mac_helper_functions.h"

#include <iostream>

#include <ApplicationServices/ApplicationServices.h>
#include <Foundation/Foundation.h>

#include "lib/mac/scoped_cf_type_ref.h"

using std::cerr;

namespace acacia {

ValueType DeduceValueType(CFTypeRef cf_value, const std::string& attribute) {
  CFTypeID type_id = CFGetTypeID(cf_value);

  if (type_id == CFBooleanGetTypeID())
    return ValueType::BOOLEAN;

  if (type_id == CFNumberGetTypeID()) {
    if (CFNumberIsFloatType((CFNumberRef)cf_value))
      return ValueType::FLOAT;

    return ValueType::INT;
  }

  if (type_id == CFStringGetTypeID())
    return ValueType::STRING;

  if (type_id == CFURLGetTypeID())
    return ValueType::URL;

  if (type_id == AXUIElementGetTypeID())
    return ValueType::NODE;

  if (type_id == CFArrayGetTypeID())
    return ValueType::LIST;

  if (type_id == AXValueGetTypeID()) {
    AXValueType ax_value_type = AXValueGetType((AXValueRef)cf_value);
    switch (ax_value_type) {
      case kAXValueCGPointType:
        return ValueType::POINT;
      case kAXValueCGSizeType:
        return ValueType::SIZE;
      case kAXValueCGRectType:
        return ValueType::RECT;
      case kAXValueCFRangeType:
        return ValueType::RANGE;
      default:
        return ValueType::UNKNOWN;
    }
  }

  if (type_id == AXTextMarkerGetTypeID())
    return ValueType::TEXTMARKER;

  if (type_id == AXTextMarkerRangeGetTypeID())
    return ValueType::TEXTMARKERRANGE;

  if (type_id == CFDataGetTypeID())
    return ValueType::DATA;

  if (type_id == CFDictionaryGetTypeID())
    return ValueType::DICTIONARY;

  if (attribute != "") {
    CFStringRef description = CFCopyTypeIDDescription(type_id);
    cerr << "Unknown type: " << type_id << " ("
         << CFStringRefToStdString(description) << ") for attribute "
         << attribute << "\n";
  }
  return ValueType::UNKNOWN;
}

const std::string CFStringRefToStdString(CFStringRef cf_string) {
  if (cf_string == nullptr)
    return "";

  const char* chars =
      CFStringGetCStringPtr(cf_string, CFStringGetSystemEncoding());
  if (!chars) {
    // CFStringRef can secretly be an NSString, in which case
    // CFStringGetCStringPtr doesn't work.
    NSString* ns_string = (__bridge NSString*)cf_string;
    const char* ns_chars =
        [ns_string cStringUsingEncoding:[NSString defaultCStringEncoding]];
    chars = ns_chars ? ns_chars : "";
  }
  return std::string(chars);
}

ScopedCFTypeRef<CFStringRef> StdStringToCFStringRef(
    const std::string& std_string) {
  return ScopedCFTypeRef<CFStringRef>(
      CFStringCreateWithCString(kCFAllocatorDefault, std_string.c_str(),
                                [NSString defaultCStringEncoding]));
}

std::string AXErrorToString(AXError err) {
  switch (err) {
    case kAXErrorAPIDisabled:
      return "kAXErrorAPIDisabled";
    case kAXErrorActionUnsupported:
      return "kAXErrorActionUnsupported";
    case kAXErrorAttributeUnsupported:
      return "kAXErrorAttributeUnsupported";
    case kAXErrorCannotComplete:
      return "kAXErrorCannotComplete";
    case kAXErrorFailure:
      return "kAXErrorFailure";
    case kAXErrorIllegalArgument:
      return "kAXErrorIllegalArgument";
    case kAXErrorInvalidUIElement:
      return "kAXErrorInvalidUIElement";
    case kAXErrorInvalidUIElementObserver:
      return "kAXErrorInvalidUIElementObserver";
    case kAXErrorNoValue:
      return "kAXErrorNoValue";
    case kAXErrorNotEnoughPrecision:
      return "kAXErrorNotEnoughPrecision";
    case kAXErrorNotImplemented:
      return "kAXErrorNotImplemented";
    case kAXErrorNotificationAlreadyRegistered:
      return "kAXErrorNotificationAlreadyRegistered";
    case kAXErrorNotificationNotRegistered:
      return "kAXErrorNotificationNotRegistered";
    case kAXErrorNotificationUnsupported:
      return "kAXErrorNotificationUnsupported";
    default:
      return std::to_string(err);
  }
}

}  // namespace acacia
