#ifndef LIB_IA2_IA_HYPERLINK_H_
#define LIB_IA2_IA_HYPERLINK_H_

#include <string>

#include <wrl/client.h>

#include "axaccess/export.h"
#include "third_party/ia2/include/ia2/ia2_api_all.h"

class AXA_EXPORT IAHyperlink {
 public:
  IAHyperlink(Microsoft::WRL::ComPtr<IAccessibleHyperlink> iface)
      : iface_(iface) {}
  ~IAHyperlink(){};

  bool isNull() { return !iface_; }
  std::string toString();
  long getStartIndex();
  long getEndIndex();
  std::string getAnchorTarget(long index);

 private:
  Microsoft::WRL::ComPtr<IAccessibleHyperlink> iface_;
};

#endif  // LIB_IA2_IA_HYPERLINK_H_
