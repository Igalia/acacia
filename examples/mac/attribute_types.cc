#include "include/axaccess/mac/axapi_node.h"

#include <cstdlib>
#include <iostream>
#include <map>
#include <regex>
#include <string>

using std::map;
using std::string;
using std::vector;

using mac_inspect::AXAPINode;
using mac_inspect::ValueType;
using mac_inspect::ValueTypeToString;

void print_usage(std::string& program_name) {
  std::cout << "Usage: " << program_name << " <pid>\n";
}

void CollectAttributeTypes(AXAPINode node,
                           map<string, string>& attribute_types) {
  vector<string> attributes = node.CopyAttributeNames();
  for (const string& attribute : attributes) {
    // TODO: Some attributes map to *multiple* types. This should map to a
    // vector of string, and only skip if we've already logged the type.
    if (attribute_types.count(attribute) > 0)
      continue;

    ValueType type = node.GetAttributeValueType(attribute);

    if (type != ValueType::NOT_PRESENT) {
      if (type == ValueType::LIST) {
        ValueType element_type = node.GetListAttributeElementType(attribute);
        if (element_type != ValueType::UNKNOWN) {
          string list_type = ValueTypeToString(type) + "<" +
                             ValueTypeToString(element_type) + ">";
          attribute_types[attribute] = list_type;
        }
      } else {
        attribute_types[attribute] = ValueTypeToString(type);
      }
    }
  }

  if (!node.HasAttribute("AXChildren"))
    return;

  try {
    vector<AXAPINode> children = node.CopyNodeListAttributeValue("AXChildren");
    for (AXAPINode& child : children)
      CollectAttributeTypes(child, attribute_types);
  } catch (...) {
  }
}

void LogAllAttributeValueTypes(pid_t pid) {
  AXAPINode application = AXAPINode::CreateForPID(pid);
  map<string, string> attribute_types;

  CollectAttributeTypes(application, attribute_types);

  std::cout << "\n\nAttributes:\n-----------\n";
  for (const auto& [attribute, type] : attribute_types)
    std::cout << attribute << ": " << type << "\n";
}

int main(int argc, char** argv) {
  std::string program_name(argv[0]);

  if (argc != 2) {
    print_usage(program_name);
    return 1;
  }

  std::string pid_string(argv[1]);
  std::regex number_regex("\\d+");
  if (!std::regex_match(pid_string, number_regex)) {
    print_usage(program_name);
    return 1;
  }

  const int pid = std::stoi(pid_string);
  std::cerr << "Got PID: " << pid << "\n";

  LogAllAttributeValueTypes((pid_t)pid);

  return 0;
}
