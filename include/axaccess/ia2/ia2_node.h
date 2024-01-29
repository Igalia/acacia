#ifndef LIB_IA2_IA2_NODE_H_
#define LIB_IA2_IA2_NODE_H_

#include <memory>
#include <string>
#include <vector>
#include "axa_export.h"

class Ia2Node;
typedef std::unique_ptr<Ia2Node> Ia2NodePtr;

class AXA_EXPORT Ia2Node {
  // We need to have a point to an IA2 node, I assume, here.

  public:
    Ia2Node() {};
    ~Ia2Node() {};

    std::string get_accRole();
    std::string get_accName();
};

#endif // LIB_IA2_IA2_NODE_H_
