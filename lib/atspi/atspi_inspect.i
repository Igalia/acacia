%module atspi_inspect
%{
#include <axaccess/atspi/atspi_component_interface.h>
#include <axaccess/atspi/atspi_node.h>
#include <axaccess/atspi/linux_utils.h>
%}

%include <std_string.i>
%include <std_pair.i>
%include <std_vector.i>
%include <std_except.i>

namespace std {
  %template(AtspiNodeVector) vector<AtspiNode>;
  %template(AtspiStringVector) vector<std::string>;
  %template(AtspiPairIntInt) pair<int, int>;
};

%catches(std::runtime_error) AtspiNode::getRoleName() const;
%catches(std::runtime_error) AtspiNode::getName() const;
%catches(std::runtime_error) AtspiNode::getDescription() const;
%catches(std::runtime_error) AtspiNode::getAttributes() const;
%catches(std::runtime_error) AtspiNode::getInterfaces() const;
%catches(std::runtime_error) AtspiNode::getRelations() const;
%catches(std::runtime_error) AtspiNode::getTargetForRelationAtIndex(int relation_index, int target_index) const;
%catches(std::runtime_error) AtspiNode::getStates() const;
%catches(std::runtime_error) AtspiNode::getChildCount() const;
%catches(std::runtime_error) AtspiNode::getChildAtIndex(int index) const;
%catches(std::runtime_error) AtspiNode::getChildren() const;
%catches(std::runtime_error) AtspiNode::queryComponent() const;

%catches(std::runtime_error) AtspiComponentInterface::toString() const;
%catches(std::runtime_error) AtspiComponentInterface::getPosition() const;
%catches(std::runtime_error) AtspiComponentInterface::getSize() const;

%include <axaccess/atspi/atspi_component_interface.h>
%include <axaccess/atspi/atspi_node.h>
%include <axaccess/atspi/linux_utils.h>
