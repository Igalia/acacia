#include <iostream>
#include <map>
#include <ostream>
#include <regex>
#include <string>

#include <axaccess/atspi/linux_utils.h>

static void PrintUsage(std::string& program_path) {
  std::string program_name = program_path;
  size_t pos = program_name.find_last_of("/");
  if (pos != std::string::npos) {
    program_name = program_name.substr(pos + 1);
  }

  std::cout << "Usage:\n";
  std::cout << "  " << program_name << " --name=NAME\n";
  std::cout << "  " << program_name << " --pid=PID\n";
  std::cout << "  " << program_name << " --name=NAME --pid=PID\n";
}

static std::map<std::string, std::string> ParseArguments(int argc,
                                                         char** argv) {
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

static std::string StringVectorToString(std::vector<std::string> strings) {
  std::sort(strings.begin(), strings.end());
  std::string result;
  for (auto string : strings) {
    result += string + ", ";
  }
  size_t pos = result.find_last_not_of(", ");
  if (pos != std::string::npos) {
    result = result.substr(0, pos + 1);
  }
  return result;
}

static void PrintNode(AtspiNode node, int level) {
  for (auto i = 0; i < level; i++)
    std::cout << "--";
  std::cout << "> " << node.getRoleName();
  std::cout << " Name='" << node.getName() << "'";
  std::cout << " Description='" << node.getDescription() << "'\n";

  std::string indent(level * 2, ' ');
  std::vector<std::string> states = node.getStates();
  std::cout << indent << "* States=(" << StringVectorToString(states) << ")\n";

  std::vector<std::string> interfaces = node.getInterfaces();
  std::cout << indent << "* Interfaces=(" << StringVectorToString(interfaces)
            << ")\n";

  std::vector<std::string> attributes = node.getAttributes();
  std::cout << indent << "* Attributes=(" << StringVectorToString(attributes)
            << ")\n";

  std::vector<std::string> relations = node.getRelations();
  // We dump this conditionally because most objects lack relations.
  if (!relations.empty()) {
    std::cout << indent << "* Relations=(" << StringVectorToString(relations)
              << ")\n";
  }

  AtspiComponentInterface component = node.queryComponent();
  std::cout << indent << "* Component: " << component.toString() << "\n";

  int32_t child_count = node.getChildCount();
  for (auto i = 0; i < child_count; i++) {
    auto child = node.getChildAtIndex(i);
    PrintNode(child, level + 1);
  }
}

int main(int argc, char** argv) {
  std::string program_name(argv[0]);
  auto args = ParseArguments(argc, argv);

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
    PrintUsage(program_name);
    return 1;
  }

  AtspiNode root;
  if (!name.empty()) {
    root = findRootAtspiNodeFromName(name, pid);
  } else {
    root = findRootAtspiNodeFromPID(pid);
  }

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
    PrintNode(root, 0);
  } catch (std::exception e) {
    std::cerr << e.what();
    return -1;
  }

  return 0;
}
