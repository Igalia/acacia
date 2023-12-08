#include "include/axaccess/mac/axapi_node.h"

#include <string>
#include <vector>

namespace mac_inspect {

AXAPINode::AXAPINode(AXUIElementRef ax_element) : ax_element_(ax_element) {}

std::string AXAPINode::GetRole() {
  return "";
}

std::string AXAPINode::GetTitle() {
  return "";
}

std::vector<std::string> AXAPINode::GetAttributeNames() {
  std::vector<std::string> result;
  return result;
}

std::string AXAPINode::GetStringAttributeValue(std::string& attribute_name) {
  return "";
}

AXAPINode AXAPINode::createForPID(pid_t pid) {
  AXUIElementRef axuielement = AXUIElementCreateApplication(pid);
  return AXAPINode(axuielement);
}

}  // namespace mac_inspect