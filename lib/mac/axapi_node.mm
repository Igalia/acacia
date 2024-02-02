#include "include/axaccess/mac/axapi_node.h"

#import <Foundation/Foundation.h>
#include <iostream>
#include <string>
#include <vector>

namespace mac_inspect {

std::string CFStringRefToStdString(CFStringRef cf_string) {
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

AXAPINode::AXAPINode(AXUIElementRef ax_ui_element)
    : ax_ui_element_(ax_ui_element) {}

AXAPINodePtr AXAPINode::CreateForPID(pid_t pid) {
  AXUIElementRef root_ax_ui_element = AXUIElementCreateApplication(pid);
  return AXAPINodePtr(new AXAPINode(root_ax_ui_element));
}

AXError AXAPINode::CopyAttributeNames(std::vector<std::string>& attributes) {
  CFArrayRef cf_attributes = NULL;
  AXError err = AXUIElementCopyAttributeNames(ax_ui_element_, &cf_attributes);
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
  return err;
}

AXError AXAPINode::CopyAttributeValue(const std::string& attribute,
                                      std::string& value) {
  CFStringRef cf_attribute = StdStringToCFStringRef(attribute);
  CFTypeRef cf_value;
  AXError err =
      AXUIElementCopyAttributeValue(ax_ui_element_, cf_attribute, &cf_value);

  // TODO: better handling of attributes which return the wrong type
  if (err == kAXErrorSuccess && CFGetTypeID(cf_value) == CFStringGetTypeID()) {
    value = CFStringRefToStdString((CFStringRef)cf_value);
  }

  if (cf_attribute)
    CFRelease(cf_attribute);
  if (cf_value)
    CFRelease(cf_value);
  return err;
}

AXError AXAPINode::CopyAttributeValue(const std::string& attribute,
                                      std::vector<AXAPINode>& nodes) {
  CFStringRef cf_attribute = StdStringToCFStringRef(attribute);
  CFTypeRef cf_value;
  AXError err =
      AXUIElementCopyAttributeValue(ax_ui_element_, cf_attribute, &cf_value);

  // TODO: better handling of attributes which return the wrong type
  if (err == kAXErrorSuccess && CFGetTypeID(cf_value) == CFArrayGetTypeID()) {
    CFArrayRef cf_value_array = (CFArrayRef)cf_value;
    for (CFIndex i = 0; i < CFArrayGetCount(cf_value_array); ++i) {
      CFTypeRef cf_ith_value =
          (CFTypeRef)CFArrayGetValueAtIndex(cf_value_array, i);
      if (CFGetTypeID(cf_ith_value) == AXUIElementGetTypeID()) {
        nodes.push_back(AXAPINode((AXUIElementRef)cf_ith_value));
      }
    }
  }

  if (cf_attribute)
    CFRelease(cf_attribute);
  if (cf_value)
    CFRelease(cf_value);
  return err;
}

}  // namespace mac_inspect
