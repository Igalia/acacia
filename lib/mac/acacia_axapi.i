%module acacia_axapi

%{
#include <include/acacia/mac/mac_data_types.h>
#include <include/acacia/mac/axapi_node.h>
%}

%include <std_string.i>
%include <std_vector.i>

namespace std {
  %template(AXAPINodeVector) vector<acacia::AXAPINode>;
  %template(StringVector) vector<string>;
  %template(RangeVector) vector<acacia::Range>;
  %template(DictVector) vector<acacia::Dictionary>;
};

%catches(std::runtime_error) acacia::AXAPINode::getAttributeNames() const;
%catches(std::runtime_error) acacia::AXAPINode::hasAttribute(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) acacia::AXAPINode::getStringValue(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) acacia::AXAPINode::getValueType(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) acacia::AXAPINode::getListElementType(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) acacia::AXAPINode::getListElementCount(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) acacia::AXAPINode::getBooleanValue(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) acacia::AXAPINode::getIntValue(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) acacia::AXAPINode::getFloatValue(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) acacia::AXAPINode::getStringValue(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) acacia::AXAPINode::getURLValue(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) acacia::AXAPINode::getNodeValue(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) acacia::AXAPINode::getPointValue(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) acacia::AXAPINode::getSizeValue(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) acacia::AXAPINode::getRectValue(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) acacia::AXAPINode::getRangeValue(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) acacia::AXAPINode::getNodeListValue(const std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) acacia::AXAPINode::getNodeListValueAtIndex(const std::string& attribute, int index) const;
%catches(std::runtime_error, std::invalid_argument) acacia::AXAPINode::getStringListValue(std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) acacia::AXAPINode::getStringListValueAtIndex(std::string& attribute, int index) const;
%catches(std::runtime_error, std::invalid_argument) acacia::AXAPINode::getRangeListValue(std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) acacia::AXAPINode::getRangeListValueAtIndex(std::string& attribute, int index) const;
%catches(std::runtime_error, std::invalid_argument) acacia::AXAPINode::getDictionaryListValue(std::string& attribute) const;
%catches(std::runtime_error, std::invalid_argument) acacia::AXAPINode::getDictionaryListValueAtIndex(std::string& attribute, int index) const;

%rename(findRootAXAPINodeForPID) acacia::findRootAXAPINodeForPID;
%rename(findRootAXAPINodeForName) acacia::findRootAXAPINodeForName;

%warnfilter(503) acacia::AXAPINode::operator=;
%warnfilter(503) acacia::Point::operator=;
%warnfilter(503) acacia::Size::operator=;
%warnfilter(503) acacia::Rect::operator=;
%warnfilter(503) acacia::Range::operator=;
%warnfilter(503) acacia::Dictionary::operator=;


%include <include/acacia/mac/mac_data_types.h>
%include <include/acacia/mac/axapi_node.h>
