%module mac_inspect

%{
#include <axaccess/mac/axapi_node.h>
%}

%include "std_string.i"
%include <std_unique_ptr.i>
%unique_ptr(mac_inspect::AXAPINode)

%include <axaccess/mac/axapi_node.h>
