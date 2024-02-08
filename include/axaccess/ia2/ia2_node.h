#ifndef LIB_IA2_IA2_NODE_H_
#define LIB_IA2_IA2_NODE_H_

#include <memory>
#include <string>
#include <vector>
#include "axaccess/export.h"

class IA2Node;
typedef std::unique_ptr<IA2Node> IA2NodePtr;

class AXA_EXPORT IA2Node {
  // We need to have a point to an IA2 node, I assume, here.

  public:
    IA2Node() {};
    ~IA2Node() {};

    std::string get_accRole();
    std::string get_accName();
};

#endif // LIB_IA2_IA2_NODE_H_
