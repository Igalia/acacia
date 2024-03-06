#include <iostream>
#include <map>
#include <ostream>
#include <regex>
#include <stdexcept>
#include <string>

#include "include/axaccess/ia2/ia2_node.h"
#include "include/axaccess/ia2/win_utils.h"

using namespace win_utils;

void print_usage(std::string& program_path) {
  std::string program_name = program_path;
  size_t pos = program_name.find_last_of("\\");
  if (pos != std::string::npos) {
    program_name = program_name.substr(pos + 1);
  }

  std::cout << "Usage:\n";
  std::cout << "  " << program_name << " --name=NAME\n";
  std::cout << "  " << program_name << " --pid=PID\n";
  std::cout << "  " << program_name << " --name=NAME --pid=PID\n";
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

std::map<std::string, std::string> parse_arguments(int argc, char** argv) {
  std::map<std::string, std::string> argument_map;
  for (int i = 1; i < argc; ++i) {
    std::string arg(argv[i]);
    size_t pos = arg.find('=');
    if (pos != std::string::npos) {
      // Argument format is --key=value
      std::string key = arg.substr(0, pos);
      std::string value = arg.substr(pos + 1);
      argument_map[key] = value;
    } else {
      // Argument format is --key value, assuming there is a value.
      std::string key = arg;
      if (i + 1 < argc) {
        argument_map[key] = argv[++i];
      }
    }
  }

  return argument_map;
}

int main(int argc, char** argv) {
  std::string program_name(argv[0]);
  auto args = parse_arguments(argc, argv);

  std::string name;
  if (args.find("--name") != args.end()) {
    name = args["--name"];
  }

  int pid = 0;
  if (args.find("--pid") != args.end()) {
    std::string pid_string = args["--pid"];
    std::regex number_regex("\\d+");
    if (std::regex_match(pid_string, number_regex)) {
      pid = std::stoi(pid_string);
    }
  }

  if (name.empty() && !pid) {
    print_usage(program_name);
    return 1;
  }

  HRESULT hr = CoInitialize(nullptr);
  if (FAILED(hr)) {
    throw std::runtime_error("CoInitialize failed with error code: " +
                             HResultErrorToString(hr));
  }

  int exit_code = 0;
  if (IA2NodePtr root = IA2Node::CreateRootForName(name, pid)) {
    print_node(root, 0);
  } else {
    std::cerr << "ERROR: Could not find match for";
    if (!name.empty()) {
      std::cerr << " name: '" << name << "'";
    }
    if (pid) {
      std::cerr << " PID: " << pid;
    }
    std::cerr << std::endl;
    exit_code = -1;
  }

  CoUninitialize();
  return exit_code;
}
