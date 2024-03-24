
#include <iostream>
#include <ostream>
#include <regex>
#include <string>

#include "include/axaccess/mac/axapi_node.h"
#include "include/axaccess/mac/mac_data_types.h"

using mac_inspect::AXAPINode;
using mac_inspect::ValueType;

void print_usage(std::string& program_name) {
  std::cout << "Usage: " << program_name << " <pid>\n";
}

static void print_attributes(AXAPINode node) {
  std::cout << node.CopyStringAttributeValue("AXRole");

  if (node.HasAttribute("AXTitle")) {
    std::string title = node.CopyStringAttributeValue("AXTitle");
    if (!title.empty())
      std::cout << " \"" << node.CopyStringAttributeValue("AXTitle") << "\"";
  }

  std::cout << "\n";
}

static void print_node(AXAPINode node, int level) {
  if (!node.HasAttribute("AXRole"))
    return;

  for (auto i = 0; i < level; i++)
    std::cout << "--";

  std::cout << "> ";

  try {
    print_attributes(node);
  } catch (std::runtime_error e) {
    std::cout << " (error: " << e.what() << ")\n";
  }

  if (!node.HasAttribute("AXChildren"))
    return;

  int32_t child_count = node.GetListAttributeValueCount("AXChildren");
  for (auto i = 0; i < child_count; i++) {
    try {
      auto child = node.CopyNodeListAttributeValueAtIndex("AXChildren", i);
      print_node(child, level + 1);
    } catch (...) {
      // Sometimes getting a child produces kAXErrorFailure for totally opaque
      // reasons, yay
      continue;
    }
  }
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

  AXAPINode root = AXAPINode::CreateForPID(pid);
  try {
    print_node(root, 0);
  } catch (std::runtime_error e) {
    std::cerr << "\n\n" << e.what();
    return -1;
  } catch (std::invalid_argument e) {
    std::cerr << "\n\n" << e.what();
    return -1;
  }

    return 0;
}
