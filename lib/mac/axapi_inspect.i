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
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getStringValue(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getValueType(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getListElementType(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getListElementCount(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getBooleanValue(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getIntValue(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getFloatValue(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getStringValue(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getURLValue(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getNodeValue(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getPointValue(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getSizeValue(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getRectValue(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getRangeValue(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getNodeListValue(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getNodeListValueAtIndex(const std::string& attribute, int index) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getStringListValue(std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getStringListValueAtIndex(std::string& attribute, int index) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getRangeListValue(std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getRangeListValueAtIndex(std::string& attribute, int index) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getDictionaryListValue(std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) mac_inspect::AXAPINode::getDictionaryListValueAtIndex(std::string& attribute, int index) const;

%rename(findRootAXAPINodeForPID) mac_inspect::findRootAXAPINodeForPID;
%rename(findRootAXAPINodeForName) mac_inspect::findRootAXAPINodeForName;

%include <include/axaccess/mac/mac_data_types.h>
%include <include/axaccess/mac/axapi_node.h>
