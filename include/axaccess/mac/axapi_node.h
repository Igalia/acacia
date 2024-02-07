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

  static AXAPINodePtr CreateForPID(int pid);

  std::vector<std::string> CopyAttributeNames();

  std::string CopyStringAttributeValue(const std::string& attribute);

  std::vector<AXAPINodePtr> CopyNodeListAttributeValue(
      const std::string& attribute);

 private:
  explicit AXAPINode(AXUIElementRef ax_element);
  AXUIElementRef ax_ui_element_;

  friend class AXAPIContextImpl;
};

}  // namespace mac_inspect

#endif  // LIB_MAC_AXAPI_NODE_H_
