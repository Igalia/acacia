#ifndef LIB_IA2_IA_TEXT_H_
#define LIB_IA2_IA_TEXT_H_

#include <string>

#include <wrl/client.h>

#include "acacia/export.h"
#include "third_party/ia2/include/ia2/ia2_api_all.h"

class AXA_EXPORT IAText {
 public:
  IAText(Microsoft::WRL::ComPtr<IAccessibleText> iface) : iface_(iface) {}
  ~IAText(){};

  bool isNull() { return !iface_; }
  std::string toString();
  long getCaretOffset();
  long getNCharacters();
  std::string getText(long start_offset, long end_offset);

 private:
  Microsoft::WRL::ComPtr<IAccessibleText> iface_;
};

#endif  // LIB_IA2_IA_TEXT_H_
