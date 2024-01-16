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

AXAPINode::AXAPINode(AXUIElementRef ax_ui_element)
    : ax_ui_element_(ax_ui_element) {}

AXAPINodePtr AXAPINode::createForPID(long pid) {
  AXUIElementRef ax_ui_element = AXUIElementCreateApplication((pid_t)pid);
  return AXAPINodePtr(new AXAPINode(ax_ui_element));
}

std::string AXAPINode::GetRole() {
  CFTypeRef cf_role = nullptr;
  if (AXUIElementCopyAttributeValue(ax_ui_element_, kAXRoleAttribute,
                                    &cf_role) != kAXErrorSuccess) {
    return "";
  }

  return CFStringRefToStdString((CFStringRef)cf_role);
}

std::string AXAPINode::GetTitle() {
  CFStringRef cf_title = nullptr;
  if (AXUIElementCopyAttributeValue(ax_ui_element_, kAXTitleAttribute,
                                    (CFTypeRef*)&cf_title) != kAXErrorSuccess) {
    return "";
  }

  return CFStringRefToStdString(cf_title);
}

std::vector<std::string> AXAPINode::GetAttributeNames() {
  std::vector<std::string> result;
  return result;
}

std::string AXAPINode::GetStringAttributeValue(std::string& attribute_name) {
  return "";
}

long AXAPINode::GetChildCount() {
  CFArrayRef children_ref;
  if ((AXUIElementCopyAttributeValue(ax_ui_element_, kAXChildrenAttribute,
                                     (CFTypeRef*)&children_ref)) !=
      kAXErrorSuccess) {
    return 0;
  }
  return CFArrayGetCount(children_ref);
}

AXAPINodePtr AXAPINode::GetChildAt(long index) {
  CFArrayRef children_ref;
  if ((AXUIElementCopyAttributeValue(ax_ui_element_, kAXChildrenAttribute,
                                     (CFTypeRef*)&children_ref)) !=
      kAXErrorSuccess) {
    return nullptr;
  }
  std::cerr << "Got children " << CFArrayGetCount(children_ref) << "\n";
  AXUIElementRef child_ref =
      (AXUIElementRef)CFArrayGetValueAtIndex(children_ref, index);
  if (!child_ref)
    return nullptr;
  return AXAPINodePtr(new AXAPINode(child_ref));
}

}  // namespace mac_inspect
