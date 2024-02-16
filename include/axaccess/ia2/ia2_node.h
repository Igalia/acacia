#ifndef LIB_IA2_IA2_NODE_H_
#define LIB_IA2_IA2_NODE_H_

#include <memory>
#include <string>
#include <vector>
#include "axaccess/export.h"

#include <oleacc.h>
#include <wrl/client.h>

class IA2Node;
typedef std::unique_ptr<IA2Node> IA2NodePtr;

class AXA_EXPORT IA2Node {
  Microsoft::WRL::ComPtr<IAccessible> root_;

 public:
   IA2Node(Microsoft::WRL::ComPtr<IAccessible> root) : root_(root) {};
   ~IA2Node() {};

   static IA2NodePtr CreateForPID(const int pid);
   // testing
   static void DumpRoleTree(const int pid);

   std::string get_accRole();
   std::string get_accName();

   std::string ia2_role();
};

#endif  // LIB_IA2_IA2_NODE_H_
