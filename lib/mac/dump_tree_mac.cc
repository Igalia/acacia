
#include <iostream>
#include <ostream>
#include <regex>
#include <string>

#include "lib/mac/mac.h"

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

    return 0;
}
