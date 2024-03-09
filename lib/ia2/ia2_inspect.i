%module ia2_inspect
%{
#include <include/axaccess/ia2/ia_node.h>
%}

%include <std_string.i>
%include <std_vector.i>

namespace std {
  %template(StringVector) vector<string>;
};

%catches(std::runtime_error) IANode::get_accRole();
%catches(std::runtime_error) IANode::get_accName();
%catches(std::runtime_error) IANode::get_accDescription();
%catches(std::runtime_error) IANode::get_accChildCount();
%catches(std::runtime_error) IANode::get_accState();
%catches(std::runtime_error) IANode::AccessibleChildAt(int index);
%catches(std::runtime_error) IANode::GetStates();

#define AXA_EXPORT
%include <axaccess/ia2/ia_node.h>
