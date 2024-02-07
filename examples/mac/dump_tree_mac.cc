
#include <iostream>
#include <ostream>
#include <regex>
#include <string>

#include "include/axaccess/mac/axapi_node.h"

using mac_inspect::AXAPINode;
using mac_inspect::AXAPINodePtr;

void print_usage(std::string& program_name) {
  std::cout << "Usage: "<< program_name << " <pid>\n";
}

void logInfoForPID(pid_t pid) {
  AXAPINodePtr application = AXAPINode::CreateForPID(pid);

  std::vector<std::string> attributes = application->CopyAttributeNames();
  std::cerr << "Attributes: ";
  for (std::string& attribute : attributes) {
    std::cerr << attribute << " ";
  }
  std::cerr << "\n";

  std::string title = application->CopyStringAttributeValue("AXTitle");
  std::cerr <<  "Title: " << title << "\n";
  std::string role = application->CopyStringAttributeValue("AXRole");
  std::cerr << "Role: " << role << "\n";

  std::cerr << "\n";

  std::vector<AXAPINodePtr> children =
      application->CopyNodeListAttributeValue("AXChildren");
  for (AXAPINodePtr& child : children) {
    std::string child_title = child->CopyStringAttributeValue("AXTitle");
    std::string child_role = child->CopyStringAttributeValue("AXRole");
    std::cerr << "Child: " << child_role << " \"" << child_title << "\"\n";
    std::vector<std::string> attributes = child->CopyAttributeNames();
    std::cerr << "Attributes: ";
    for (std::string& attribute : attributes) {
      std::cerr << attribute << " ";
    }
    std::cerr << "\n\n";
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

    logInfoForPID((pid_t)pid);

    return 0;
}
