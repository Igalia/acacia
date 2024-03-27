#include "include/axaccess/mac/axapi_node.h"

#import <AppKit/NSRunningApplication.h>
#import <AppKit/NSWorkspace.h>
#import <Foundation/Foundation.h>

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "include/axaccess/mac/mac_data_types.h"
#include "lib/mac/mac_helper_functions.h"
#include "lib/mac/scoped_cf_type_ref.h"

using std::cerr;

namespace mac_inspect {

AXAPINode findRootAXAPINodeForPID(int pid) {
  AXUIElementRef root_ax_ui_element = AXUIElementCreateApplication((pid_t)pid);

  // Check whether we got an actual AXUIElement or an invalid placeholder.
  ScopedCFTypeRef<CFArrayRef> cf_attributes;
  AXError err = AXUIElementCopyAttributeNames(root_ax_ui_element,
                                              cf_attributes.get_ptr());
  if (err)
    return mac_inspect::AXAPINode();

  return AXAPINode(root_ax_ui_element);
}

AXAPINode findRootAXAPINodeForName(std::string name) {
  ScopedCFTypeRef<CFStringRef> cf_name = StdStringToCFStringRef(name);
  NSWorkspace* ws = [NSWorkspace sharedWorkspace];
  NSArray* running_apps = [[ws runningApplications]
      filteredArrayUsingPredicate:
          [NSComparisonPredicate
              predicateWithFormat:@"activationPolicy == %ld",
                                  NSApplicationActivationPolicyRegular]];
  NSArray* filtered_apps = [running_apps
      filteredArrayUsingPredicate:
          [NSPredicate predicateWithFormat:@"localizedName contains[c] %@",
                                           (NSString*)cf_name.get()]];
  for (NSRunningApplication* app in filtered_apps) {
    CFShow(app);
  }
  if ([filtered_apps count] == 0)
    return AXAPINode();

  // Just return the first one that matches.
  NSRunningApplication* app = filtered_apps[0];
  pid_t pid = [app processIdentifier];
  if (pid == -1)
    return AXAPINode();

  AXUIElementRef root_ax_ui_element = AXUIElementCreateApplication(pid);
  return AXAPINode(root_ax_ui_element);
}

AXAPINode::AXAPINode() {}

AXAPINode::AXAPINode(AXUIElementRef ax_ui_element)
    : ax_ui_element_(ax_ui_element) {}

AXAPINode::AXAPINode(const AXAPINode& other) {
  if (other.ax_ui_element_)
    ax_ui_element_ = (AXUIElementRef)CFRetain(other.ax_ui_element_);
}

AXAPINode::~AXAPINode() {
  if (ax_ui_element_)
    CFRelease(ax_ui_element_);
}

AXAPINode& AXAPINode::operator=(AXAPINode other) {
  if (other.ax_ui_element_)
    ax_ui_element_ = (AXUIElementRef)CFRetain(other.ax_ui_element_);
  return *this;
}

bool AXAPINode::isNull() {
  return ax_ui_element_ == NULL;
}

std::vector<std::string> AXAPINode::getAttributeNames() const {
  ScopedCFTypeRef<CFArrayRef> cf_attributes;
  AXError err =
      AXUIElementCopyAttributeNames(ax_ui_element_, cf_attributes.get_ptr());
  std::vector<std::string> attributes;
  if (err) {
    throw std::runtime_error(
        "Attempting to copy attribute names produced error code " +
        AXErrorToString(err));
  }
  for (CFIndex i = 0; i < CFArrayGetCount(cf_attributes.get()); ++i) {
    CFStringRef cf_attribute =
        (CFStringRef)CFArrayGetValueAtIndex(cf_attributes.get(), i);
    attributes.push_back(CFStringRefToStdString(cf_attribute));
  }
  return attributes;
}

bool AXAPINode::hasAttribute(const std::string& attribute) const {
  return getValueType(attribute) != ValueType::NOT_PRESENT;
}

ValueType AXAPINode::getValueType(const std::string& attribute) const {
  ScopedCFTypeRef<CFStringRef> cf_attribute = StdStringToCFStringRef(attribute);
  ScopedCFTypeRef<CFTypeRef> cf_value;
  AXError err = AXUIElementCopyAttributeValue(
      ax_ui_element_, cf_attribute.get(), cf_value.get_ptr());

  if (err) {
    if (err == kAXErrorNoValue || err == kAXErrorAttributeUnsupported)
      return ValueType::NOT_PRESENT;

    return ValueType::UNKNOWN;
  }

  return DeduceValueType(cf_value.get());
}

ValueType AXAPINode::getListElementType(const std::string& attribute) const {
  ScopedCFTypeRef<CFStringRef> cf_attribute = StdStringToCFStringRef(attribute);
  ScopedCFTypeRef<CFTypeRef> cf_value;
  AXError err = AXUIElementCopyAttributeValue(
      ax_ui_element_, cf_attribute.get(), cf_value.get_ptr());

  if (err) {
    // Handle errors quietly here.
    if (err == kAXErrorNoValue || err == kAXErrorAttributeUnsupported)
      return ValueType::NOT_PRESENT;

    return ValueType::UNKNOWN;
  }
  if (CFArrayGetCount((CFArrayRef)cf_value.get()) == 0) {
    // Can't determine the list type of an empty list.
    return ValueType::UNKNOWN;
  }

  CFTypeRef cf_first_value =
      (CFTypeRef)CFArrayGetValueAtIndex((CFArrayRef)cf_value.get(), 0);
  ValueType type = DeduceValueType(cf_first_value);
  return type;
}

int32_t AXAPINode::getListElementCount(const std::string& attribute) const {
  ScopedCFTypeRef<CFStringRef> cf_attribute = StdStringToCFStringRef(attribute);

  CFIndex count;
  AXError err = AXUIElementGetAttributeValueCount(ax_ui_element_,
                                                  cf_attribute.get(), &count);
  if (err) {
    switch (err) {
      case kAXErrorAttributeUnsupported:
        throw std::invalid_argument(
            "Attribute " + attribute +
            " is not supported on this node. Use hasAttribute() or "
            "getAttributeNames() to check which attributes are available.");
      default:
        throw std::runtime_error(
            "Attempting to get value count for attribute " + attribute +
            " produced error code " + AXErrorToString(err));
    }
  }

  return (int32_t)count;
}

ScopedCFTypeRef<CFTypeRef> AXAPINode::GetRawValue(
    const std::string& attribute,
    ValueType expected_type) const {
  ScopedCFTypeRef<CFStringRef> cf_attribute = StdStringToCFStringRef(attribute);
  ScopedCFTypeRef<CFTypeRef> cf_value;
  AXError err = AXUIElementCopyAttributeValue(
      ax_ui_element_, cf_attribute.get(), cf_value.get_ptr());

  if (err) {
    switch (err) {
      case kAXErrorAttributeUnsupported:
        throw std::invalid_argument(
            "Attribute " + attribute +
            " is not supported on this node. Use hasAttribute() or "
            "getAttributeNames() to check which attributes are available.");
      default:
        throw std::runtime_error(
            "Attempting to copy " + ValueTypeToString(expected_type) +
            " value for attribute " + attribute + " produced error code " +
            AXErrorToString(err));
    }
  }

  ValueType type = DeduceValueType(cf_value.get());
  if (type != expected_type) {
    throw std::invalid_argument("Value for " + attribute + " is a " +
                                ValueTypeToString(type) + ", not a " +
                                ValueTypeToString(expected_type) + ".");
  }

  return cf_value;
}

ScopedCFTypeRef<CFArrayRef> AXAPINode::GetRawArrayValue(
    const std::string& attribute) const {
  ScopedCFTypeRef<CFStringRef> cf_attribute = StdStringToCFStringRef(attribute);
  ScopedCFTypeRef<CFArrayRef> cf_array;
  AXError err = AXUIElementCopyAttributeValues(
      ax_ui_element_, cf_attribute.get(), 0, INT32_MAX, cf_array.get_ptr());

  if (err) {
    switch (err) {
      case kAXErrorAttributeUnsupported:
        throw std::invalid_argument(
            "Attribute " + attribute +
            " is not supported on this node. Use hasAttribute() or "
            "getAttributeNames() to check which attributes are available.");
      default:
        throw std::runtime_error("Attempting to copy value for attribute " +
                                 attribute + " produced error code " +
                                 AXErrorToString(err));
    }
  }

  return cf_array;
}

ScopedCFTypeRef<CFTypeRef> AXAPINode::GetRawArrayValueAtIndex(
    const std::string& attribute,
    int index,
    ValueType expected_type) const {
  ScopedCFTypeRef<CFStringRef> cf_attribute = StdStringToCFStringRef(attribute);
  ScopedCFTypeRef<CFArrayRef> cf_array;
  AXError err =
      AXUIElementCopyAttributeValues(ax_ui_element_, cf_attribute.get(),
                                     (CFIndex)index, 1l, cf_array.get_ptr());

  if (err) {
    switch (err) {
      case kAXErrorAttributeUnsupported:
        throw std::invalid_argument(
            "Attribute " + attribute +
            " is not supported on this node. Use      () or "
            "getAttributeNames() to check which attributes are available.");
      case kAXErrorIllegalArgument:
        throw std::invalid_argument(
            "Index " + std::to_string(index) +
            " is out of bounds, or the value of " + attribute +
            " is not an array. Use getListElementCount() to "
            "check the number of values.");
      default:
        int32_t count = getListElementCount(attribute);
        throw std::runtime_error(
            "Attempting to copy value at index " + std::to_string(index) +
            " (count is " + std::to_string(count) + ") for attribute " +
            attribute + " produced error code " + AXErrorToString(err));
    }
  }

  if (CFArrayGetCount(cf_array.get()) != 1l)
    throw std::runtime_error("Couldn't get array");

  auto cf_value = ScopedCFTypeRef<CFTypeRef>::CreateFromUnownedRef(
      (CFTypeRef)CFArrayGetValueAtIndex(cf_array.get(), 0));
  ValueType type = DeduceValueType(cf_value.get());
  if (type != expected_type) {
    throw std::invalid_argument("List value for " + attribute + " at " +
                                std::to_string(index) + " is a " +
                                ValueTypeToString(type) + ", not a " +
                                ValueTypeToString(expected_type) + ".");
  }
  return cf_value;
}

bool AXAPINode::getBooleanValue(const std::string& attribute) const {
  ScopedCFTypeRef<CFTypeRef> cf_value =
      GetRawValue(attribute, ValueType::BOOLEAN);

  return CFBooleanGetValue((CFBooleanRef)cf_value.get());
}

int AXAPINode::getIntValue(const std::string& attribute) const {
  ScopedCFTypeRef<CFTypeRef> cf_value = GetRawValue(attribute, ValueType::INT);

  int int_value;
  if (!CFNumberGetValue((CFNumberRef)cf_value.get(),
                        CFNumberGetType((CFNumberRef)cf_value.get()),
                        &int_value)) {
    throw std::runtime_error("Couldn't get int value for " + attribute);
  }

  return int_value;
}

float AXAPINode::getFloatValue(const std::string& attribute) const {
  ScopedCFTypeRef<CFTypeRef> cf_value =
      GetRawValue(attribute, ValueType::FLOAT);

  float float_value;
  if (!CFNumberGetValue((CFNumberRef)cf_value.get(),
                        CFNumberGetType((CFNumberRef)cf_value.get()),
                        &float_value)) {
    throw std::runtime_error("Couldn't get float value for " + attribute);
  }

  return float_value;
}

std::string AXAPINode::getStringValue(const std::string& attribute) const {
  ScopedCFTypeRef<CFStringRef> cf_attribute = StdStringToCFStringRef(attribute);
  ScopedCFTypeRef<CFTypeRef> cf_value;
  AXError err = AXUIElementCopyAttributeValue(
      ax_ui_element_, cf_attribute.get(), cf_value.get_ptr());

  if (err) {
    switch (err) {
      case kAXErrorNoValue:
        // For some reason, sometimes an AXUIElement lists a string attribute
        // which has no value. Since we can't check for this condition other
        // than getting the attribute, handle this case quietly.
        return "";
      case kAXErrorAttributeUnsupported:
        throw std::invalid_argument(
            "Attribute " + attribute +
            " is not supported on this node. Use hasAttribute() or "
            "getAttributeNames() to check which attributes are available.");
      default:
        throw std::runtime_error(
            "Attempting to copy string value for attribute " + attribute +
            " produced error code " + AXErrorToString(err));
    }
  }

  if (CFGetTypeID(cf_value.get()) != CFStringGetTypeID()) {
    ValueType type = DeduceValueType(cf_value.get());
    throw std::invalid_argument("Value for " + attribute + " is a " +
                                ValueTypeToString(type) + ", not a " +
                                ValueTypeToString(ValueType::STRING) + ".");
  }

  return CFStringRefToStdString((CFStringRef)cf_value.get());
}

std::string AXAPINode::getURLValue(const std::string& attribute) const {
  ScopedCFTypeRef<CFTypeRef> cf_value = GetRawValue(attribute, ValueType::URL);

  CFStringRef cf_url_string = CFURLGetString((CFURLRef)cf_value.get());

  return CFStringRefToStdString(cf_url_string);
}

AXAPINode AXAPINode::getNodeValue(const std::string& attribute) const {
  ScopedCFTypeRef<CFTypeRef> cf_value = GetRawValue(attribute, ValueType::NODE);

  return AXAPINode((AXUIElementRef)(cf_value.Retain()));
}

Point AXAPINode::getPointValue(const std::string& attribute) const {
  ScopedCFTypeRef<CFTypeRef> cf_value =
      GetRawValue(attribute, ValueType::POINT);

  CGPoint cg_point;
  if (!AXValueGetValue((AXValueRef)cf_value.get(),
                       (AXValueType)kAXValueCGPointType, &cg_point)) {
    throw std::runtime_error("Could not get " +
                             ValueTypeToString(ValueType::POINT) +
                             " value for " + attribute);
  }

  return Point(cg_point.x, cg_point.y);
}

Size AXAPINode::getSizeValue(const std::string& attribute) const {
  ScopedCFTypeRef<CFTypeRef> cf_value = GetRawValue(attribute, ValueType::SIZE);

  CGSize cg_size;
  if (!AXValueGetValue((AXValueRef)cf_value.get(),
                       (AXValueType)kAXValueCGSizeType, &cg_size)) {
    throw std::runtime_error("Could not get " +
                             ValueTypeToString(ValueType::SIZE) +
                             " value for " + attribute);
  }

  return Size(cg_size.width, cg_size.height);
}

Rect AXAPINode::getRectValue(const std::string& attribute) const {
  ScopedCFTypeRef<CFTypeRef> cf_value = GetRawValue(attribute, ValueType::RECT);

  CGRect cg_rect;
  if (!AXValueGetValue((AXValueRef)cf_value.get(),
                       (AXValueType)kAXValueCGRectType, &cg_rect)) {
    throw std::runtime_error("Could not get " +
                             ValueTypeToString(ValueType::RECT) +
                             " value for " + attribute);
  }
  CGPoint& cg_origin = cg_rect.origin;
  CGSize& cg_size = cg_rect.size;
  return Rect(cg_origin.x, cg_origin.y, cg_size.width, cg_size.height);
}

Range AXAPINode::getRangeValue(const std::string& attribute) const {
  ScopedCFTypeRef<CFTypeRef> cf_value =
      GetRawValue(attribute, ValueType::RANGE);

  CFRange cf_range;
  if (!AXValueGetValue((AXValueRef)cf_value.get(),
                       (AXValueType)kAXValueCFRangeType, &cf_range)) {
    throw std::runtime_error("Could not get " +
                             ValueTypeToString(ValueType::RANGE) +
                             " value for " + attribute);
  }

  return Range(cf_range.length, cf_range.location);
}

std::vector<AXAPINode> AXAPINode::getNodeListValue(
    const std::string& attribute) const {
  ScopedCFTypeRef<CFArrayRef> cf_array = GetRawArrayValue(attribute);

  std::vector<AXAPINode> value;
  for (CFIndex i = 0; i < CFArrayGetCount(cf_array.get()); ++i) {
    CFTypeRef cf_ith_value =
        (CFTypeRef)CFArrayGetValueAtIndex(cf_array.get(), i);

    if (CFGetTypeID(cf_ith_value) != AXUIElementGetTypeID()) {
      ValueType value_type = DeduceValueType(cf_ith_value);
      throw std::invalid_argument("Value for " + attribute + " is a list of " +
                                  ValueTypeToString(value_type) + ", not a " +
                                  ValueTypeToString(ValueType::NODE) + ".");
    }

    value.push_back(AXAPINode((AXUIElementRef)CFRetain(cf_ith_value)));
  }

  return value;
}

AXAPINode AXAPINode::getNodeListValueAtIndex(const std::string& attribute,
                                             int index) const {
  ScopedCFTypeRef<CFTypeRef> cf_value =
      GetRawArrayValueAtIndex(attribute, index, ValueType::NODE);

  return AXAPINode((AXUIElementRef)cf_value.Retain());
}

std::vector<std::string> AXAPINode::getStringListValue(
    std::string& attribute) const {
  ScopedCFTypeRef<CFArrayRef> cf_array = GetRawArrayValue(attribute);

  std::vector<std::string> value;
  for (CFIndex i = 0; i < CFArrayGetCount(cf_array.get()); ++i) {
    CFTypeRef cf_ith_value =
        (CFTypeRef)CFArrayGetValueAtIndex(cf_array.get(), i);

    if (CFGetTypeID(cf_ith_value) != CFStringGetTypeID()) {
      ValueType value_type = DeduceValueType(cf_ith_value);
      throw std::invalid_argument("Value for " + attribute + " is a list of " +
                                  ValueTypeToString(value_type) + ", not a " +
                                  ValueTypeToString(ValueType::STRING) + ".");
    }

    value.push_back(CFStringRefToStdString((CFStringRef)cf_ith_value));
  }

  return value;
}

std::string AXAPINode::getStringListValueAtIndex(std::string& attribute,
                                                 int index) const {
  ScopedCFTypeRef<CFTypeRef> cf_value =
      GetRawArrayValueAtIndex(attribute, index, ValueType::STRING);

  return CFStringRefToStdString((CFStringRef)cf_value.Retain());
}

std::vector<Range> AXAPINode::getRangeListValue(std::string& attribute) const {
  ScopedCFTypeRef<CFArrayRef> cf_array = GetRawArrayValue(attribute);

  std::vector<Range> value;
  for (CFIndex i = 0; i < CFArrayGetCount(cf_array.get()); ++i) {
    CFTypeRef cf_ith_value =
        (CFTypeRef)CFArrayGetValueAtIndex(cf_array.get(), i);

    ValueType value_type = DeduceValueType(cf_ith_value);
    if (value_type != ValueType::RANGE) {
      throw std::invalid_argument("Value for " + attribute + " is a list of " +
                                  ValueTypeToString(value_type) + ", not a " +
                                  ValueTypeToString(ValueType::RANGE) + ".");
    }

    CFRange cf_range;
    if (!AXValueGetValue((AXValueRef)cf_ith_value,
                         (AXValueType)kAXValueCFRangeType, &cf_range)) {
      throw std::runtime_error("Could not get " +
                               ValueTypeToString(ValueType::RANGE) +
                               " value for " + attribute);
    }

    value.push_back(Range(cf_range.length, cf_range.location));
  }

  return value;
}

Range AXAPINode::getRangeListValueAtIndex(std::string& attribute,
                                          int index) const {
  ScopedCFTypeRef<CFTypeRef> cf_value =
      GetRawArrayValueAtIndex(attribute, index, ValueType::RANGE);
  CFRange cf_range;
  if (!AXValueGetValue((AXValueRef)cf_value.get(),
                       (AXValueType)kAXValueCFRangeType, &cf_range)) {
    throw std::runtime_error("Could not get " +
                             ValueTypeToString(ValueType::RANGE) +
                             " value for " + attribute);
  }
  return Range(cf_range.length, cf_range.location);
}

std::vector<Dictionary> AXAPINode::getDictionaryListValue(
    std::string& attribute) const {
  ScopedCFTypeRef<CFArrayRef> cf_array = GetRawArrayValue(attribute);

  std::vector<Dictionary> value;
  for (CFIndex i = 0; i < CFArrayGetCount(cf_array.get()); ++i) {
    CFTypeRef cf_ith_value =
        (CFTypeRef)CFArrayGetValueAtIndex(cf_array.get(), i);

    if (CFGetTypeID(cf_ith_value) == CFDictionaryGetTypeID()) {
      ValueType value_type = DeduceValueType(cf_ith_value);
      throw std::invalid_argument("Value for " + attribute + " is a list of " +
                                  ValueTypeToString(value_type) + ", not a " +
                                  ValueTypeToString(ValueType::DICTIONARY) +
                                  ".");
    }

    CFDictionaryRef cf_dictionary;

    value.push_back(Dictionary((CFDictionaryRef)CFRetain(cf_dictionary)));
  }

  return value;
}

Dictionary AXAPINode::getDictionaryListValueAtIndex(std::string& attribute,
                                                    int index) const {
  ScopedCFTypeRef<CFTypeRef> cf_value =
      GetRawArrayValueAtIndex(attribute, index, ValueType::DICTIONARY);

  return Dictionary((CFDictionaryRef)cf_value.Retain());
}

}  // namespace mac_inspect
