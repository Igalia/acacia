
#include <iostream>
#include <ostream>
#include <regex>
#include <string>

#include "include/acacia/mac/axapi_node.h"
#include "include/acacia/mac/mac_data_types.h"

using acacia::AXAPINode;
using acacia::ValueType;

void print_usage(std::string& program_path) {
  std::string program_name = program_path;
  size_t pos = program_name.find_last_of("/");
  if (pos != std::string::npos) {
    program_name = program_name.substr(pos + 1);
  }

  std::cout << "Usage:\n";
  std::cout << "  " << program_name << " --name=NAME\n";
  std::cout << "  " << program_name << " --pid=PID\n";
}

static void print_attributes(AXAPINode node) {
  std::cout << node.getStringValue("AXRole");

  if (node.hasAttribute("AXTitle")) {
    std::string title = node.getStringValue("AXTitle");
    if (!title.empty())
      std::cout << " \"" << node.getStringValue("AXTitle") << "\"";
  }

  std::cout << "\n";
}

static void print_node(AXAPINode node, int level) {
  if (!node.hasAttribute("AXRole"))
    return;

  for (auto i = 0; i < level; i++)
    std::cout << "--";

  std::cout << "> ";

  try {
    print_attributes(node);
  } catch (std::runtime_error e) {
    std::cout << " (error: " << e.what() << ")\n";
  }

  if (!node.hasAttribute("AXChildren"))
    return;

  int32_t child_count = node.getListElementCount("AXChildren");
  for (auto i = 0; i < child_count; i++) {
    try {
      auto child = node.getNodeListValueAtIndex("AXChildren", i);
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

  AXAPINode root;
  std::string arg_string(argv[1]);
  std::regex arg_regex("--(\\w+)=(\\w+)");
  std::smatch m;
  if (!std::regex_match(arg_string, m, arg_regex)) {
    print_usage(program_name);
    return 1;
  }

  std::string flag = m[1];
  std::string value = m[2];
  if (flag == "pid") {
    const int pid = std::stoi(value);
    root = acacia::findRootAXAPINodeForPID(pid);
    if (root.isNull()) {
      std::cerr << "No program for PID " << pid << ".\n";
      return 0;
    }
  } else if (flag == "name") {
    root = acacia::findRootAXAPINodeForName(value);
    if (root.isNull()) {
      std::cerr << "No program matching name \"" << value << "\".\n";
      return 0;
    }
  } else {
    print_usage(program_name);
    return 1;
  }

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
