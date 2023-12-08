
#include <iostream>
#include <ostream>
#include <regex>
#include <string>

#include "include/axaccess/mac/axapi_node.h"

using mac_inspect::AXAPINode;

void print_usage(std::string& program_name) {
  std::cout << "Usage: "<< program_name << " <pid>\n";
}

void logInfoForPID(pid_t pid) {
  AXAPINode application = AXAPINode::createForPID(pid);
  std::vector<std::string> attributes = application.GetAttributeNames();
  if (attributes.empty()) {
    std::cerr << "No application with PID " << pid << "\n";
    return;
  }
  std::string title = application.GetTitle();
  std::cout <<  "Title: " << title << "\n";
  std::string role = application.GetRole();
  std::cout << "Role: " << role << "\n";

  for (std::string attribute : attributes) {
    std::string attribute_value = application.GetStringAttributeValue(attribute);
    std::cout << attribute << " is " << attribute_value << "\n";
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
    std::cout << "Got PID: " << pid << "\n";

    logInfoForPID(pid);

    return 0;
}

