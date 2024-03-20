#ifndef LIB_IA2_IA_2_H_
#define LIB_IA2_IA_2_H_

#include <string>
#include <vector>

#include <wrl/client.h>

#include "axaccess/export.h"
#include "third_party/ia2/include/ia2/ia2_api_all.h"

struct GroupPosition {
  long level;
  long setsize;
  long position;

  GroupPosition(){};
  GroupPosition(long level, long setsize, long position)
      : level(level), setsize(setsize), position(position) {}

  bool IsEmpty() { return level == 0 && setsize == 0 && position == 0; }
};

class AXA_EXPORT IA2 {
 public:
  IA2(Microsoft::WRL::ComPtr<IAccessible2> iface) : iface_(iface) {}
  ~IA2(){};

  bool IsNull() { return !iface_; }
  std::string GetProperties();
  std::string get_attributes();
  GroupPosition get_groupPosition();
  std::vector<std::string> GetRelations();
  std::string role();
  long get_states();
  std::vector<std::string> GetStates();

 private:
  Microsoft::WRL::ComPtr<IAccessible2> iface_;
};

#endif  // LIB_IA2_IA_2_H_