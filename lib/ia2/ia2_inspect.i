%module ia2_inspect
%{
#include <include/axaccess/ia2/ia_2.h>
#include <include/axaccess/ia2/ia_action.h>
#include <include/axaccess/ia2/ia_component.h>
#include <include/axaccess/ia2/ia_node.h>
#include <include/axaccess/ia2/ia_value.h>
%}

%include <std_pair.i>
%include <std_string.i>
%include <std_vector.i>

namespace std {
  %template(StringVector) vector<string>;
  %template(PairLongLong) pair<long, long>;
};

%catches(std::runtime_error) IANode::get_accRole();
%catches(std::runtime_error) IANode::get_accName();
%catches(std::runtime_error) IANode::get_accDescription();
%catches(std::runtime_error) IANode::get_accChildCount();
%catches(std::runtime_error) IANode::get_accState();
%catches(std::runtime_error) IANode::AccessibleChildAt(int index);
%catches(std::runtime_error) IANode::GetStates();

%catches(std::runtime_error) IA2::IA2(IANode node);
%catches(std::runtime_error) IA2::get_attributes();
%catches(std::runtime_error) IA2::role();
%catches(std::runtime_error) IA2::get_states();
%catches(std::runtime_error) IA2::GetProperties();
%catches(std::runtime_error) IA2::GetStates();

%catches(std::runtime_error) IAAction::IAAction(IANode node);
%catches(std::runtime_error) IAAction::nActions();
%catches(std::runtime_error) IAAction::get_description(int index);
%catches(std::runtime_error) IAAction::get_name(int index);
%catches(std::runtime_error) IAAction::GetProperties();

%catches(std::runtime_error) IAComponent::IAComponent(IANode node);
%catches(std::runtime_error) IAComponent::get_background();
%catches(std::runtime_error) IAComponent::get_foreground();
%catches(std::runtime_error) IAComponent::get_locationInParent();
%catches(std::runtime_error) IAComponent::GetProperties();

%catches(std::runtime_error) IAValue::IAValue(IANode node);
%catches(std::runtime_error) IAValue::get_currentValue();
%catches(std::runtime_error) IAValue::get_maximumValue();
%catches(std::runtime_error) IAValue::get_minimumValue();
%catches(std::runtime_error) IAValue::GetProperties();

#define AXA_EXPORT
%include <axaccess/ia2/ia_2.h>
%include <axaccess/ia2/ia_action.h>
%include <axaccess/ia2/ia_component.h>
%include <axaccess/ia2/ia_node.h>
%include <axaccess/ia2/ia_value.h>
