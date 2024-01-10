#include "include/axaccess/mac/axapi_node.h"

#import <Foundation/Foundation.h>
#include <iostream>
#include <string>
#include <vector>

namespace mac_inspect {

std::string CFStringRefToStdString(CFStringRef cf_string) {
  std::cerr << "CFStringRefToStdString\n";
  CFShowStr(cf_string);
  if (cf_string == nil)
    return "";
  std::cerr << "not nil" << "\n";
  std::cerr << "encoding is " << (CFStringGetSystemEncoding() == kCFStringEncodingMacRoman ? "kCFStringEncodingMacRoman" : "something else") << "\n";


  const char* chars = CFStringGetCStringPtr(cf_string, CFStringGetSystemEncoding());
  if (chars) {
    return std::string(chars);
  }
  std::cerr << "Couldn't get c_string - might be an NSString\n";
  NSString* ns_string = (__bridge NSString*) cf_string;
  chars = [ns_string cStringUsingEncoding:[NSString defaultCStringEncoding]];
  if (!chars) {
    return std::string();
  }
  return std::string(chars);
}

AXAPINode::AXAPINode(AXUIElementRef ax_element) : ax_element_(ax_element) {}

std::string AXAPINode::GetRole() {
  CFTypeRef cf_role = nullptr;
  if (AXUIElementCopyAttributeValue(ax_element_, kAXRoleAttribute, &cf_role) != noErr)
    return "";

  return CFStringRefToStdString((CFStringRef) cf_role);
}

std::string AXAPINode::GetTitle() {
  CFStringRef cf_title = nullptr;
  if (AXUIElementCopyAttributeValue(ax_element_, kAXTitleAttribute, (CFTypeRef*)&cf_title) != noErr)
    return "";

  return CFStringRefToStdString(cf_title);
}

std::vector<std::string> AXAPINode::GetAttributeNames() {
  std::vector<std::string> result;
  return result;
}

std::string AXAPINode::GetStringAttributeValue(std::string& attribute_name) {
  return "";
}

AXAPINode AXAPINode::createForPID(long pid) {
  AXUIElementRef axuielement = AXUIElementCreateApplication((pid_t) pid);
  return AXAPINode(axuielement);
}

}  // namespace mac_inspect