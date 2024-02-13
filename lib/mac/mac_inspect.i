%module mac_inspect

%{
#include <include/axaccess/mac/axapi_node.h>
%}

%include <std_string.i>
%include <std_vector.i>

namespace std {
  %template(AXAPINodeVector) vector<mac_inspect::AXAPINode>;
  %template(StringVector) vector<string>;
};

%include <include/axaccess/mac/axapi_node.h>
