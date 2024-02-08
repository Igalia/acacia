#include "include/axaccess/mac/axapi_node.h"

#import <Foundation/Foundation.h>

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using std::cerr;

namespace mac_inspect {

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

CFStringRef StdStringToCFStringRef(const std::string& std_string) {
  return CFStringCreateWithCString(kCFAllocatorDefault, std_string.c_str(),
                                   [NSString defaultCStringEncoding]);
}

AXAPINode::AXAPINode() {}

AXAPINode::AXAPINode(AXUIElementRef ax_ui_element)
    : ax_ui_element_((AXUIElementRef)CFRetain(ax_ui_element)) {}

AXAPINode AXAPINode::CreateForPID(int pid) {
  AXUIElementRef root_ax_ui_element = AXUIElementCreateApplication((pid_t)pid);
  return AXAPINode(root_ax_ui_element);
}

std::vector<std::string> AXAPINode::CopyAttributeNames() const {
  CFArrayRef cf_attributes = NULL;
  AXError err = AXUIElementCopyAttributeNames(ax_ui_element_, &cf_attributes);
  std::vector<std::string> attributes;
  if (err == kAXErrorSuccess) {
    for (CFIndex i = 0; i < CFArrayGetCount(cf_attributes); ++i) {
      CFStringRef cf_attribute =
          (CFStringRef)CFArrayGetValueAtIndex(cf_attributes, i);
      attributes.push_back(CFStringRefToStdString(cf_attribute));
    }
  }

  // TODO: can we do something clever with scoping to automatically do these
  // releases?
  if (cf_attributes)
    CFRelease(cf_attributes);
  if (err) {
    throw std::invalid_argument(
        "Attempting to copy attribute names produced error code " +
        std::to_string(err));
  }
  return attributes;
}

std::string AXAPINode::CopyStringAttributeValue(
    const std::string& attribute) const {
  CFStringRef cf_attribute = StdStringToCFStringRef(attribute);
  CFTypeRef cf_value = NULL;
  AXError err =
      AXUIElementCopyAttributeValue(ax_ui_element_, cf_attribute, &cf_value);
  std::string value;
  // TODO: better handling of attributes which return the wrong type
  if (err == kAXErrorSuccess && CFGetTypeID(cf_value) == CFStringGetTypeID()) {
    value = CFStringRefToStdString((CFStringRef)cf_value);
  } else if (err == kAXErrorNoValue) {
    return "";
  }

  if (cf_attribute)
    CFRelease(cf_attribute);
  if (cf_value)
    CFRelease(cf_value);
  if (err) {
    std::string ax_err;
    switch (err) {
      case kAXErrorAttributeUnsupported:
        ax_err = "kAXErrorAttributeUnsupported";
        break;
      case kAXErrorNoValue:
        ax_err = "kAXErrorNoValue";
        break;
      case kAXErrorIllegalArgument:
        ax_err = "kAXErrorIllegalArgument";
        break;
      case kAXErrorCannotComplete:
        ax_err = "kAXErrorCannotComplete";
        break;
      case kAXErrorNotImplemented:
        ax_err = "kAXErrorNotImplemented";
        break;
      default:
        ax_err = std::to_string(err);
    }
    throw std::invalid_argument("Attempting to copy value for attribute " +
                                attribute + " produced error code " + ax_err);
  }
  return value;
}

std::vector<AXAPINode> AXAPINode::CopyNodeListAttributeValue(
    const std::string& attribute) const {
  CFStringRef cf_attribute = StdStringToCFStringRef(attribute);
  CFTypeRef cf_value;
  AXError err =
      AXUIElementCopyAttributeValue(ax_ui_element_, cf_attribute, &cf_value);

  // TODO: better handling of attributes which return the wrong type
  std::vector<AXAPINode> value;
  if (err == kAXErrorSuccess && CFGetTypeID(cf_value) == CFArrayGetTypeID()) {
    CFArrayRef cf_value_array = (CFArrayRef)cf_value;
    for (CFIndex i = 0; i < CFArrayGetCount(cf_value_array); ++i) {
      CFTypeRef cf_ith_value =
          (CFTypeRef)CFArrayGetValueAtIndex(cf_value_array, i);
      if (CFGetTypeID(cf_ith_value) == AXUIElementGetTypeID()) {
        value.push_back(AXAPINode((AXUIElementRef)cf_ith_value));
      }
    }
  }

  if (cf_attribute)
    CFRelease(cf_attribute);
  if (cf_value)
    CFRelease(cf_value);
  if (err) {
    std::string ax_err;
    switch (err) {
      case kAXErrorAttributeUnsupported:
        ax_err = "kAXErrorAttributeUnsupported";
        break;
      case kAXErrorNoValue:
        ax_err = "kAXErrorNoValue";
        break;
      case kAXErrorIllegalArgument:
        ax_err = "kAXErrorIllegalArgument";
        break;
      case kAXErrorCannotComplete:
        ax_err = "kAXErrorCannotComplete";
        break;
      case kAXErrorNotImplemented:
        ax_err = "kAXErrorNotImplemented";
        break;
      default:
        ax_err = std::to_string(err);
    }
    throw std::invalid_argument("Attempting to copy value for attribute " +
                                attribute + " produced error code " + ax_err);
  }
  return value;
}

}  // namespace mac_inspect
