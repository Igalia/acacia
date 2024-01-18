#ifndef LIB_MAC_AXAPI_NODE_H_
#define LIB_MAC_AXAPI_NODE_H_

#include <ApplicationServices/ApplicationServices.h>

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace mac_inspect {

class AXAPINode;
typedef std::unique_ptr<AXAPINode> AXAPINodePtr;

class AXAPINode {
 public:
  ~AXAPINode() = default;

  static AXAPINodePtr createForPID(long pid);

  std::string GetRole();
  std::string GetTitle();
  std::vector<std::string> GetAttributeNames();
  std::string GetStringAttributeValue(std::string& attribute_name);
  long GetChildCount();
  AXAPINodePtr GetChildAt(long index);

 private:
  explicit AXAPINode(AXUIElementRef ax_element);
  AXUIElementRef ax_ui_element_;
};

}  // namespace mac_inspect

#endif  // LIB_MAC_AXAPI_NODE_H_
