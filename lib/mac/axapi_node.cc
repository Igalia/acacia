#include "include/axaccess/mac/axapi_node.h"

#include <iostream>
#include <string>
#include <vector>

namespace mac_inspect {

std::string CFStringRefToStdString(CFStringRef cf_string) {
  std::cerr << "CFStringRefToStdString " << cf_string << "\n";
  if (cf_string == nil)
    return "";
  std::cerr << "not nil" << "\n";

  auto c_string = CFStringGetCStringPtr(cf_string, kCFStringEncodingUTF8);
  if (c_string == nullptr) {
    std::cerr << "Couldn't get c_string\n";
    return "";
  }
  std::cerr << "got c_string: " << c_string << "\n";
  std::string result(c_string);
  std::cerr << "got result" << "\n";
  return result;
}

AXAPINode::AXAPINode(AXUIElementRef ax_element) : ax_element_(ax_element) {}

std::string AXAPINode::GetRole() {
  CFStringRef cf_role = nullptr;
  if (AXUIElementCopyAttributeValue(ax_element_, kAXRoleAttribute, (CFTypeRef*)&cf_role) != noErr)
    return "";

  return CFStringRefToStdString(cf_role);
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