#include <iostream>
#include <ostream>
#include <regex>
#include <string>

#include "include/axaccess/ia2/win_utils.h"
#include "include/axaccess/ia2/ia2_node.h"


void print_usage(std::string& program_name) {
    std::cout << "Usage: "<< program_name << " <pid>\n";
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
    IA2NodePtr root = find_root_accessible_from_pid(pid);
    if (!root) {
      std::cerr << "No accessible root found at pid " << pid << "\n";
      return -1;
    }
    
    std::cout << root->get_accRole();
    std::cout << " (" << root->get_accName() << ")\n";
    return 0;
}
