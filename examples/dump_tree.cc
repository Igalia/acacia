#include <assert.h>
#include <iostream>
#include <ostream>
#include <regex>
#include <string>

#include <axaccess/axaccess.h>

void print_usage(std::string& program_name) {
    std::cout << "Usage: "<< program_name << " <pid>\n";
}

static void print_node(AXA::NodePtr& node, int level) {
  for (auto i = 0; i < level; i++)
    std::cout << "--";
  std::cout << "> " << node->GetRole();
  std::string node_name = node->GetName();
  if (!node_name.empty())
    std::cout << " (" << node_name << ")";
  std::cout << "\n";

  int32_t child_count = node->GetChildCount();
  if (child_count < 0)
    return;

  for (auto i = 0; i < child_count; i++) {
    auto child = node->GetChildAt(i);
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

  const int pid = std::stoi(pid_string);
  std::cout << "Got PID: " << pid << "\n";

  AXA::ContextPtr ctx = AXA::Context::Create();
  assert(ctx != nullptr);

  AXA::NodePtr root = ctx->GetAccessibleRootByPID(pid);
  if (root == nullptr) {
    std::cerr << "No accessible root found at pid " << pid << "\n";
    return EXIT_FAILURE;
  }

  print_node(root, 0);

  root.reset();
  ctx.reset();

  return EXIT_SUCCESS;
}
