%module ia2_inspect
%{
#include <include/axaccess/ia2/ia2_node.h>
%}

%include <std_string.i>

%catches(std::runtime_error) IA2Node::get_accRole();
%catches(std::runtime_error) IA2Node::get_accName();
%catches(std::runtime_error) IA2Node::get_accChildCount();
%catches(std::runtime_error) IA2Node::AccessibleChildAt(int index);

#define AXA_EXPORT
%include <axaccess/ia2/ia2_node.h>
