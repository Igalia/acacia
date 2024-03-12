%module atspi_inspect
%{
#include <axaccess/atspi/atspi_node.h>
#include <axaccess/atspi/linux_utils.h>
%}

%include <std_string.i>
%include <std_unique_ptr.i>
%unique_ptr(AtspiNode)

%catches(std::runtime_error) atspi_inspect::AtspiNode::get_role_name() const;
%catches(std::runtime_error) atspi_inspect::AtspiNode::get_name() const;
%catches(std::runtime_error) atspi_inspect::AtspiNode::get_child_count() const;
%catches(std::runtime_error) atspi_inspect::AtspiNode::get_child_at_index() const;
%catches(std::runtime_error) atspi_inspect::AtspiNode::get_children() const;

%include <axaccess/atspi/atspi_node.h>
%include <axaccess/atspi/linux_utils.h>
