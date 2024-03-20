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

  bool IsNull() { return !iface_; }
  std::string GetProperties();
  long get_startIndex();
  long get_endIndex();
  std::string get_anchorTarget(long index);

 private:
  Microsoft::WRL::ComPtr<IAccessibleHyperlink> iface_;
};

#endif  // LIB_IA2_IA_HYPERLINK_H_