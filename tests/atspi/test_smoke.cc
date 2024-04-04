#include <acacia/atspi/linux_utils.h>
#include <assert.h>

int main(int argc, char** argv) {
  AtspiNode root;

  // @TODO: Just a smoke test to check-in unit tests infrastructure and
  // successful linking against AT-SPI backend libraries.

  root = findRootAtspiNodeForName("_invalid_app_name_", 0);
  assert(root.isNull());

  return 0;
}
