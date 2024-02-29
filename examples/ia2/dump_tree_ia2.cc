#include <iostream>
#include <ostream>
#include <regex>
#include <string>

#include "include/axaccess/ia2/ia2_node.h"

void print_usage(std::string& program_name) {
  std::cout << "Usage: " << program_name << " <pid>\n";
}

static void print_node(IA2NodePtr& node, int level) {
  for (auto i = 0; i < level; i++)
    std::cout << "--";
  std::cout << "> ";

  std::string msaa_role = node->get_accRole();
  std::string ia2_role = node->ia2_role();
  if (ia2_role.empty() || ia2_role == msaa_role)
    std::cout << msaa_role;
  else
    std::cout << ia2_role << " " << msaa_role;

  std::string node_name = node->get_accName();
  if (!node_name.empty())
    std::cout << " (" << node_name << ")";
  std::cout << "\n";

  int32_t child_count = node->get_accChildCount();
  if (child_count < 0)
    return;

  for (auto i = 0; i < child_count; i++) {
    auto child = node->AccessibleChildAt(i);
    print_node(child, level + 1);
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

  // TODO: experiment with where to put coinitialize and couninitialize. #93
  CoInitialize(nullptr);

  const int pid = std::stoi(pid_string);
  std::cout << "Got PID: " << pid << "\n";
  IA2NodePtr root = IA2Node::CreateForPID(pid);
  if (!root) {
    std::cerr << "No accessible root found at pid " << pid << "\n";
    return -1;
  }

  print_node(root, 0);

  // TODO: experiment with where to put coinitialize and couninitialize.
  // Calling CoUninitialize here causes a seg fault because there is still a
  // reference to a interface on the stack. CoUninitialize();
  return 0;
}
