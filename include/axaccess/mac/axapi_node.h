#ifndef LIB_MAC_AXAPI_NODE_H_
#define LIB_MAC_AXAPI_NODE_H_

#include <ApplicationServices/ApplicationServices.h>

#include <memory>
#include <string>
#include <vector>

namespace mac_inspect {

class AXAPIContextImpl;

class AXAPINode {
 public:
  AXAPINode();
  AXAPINode(const AXAPINode& other);
  ~AXAPINode();

  static AXAPINode CreateForPID(int pid);

  std::vector<std::string> CopyAttributeNames() const;

  std::string CopyStringAttributeValue(const std::string& attribute) const;

  std::vector<AXAPINode> CopyNodeListAttributeValue(
      const std::string& attribute) const;

  AXAPINode CopyNodeListAttributeValueAtIndex(const std::string& attribute,
                                              int32_t index) const;

 private:
  explicit AXAPINode(AXUIElementRef ax_element);
  AXUIElementRef ax_ui_element_;

  friend class AXAPIContextImpl;
};

}  // namespace mac_inspect

#endif  // LIB_MAC_AXAPI_NODE_H_
