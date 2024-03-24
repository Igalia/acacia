#include "include/axaccess/mac/mac_data_types.h"

#include <iostream>
#include <string>
#include <vector>

#include <ApplicationServices/ApplicationServices.h>
#include <Foundation/Foundation.h>

#include "include/axaccess/mac/axapi_node.h"
#include "lib/mac/mac_helper_functions.h"
#include "lib/mac/scoped_cf_type_ref.h"

using std::cerr;

namespace mac_inspect {

std::string ValueTypeToString(ValueType value_type) {
  switch (value_type) {
    case ValueType::NOT_PRESENT:
      return "NOT_PRESENT";
    case ValueType::UNKNOWN:
      return "UNKNOWN";
    case ValueType::LIST:
      return "LIST";
    case ValueType::BOOLEAN:
      return "BOOLEAN";
    case ValueType::INT:
      return "INT";
    case ValueType::FLOAT:
      return "FLOAT";
    case ValueType::STRING:
      return "STRING";
    case ValueType::URL:
      return "URL";
    case ValueType::NODE:
      return "NODE";
    case ValueType::POINT:
      return "POINT";
    case ValueType::SIZE:
      return "SIZE";
    case ValueType::RECT:
      return "RECT";
    case ValueType::RANGE:
      return "RANGE";
    case ValueType::DICTIONARY:
      return "DICTIONARY";
    case ValueType::DATA:
      return "DATA";
    case ValueType::TEXTMARKER:
      return "TEXTMARKER";
    case ValueType::TEXTMARKERRANGE:
      return "TEXTMARKERRANGE";
  }
}

std::string Point::ToString() {
  return "(" + std::to_string(x_) + ", " + std::to_string(y_) + ")";
}

std::string Size::ToString() {
  return "[" + std::to_string(width_) + ", " + std::to_string(height_) + "]";
}

std::string Rect::ToString() {
  return origin_.ToString() + "/" + size_.ToString();
}

std::string Range::ToString() {
  return "[" + std::to_string(length_) + ", " + std::to_string(location_) + "]";
}

Dictionary::~Dictionary() {
  if (cf_dictionary_)
    CFRelease(cf_dictionary_);
}

std::vector<std::string> Dictionary::keys() {
  long count = (long)CFDictionaryGetCount(cf_dictionary_);
  std::vector<const void*> keys(count);
  CFDictionaryGetKeysAndValues(cf_dictionary_, keys.data(), NULL);

  std::vector<std::string> result;
  for (long i = 0; i < count; i++) {
    CFStringRef cf_key = (CFStringRef)(keys[i]);
    result.push_back(CFStringRefToStdString(cf_key));
  }

  return result;
}

ValueType Dictionary::getValueType(const std::string& key) {
  ScopedCFTypeRef<CFStringRef> cf_key = StdStringToCFStringRef(key);

  CFTypeRef cf_value =
      (CFTypeRef)CFDictionaryGetValue(cf_dictionary_, cf_key.get());
  return DeduceValueType(cf_value);
}

std::string Dictionary::getStringValue(const std::string& key) {
  ScopedCFTypeRef<CFStringRef> cf_key = StdStringToCFStringRef(key);

  CFTypeRef cf_value =
      (CFTypeRef)CFDictionaryGetValue(cf_dictionary_, cf_key.get());
  if (CFGetTypeID(cf_value) != CFStringGetTypeID()) {
    ValueType type = DeduceValueType(cf_value);
    throw std::invalid_argument("Dictionary value for " + key + " is a " +
                                ValueTypeToString(type) + ", not a " +
                                ValueTypeToString(ValueType::STRING) + ".");
  }

  return CFStringRefToStdString((CFStringRef)cf_value);
}

AXAPINode Dictionary::getNodeValue(const std::string& key) {
  ScopedCFTypeRef<CFStringRef> cf_key = StdStringToCFStringRef(key);

  CFTypeRef cf_value =
      (CFTypeRef)CFDictionaryGetValue(cf_dictionary_, cf_key.get());
  if (CFGetTypeID(cf_value) != AXUIElementGetTypeID()) {
    ValueType type = DeduceValueType(cf_value);
    throw std::invalid_argument("Dictionary value for " + key + " is a " +
                                ValueTypeToString(type) + ", not a " +
                                ValueTypeToString(ValueType::NODE) + ".");
  }

  return AXAPINode((AXUIElementRef)CFRetain(cf_value));
}

}  // namespace mac_inspect
