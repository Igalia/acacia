%module atspi_inspect
%{
#include <axaccess/atspi/atspi_node.h>
#include <axaccess/atspi/linux_utils.h>
%}

%include <std_string.i>
%include <std_unique_ptr.i>
%unique_ptr(AtspiNode)

%catches(std::runtime_error) AtspiNode::get_role_name();
%catches(std::runtime_error) AtspiNode::get_name();
%catches(std::runtime_error) AtspiNode::get_child_count();
%catches(std::runtime_error) AtspiNode::get_child_at_index(int index);
%catches(std::runtime_error) AtspiNode::get_children();

%include <axaccess/atspi/atspi_node.h>
%include <axaccess/atspi/linux_utils.h>
