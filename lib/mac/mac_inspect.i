%module mac_inspect

%{
#include <include/axaccess/mac/axapi_node.h>
%}

%include "std_string.i"
%include <std_unique_ptr.i>
%unique_ptr(mac_inspect::AXAPINode)

%include <include/axaccess/mac/axapi_node.h>
