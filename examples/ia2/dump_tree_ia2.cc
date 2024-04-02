#include <iostream>
#include <map>
#include <ostream>
#include <regex>
#include <string>

#include "include/axaccess/ia2/ia_2.h"
#include "include/axaccess/ia2/ia_action.h"
#include "include/axaccess/ia2/ia_component.h"
#include "include/axaccess/ia2/ia_hyperlink.h"
#include "include/axaccess/ia2/ia_node.h"
#include "include/axaccess/ia2/ia_table2.h"
#include "include/axaccess/ia2/ia_table_cell.h"
#include "include/axaccess/ia2/ia_text.h"
#include "include/axaccess/ia2/ia_value.h"
#include "include/axaccess/ia2/win_utils.h"

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

static void print_node(IANode node, int level) {
  for (auto i = 0; i < level; i++)
    std::cout << "--";
  std::cout << "> ";

  std::string msaa_role = node.getAccRole();
  IA2 ia2 = node.QueryIA2();
  std::string ia2_role = ia2.role();
  if (ia2_role.empty() || ia2_role == msaa_role)
    std::cout << msaa_role;
  else
    std::cout << ia2_role << " " << msaa_role;

  std::cout << " Name='" << node.getAccName() << "',";
  std::cout << " Description='" << node.getAccDescription() << "',";

  std::vector<std::string> states = node.getStateStrings();
  std::vector<std::string> ia2_states = ia2.getStateStrings();
  states.insert(states.end(), ia2_states.begin(), ia2_states.end());
  std::sort(states.begin(), states.end());
  std::string states_string;
  for (auto state : states) {
    states_string += state + ", ";
  }
  size_t pos = states_string.find_last_not_of(", ");
  if (pos != std::string::npos) {
    states_string = states_string.substr(0, pos + 1);
  }
  std::cout << " States=(" << states_string << ")\n";

  std::string indent(level * 2, ' ');

  // For the purpose of this example, dump properties even if null.
  std::string properties = ia2.toString();
  if (!properties.empty()) {
    std::cout << indent << "* " << properties << "\n";
  }

  IAAction action = node.QueryAction();
  if (!action.isNull()) {
    std::cout << indent << "* " << action.toString() << "\n";
  }

  IAComponent component = node.QueryComponent();
  if (!component.isNull()) {
    std::cout << indent << "* " << component.toString() << "\n";
  }

  IAHyperlink hyperlink = node.QueryHyperlink();
  if (!hyperlink.isNull()) {
    std::cout << indent << "* " << hyperlink.toString() << "\n";
  }

  IATable2 table2 = node.QueryTable2();
  if (!table2.isNull()) {
    std::cout << indent << "* " << table2.toString() << "\n";
  }

  IATableCell table_cell = node.QueryTableCell();
  if (!table_cell.isNull()) {
    std::cout << indent << "* " << table_cell.toString() << "\n";
  }

  IAText text = node.QueryText();
  if (!text.isNull()) {
    std::cout << indent << "* " << text.toString() << "\n";
  }

  IAValue value = node.QueryValue();
  if (!value.isNull()) {
    std::cout << indent << "* " << value.toString() << "\n";
  }

  int32_t child_count = node.getAccChildCount();
  if (child_count < 0)
    return;

  for (auto i = 0; i < child_count; i++) {
    auto child = node.AccessibleChildAt(i);
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

  IANode root = findRootIANodeForName(name, pid);
  if (root.isNull()) {
    std::cerr << "ERROR: Could not find match for";
    if (!name.empty()) {
      std::cerr << " name: '" << name << "'";
    }
    if (pid) {
      std::cerr << " PID: " << pid;
    }
    std::cerr << std::endl;
    return -1;
  }

  try {
    print_node(root, 0);
  } catch (const std::exception& err) {
    std::cerr << err.what();
  }

  return 0;
}
