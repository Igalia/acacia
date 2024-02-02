#ifndef LIB_MAC_AXAPI_NODE_H_
#define LIB_MAC_AXAPI_NODE_H_

#include <ApplicationServices/ApplicationServices.h>

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace mac_inspect {

class AXAPIContextImpl;
class AXAPINode;
typedef std::unique_ptr<AXAPINode> AXAPINodePtr;

class AXAPINode {
 public:
  ~AXAPINode() = default;

  static AXAPINodePtr CreateForPID(pid_t pid);

  AXError CopyAttributeNames(std::vector<std::string>& names);

  AXError CopyAttributeValue(const std::string& attribute, std::string& value);
  AXError CopyAttributeValue(const std::string& attribute,
                             std::vector<AXAPINode>& value);

 private:
  explicit AXAPINode(AXUIElementRef ax_element);
  AXUIElementRef ax_ui_element_;

  friend class AXAPIContextImpl;
};

}  // namespace mac_inspect

#endif  // LIB_MAC_AXAPI_NODE_H_
