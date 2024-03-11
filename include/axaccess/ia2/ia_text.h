#ifndef LIB_IA2_IA_TEXT_H_
#define LIB_IA2_IA_TEXT_H_

#include <string>

#include "axaccess/export.h"
#include "axaccess/ia2/ia_node.h"
#include "third_party/ia2/include/ia2/ia2_api_all.h"

class AXA_EXPORT IAText {
 public:
  IAText(IANode node) : node_(node){};
  ~IAText(){};

  std::string GetProperties();
  long get_caretOffset();
  long get_nCharacters();
  std::string get_text(long start_offset, long end_offset);

 private:
  Microsoft::WRL::ComPtr<IAccessibleText> QueryInterface();
  IANode node_;
};

#endif  // LIB_IA2_IA_TEXT_H_
