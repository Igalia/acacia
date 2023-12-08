#include <ApplicationServices/ApplicationServices.h>

#include <string>
#include <vector>

namespace mac_inspect {

class AXAPINode {
 public:
  explicit AXAPINode(AXUIElementRef ax_element);
  ~AXAPINode() = default;

  static AXAPINode createForPID(long pid);

  std::string GetRole();
  std::string GetTitle();
  std::vector<std::string> GetAttributeNames();
  std::string GetStringAttributeValue(std::string& attribute_name);

 private:
  AXUIElementRef ax_element_;
};

}  // namespace mac_inspect