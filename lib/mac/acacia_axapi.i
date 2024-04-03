%module acacia_axapi

%{
#include <include/acacia/mac/mac_data_types.h>
#include <include/acacia/mac/axapi_node.h>
%}

%include <std_string.i>
%include <std_vector.i>

namespace std {
  %template(AXAPINodeVector) vector<acacia_axapi::AXAPINode>;
  %template(StringVector) vector<string>;
  %template(RangeVector) vector<acacia_axapi::Range>;
  %template(DictVector) vector<acacia_axapi::Dictionary>;
};

%catches(std::runtime_error) acacia_axapi::AXAPINode::getAttributeNames() const;
%catches(std::runtime_error) acacia_axapi::AXAPINode::hasAttribute(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) acacia_axapi::AXAPINode::getStringValue(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) acacia_axapi::AXAPINode::getValueType(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) acacia_axapi::AXAPINode::getListElementType(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) acacia_axapi::AXAPINode::getListElementCount(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) acacia_axapi::AXAPINode::getBooleanValue(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) acacia_axapi::AXAPINode::getIntValue(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) acacia_axapi::AXAPINode::getFloatValue(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) acacia_axapi::AXAPINode::getStringValue(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) acacia_axapi::AXAPINode::getURLValue(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) acacia_axapi::AXAPINode::getNodeValue(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) acacia_axapi::AXAPINode::getPointValue(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) acacia_axapi::AXAPINode::getSizeValue(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) acacia_axapi::AXAPINode::getRectValue(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) acacia_axapi::AXAPINode::getRangeValue(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) acacia_axapi::AXAPINode::getNodeListValue(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) acacia_axapi::AXAPINode::getNodeListValueAtIndex(const std::string& attribute, int index) const;
%catches(std::runtime_error, std::invalid_argument) acacia_axapi::AXAPINode::getStringListValue(std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) acacia_axapi::AXAPINode::getStringListValueAtIndex(std::string& attribute, int index) const;
%catches(std::runtime_error, std::invalid_argument) acacia_axapi::AXAPINode::getRangeListValue(std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) acacia_axapi::AXAPINode::getRangeListValueAtIndex(std::string& attribute, int index) const;
%catches(std::runtime_error, std::invalid_argument) acacia_axapi::AXAPINode::getDictionaryListValue(std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) acacia_axapi::AXAPINode::getDictionaryListValueAtIndex(std::string& attribute, int index) const;

%rename(findRootAXAPINodeForPID) acacia_axapi::findRootAXAPINodeForPID;
%rename(findRootAXAPINodeForName) acacia_axapi::findRootAXAPINodeForName;

%include <include/acacia/mac/mac_data_types.h>
%include <include/acacia/mac/axapi_node.h>
