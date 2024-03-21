%module atspi_inspect
%{
#include <axaccess/atspi/atspi_node.h>
#include <axaccess/atspi/linux_utils.h>
%}

%include <std_string.i>
%include <std_vector.i>
%include <std_except.i>

namespace std {
  %template(AtspiNodeVector) vector<AtspiNode>;
  %template(AtspiStringVector) vector<std::string>;
};

%catches(std::runtime_error) AtspiNode::get_role_name() const;
%catches(std::runtime_error) AtspiNode::get_name() const;
%catches(std::runtime_error) AtspiNode::get_description() const;
%catches(std::runtime_error) AtspiNode::get_attributes() const;
%catches(std::runtime_error) AtspiNode::get_interfaces() const;
%catches(std::runtime_error) AtspiNode::get_relations() const;
%catches(std::runtime_error) AtspiNode::get_states() const;
%catches(std::runtime_error) AtspiNode::get_child_count() const;
%catches(std::runtime_error) AtspiNode::get_child_at_index(int index) const;
%catches(std::runtime_error) AtspiNode::get_children() const;

%include <axaccess/atspi/atspi_node.h>
%include <axaccess/atspi/linux_utils.h>
