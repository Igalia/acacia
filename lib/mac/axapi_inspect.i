%module axapi_inspect

%{
#include <include/axaccess/mac/mac_data_types.h>
#include <include/axaccess/mac/axapi_node.h>
%}

%include <std_string.i>
%include <std_vector.i>

namespace std {
  %template(AXAPINodeVector) vector<mac_inspect::AXAPINode>;
  %template(StringVector) vector<string>;
  %template(RangeVector) vector<mac_inspect::Range>;
  %template(DictVector) vector<mac_inspect::Dictionary>;
};

%catches(std::runtime_error) mac_inspect::AXAPINode::getAttributeNames() const;
%catches(std::runtime_error) mac_inspect::AXAPINode::hasAttribute(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getStringAttribute(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getValueType(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getListElementType(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getListElementCount(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getBooleanAttribute(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getIntAttribute(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getFloatAttribute(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getStringAttribute(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getURLAttribute(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getNodeAttribute(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getPointAttribute(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getSizeAttribute(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getRectAttribute(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getRangeAttribute(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getNodeListAttribute(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getNodeListAttribute(const std::string& attribute, int index) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getStringListAttribute(std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getStringListAttribute(std::string& attribute, int index) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getRangeListAttribute(std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getRangeListAttribute(std::string& attribute, int index) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getDictionaryListAttribute(std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getDictionaryListAttribute(std::string& attribute, int index) const;

%rename(findRootAXAPINodeForPID) mac_inspect::findRootAXAPINodeForPID;
%rename(findRootAXAPINodeForName) mac_inspect::findRootAXAPINodeForName;

%include <include/axaccess/mac/mac_data_types.h>
%include <include/axaccess/mac/axapi_node.h>
