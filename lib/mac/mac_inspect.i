%module mac_inspect

%{
#include <include/axaccess/mac/axapi_node.h>
%}

%include <std_string.i>
%include <std_vector.i>

namespace std {
  %template(AXAPINodeVector) vector<mac_inspect::AXAPINode>;
  %template(StringVector) vector<string>;
};

%catches(std::exception) mac_inspect::AXAPINode::CopyAttributeNames() const;
%catches(std::exception) mac_inspect::AXAPINode::HasAttribute(const std::string& attribute) const;
%catches(std::exception) mac_inspect::AXAPINode::CopyStringAttributeValue(const std::string& attribute) const;
%catches(std::exception) mac_inspect::AXAPINode::GetListAttributeValueCount(const std::string& attribute) const;
%catches(std::exception) mac_inspect::AXAPINode::GetListAttributeValueCountCopyNodeListAttributeValue(const std::string& attribute) const;
%catches(std::exception) mac_inspect::AXAPINode::CopyNodeListAttributeValueAtIndex(const std::string& attribute, int32_t index) const;

%include <include/axaccess/mac/axapi_node.h>
