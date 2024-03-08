%module ia2_inspect
%{
#include <include/axaccess/ia2/ia_node.h>
%}

%include <std_string.i>

%catches(std::runtime_error) IANode::get_accRole();
%catches(std::runtime_error) IANode::get_accName();
%catches(std::runtime_error) IANode::get_accChildCount();
%catches(std::runtime_error) IANode::AccessibleChildAt(int index);

#define AXA_EXPORT
%include <axaccess/ia2/ia_node.h>
