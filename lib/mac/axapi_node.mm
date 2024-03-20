#include "include/axaccess/mac/axapi_node.h"

#import <ApplicationServices/ApplicationServices.h>
#import <Foundation/Foundation.h>

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using std::cerr;

namespace {

// Container to handle CFRelease-ing CFTypeRefs at the end of a scope. See:
// https://developer.apple.com/library/archive/documentation/CoreFoundation/Conceptual/CFMemoryMgmt/Concepts/Ownership.html
//
// This should be used when a method with "Create" or "Copy" is used to obtain
// a CFTypeRef, to ensure CFRelease is called appropriately.
template <typename T>
class ScopedCFTypeRef {
 public:
  ScopedCFTypeRef() = default;
  ScopedCFTypeRef(T ref) : ref_(ref) {}
  ScopedCFTypeRef(ScopedCFTypeRef& other) : ref_(other.ref_) { CFRetain(ref_); }

  ~ScopedCFTypeRef() {
    if (ref_)
      CFRelease(ref_);
  }

  T get() { return ref_; }
  T* get_ptr() { return &ref_; }

  ScopedCFTypeRef& operator=(ScopedCFTypeRef other) {
    if (ref_)
      CFRelease(ref_);
    ref_ = other.ref_;
    return *this;
  }

 private:
  T ref_{NULL};
};

const std::string CFStringRefToStdString(CFStringRef cf_string) {
  if (cf_string == nullptr)
    return "";

  const char* chars =
      CFStringGetCStringPtr(cf_string, CFStringGetSystemEncoding());
  if (!chars) {
    // CFStringRef can secretly be an NSString, in which case
    // CFStringGetCStringPtr doesn't work.
    NSString* ns_string = (__bridge NSString*)cf_string;
    const char* ns_chars =
        [ns_string cStringUsingEncoding:[NSString defaultCStringEncoding]];
    chars = ns_chars ? ns_chars : "";
  }
  return std::string(chars);
}

// This returns a ScopedCFTypeRef since the CFStringRef is obtained using
// CFStringCreateWithCString, meaning we own the CFStringRef and are responsible
// for releasing it.
ScopedCFTypeRef<CFStringRef> StdStringToCFStringRef(
    const std::string& std_string) {
  return ScopedCFTypeRef<CFStringRef>(
      CFStringCreateWithCString(kCFAllocatorDefault, std_string.c_str(),
                                [NSString defaultCStringEncoding]));
}

std::string AXErrorToString(AXError err) {
  switch (err) {
    case kAXErrorAttributeUnsupported:
      return "kAXErrorAttributeUnsupported";
    case kAXErrorNoValue:
      return "kAXErrorNoValue";
    case kAXErrorIllegalArgument:
      return "kAXErrorIllegalArgument";
    case kAXErrorCannotComplete:
      return "kAXErrorCannotComplete";
    case kAXErrorNotImplemented:
      return "kAXErrorNotImplemented";
    default:
      return std::to_string(err);
  }
}

using mac_inspect::ValueType;
using mac_inspect::ValueTypeToString;
ValueType TypeIDToValueType(CFTypeID type_id,
                            ScopedCFTypeRef<CFTypeRef> cf_value,
                            const std::string& attribute = "") {
  if (type_id == CFBooleanGetTypeID())
    return ValueType::BOOLEAN;

  if (type_id == CFNumberGetTypeID()) {
    if (CFNumberIsFloatType((CFNumberRef)cf_value.get()))
      return ValueType::FLOAT;

    return ValueType::INT;
  }

  if (type_id == CFStringGetTypeID())
    return ValueType::STRING;

  if (type_id == CFURLGetTypeID())
    return ValueType::URL;

  if (type_id == AXUIElementGetTypeID())
    return ValueType::NODE;

  if (type_id == CFArrayGetTypeID())
    return ValueType::LIST;

  if (type_id == AXValueGetTypeID()) {
    AXValueType ax_value_type = AXValueGetType((AXValueRef)cf_value.get());
    switch (ax_value_type) {
      case kAXValueCGPointType:
        return ValueType::POINT;
      case kAXValueCGSizeType:
        return ValueType::SIZE;
      case kAXValueCGRectType:
        return ValueType::RECT;
      case kAXValueCFRangeType:
        return ValueType::RANGE;
      default:
        return ValueType::UNKNOWN;
    }
  }

  if (attribute != "") {
    CFStringRef description = CFCopyTypeIDDescription(type_id);
    cerr << "Unknown type: " << type_id << " ("
         << CFStringRefToStdString(description) << ") for attribute "
         << attribute << "\n";
  }
  return ValueType::UNKNOWN;
}

}  // namespace

namespace mac_inspect {

std::string ValueTypeToString(ValueType value_type) {
  switch (value_type) {
    case ValueType::NOT_PRESENT:
      return "NOT_PRESENT";
    case ValueType::UNKNOWN:
      return "UNKNOWN";
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
    case ValueType::LIST:
      return "LIST";
  }
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

AXAPINode AXAPINode::CreateForPID(int pid) {
  AXUIElementRef root_ax_ui_element = AXUIElementCreateApplication((pid_t)pid);

  // Check whether we got an actual AXUIElement or an invalid placeholder.
  ScopedCFTypeRef<CFArrayRef> cf_attributes;
  AXError err = AXUIElementCopyAttributeNames(root_ax_ui_element,
                                              cf_attributes.get_ptr());
  if (err)
    return AXAPINode();

  return AXAPINode(root_ax_ui_element);
}

bool AXAPINode::IsNull() {
  return ax_ui_element_ == NULL;
}

std::vector<std::string> AXAPINode::CopyAttributeNames() const {
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

bool AXAPINode::HasAttribute(const CFStringRef attribute) const {
  ScopedCFTypeRef<CFArrayRef> cf_attributes;
  AXError err =
      AXUIElementCopyAttributeNames(ax_ui_element_, cf_attributes.get_ptr());
  if (err) {
    throw std::runtime_error("Attempting to check for presence of attribute " +
                             CFStringRefToStdString(attribute) +
                             " produced error code " + AXErrorToString(err));
  }
  CFIndex num_attributes = CFArrayGetCount(cf_attributes.get());
  if (num_attributes == 0)
    return false;
  return CFArrayContainsValue(cf_attributes.get(),
                              CFRangeMake(0, num_attributes), attribute) == YES;
}

bool AXAPINode::HasAttribute(const std::string& attribute) const {
  ScopedCFTypeRef<CFStringRef> cf_attribute = StdStringToCFStringRef(attribute);
  return HasAttribute(cf_attribute.get());
}

ValueType AXAPINode::GetAttributeValueType(const std::string& attribute) const {
  if (!HasAttribute(attribute))
    return ValueType::NOT_PRESENT;

  ScopedCFTypeRef<CFStringRef> cf_attribute = StdStringToCFStringRef(attribute);
  ScopedCFTypeRef<CFTypeRef> cf_value;
  AXError err = AXUIElementCopyAttributeValue(
      ax_ui_element_, cf_attribute.get(), cf_value.get_ptr());

  if (err) {
    if (err == kAXErrorNoValue || err == kAXErrorAttributeUnsupported)
      return ValueType::NOT_PRESENT;

    return ValueType::UNKNOWN;
  }

  CFTypeID type_id = CFGetTypeID(cf_value.get());
  return TypeIDToValueType(type_id, cf_value, attribute);
}

ValueType AXAPINode::GetListAttributeElementType(
    const std::string& attribute) const {
  ScopedCFTypeRef<CFStringRef> cf_attribute = StdStringToCFStringRef(attribute);
  ScopedCFTypeRef<CFTypeRef> cf_value;
  AXError err = AXUIElementCopyAttributeValue(
      ax_ui_element_, cf_attribute.get(), cf_value.get_ptr());

  if (err) {
    if (err == kAXErrorNoValue || err == kAXErrorAttributeUnsupported)
      return ValueType::NOT_PRESENT;

    return ValueType::UNKNOWN;
  }
  if (CFArrayGetCount((CFArrayRef)cf_value.get()) == 0) {
    // Can't determine the list type of an empty list, so it gets its own type
    return ValueType::UNKNOWN;
  }

  ScopedCFTypeRef<CFTypeRef> cf_first_value(
      (CFTypeRef)CFArrayGetValueAtIndex((CFArrayRef)cf_value.get(), 0));
  CFRetain(cf_first_value.get());
  CFTypeID first_value_type_id = CFGetTypeID(cf_first_value.get());
  return TypeIDToValueType(first_value_type_id, cf_first_value, attribute);
}

std::string AXAPINode::CopyStringAttributeValue(
    const std::string& attribute) const {
  ScopedCFTypeRef<CFStringRef> cf_attribute = StdStringToCFStringRef(attribute);
  ScopedCFTypeRef<CFTypeRef> cf_value;
  AXError err = AXUIElementCopyAttributeValue(
      ax_ui_element_, cf_attribute.get(), cf_value.get_ptr());

  // For some reason, sometimes an AXUIElement lists an attribute which has no
  // value. Since we can't check for this condition other than getting the
  // attribute, handle this case quietly.
  if (err == kAXErrorNoValue)
    return "";

  if (err) {
    switch (err) {
      case kAXErrorAttributeUnsupported:
        throw std::invalid_argument(
            "Attribute " + attribute +
            " is not supported on this node. Use HasAttribute() or "
            "CopyAttributeValues() to check which attributes are available.");
      default:
        throw std::runtime_error("Attempting to copy value for attribute " +
                                 attribute + " produced error code " +
                                 AXErrorToString(err));
    }
  }

  // TODO: better handling of attributes which return the wrong type.
  // Should throw a useful exception if not a string.
  if (CFGetTypeID(cf_value.get()) != CFStringGetTypeID())
    return "";

  return CFStringRefToStdString((CFStringRef)cf_value.get());
}

int32_t AXAPINode::GetListAttributeValueCount(
    const std::string& attribute) const {
  ScopedCFTypeRef<CFStringRef> cf_attribute = StdStringToCFStringRef(attribute);

  CFIndex count;
  AXError err = AXUIElementGetAttributeValueCount(ax_ui_element_,
                                                  cf_attribute.get(), &count);
  if (err) {
    switch (err) {
      case kAXErrorAttributeUnsupported:
        throw std::invalid_argument(
            "Attribute " + attribute +
            " is not supported on this node. Use HasAttribute() or "
            "CopyAttributeValues() to check which attributes are available.");
      default:
        throw std::runtime_error(
            "Attempting to get value count for attribute " + attribute +
            " produced error code " + AXErrorToString(err));
    }
  }

  return (int32_t)count;
}

std::vector<AXAPINode> AXAPINode::CopyNodeListAttributeValue(
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
            " is not supported on this node. Use HasAttribute() or "
            "CopyAttributeValues() to check which attributes are available.");
      default:
        throw std::runtime_error("Attempting to copy value for attribute " +
                                 attribute + " produced error code " +
                                 AXErrorToString(err));
    }
  }

  // TODO: better handling of attributes which return the wrong type.
  // Should throw a useful exception if not an array, or (any?) element is not
  // an AXUIElement.
  std::vector<AXAPINode> value;
  for (CFIndex i = 0; i < CFArrayGetCount(cf_array.get()); ++i) {
    CFTypeRef cf_ith_value =
        (CFTypeRef)CFArrayGetValueAtIndex(cf_array.get(), i);
    if (CFGetTypeID(cf_ith_value) == AXUIElementGetTypeID()) {
      value.push_back(AXAPINode((AXUIElementRef)CFRetain(cf_ith_value)));
    }
  }

  return value;
}

AXAPINode AXAPINode::CopyNodeListAttributeValueAtIndex(
    const std::string& attribute,
    int index) const {
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
            " is not supported on this node. Use HasAttribute() or "
            "CopyAttributeValues() to check which attributes are available.");
      case kAXErrorIllegalArgument:
        throw std::invalid_argument(
            "Index " + std::to_string(index) +
            " is out of bounds, or the value of " + attribute +
            " is not an array. Use GetListAttributeValueCount() to "
            "check the number of values.");
      default:
        throw std::runtime_error("Attempting to copy value for attribute " +
                                 attribute + " produced error code " +
                                 AXErrorToString(err));
    }
  }

  if (CFArrayGetCount(cf_array.get()) != 1l) {
    throw std::runtime_error("Couldn't get array");
  }
  CFTypeRef cf_ith_value = (CFTypeRef)CFArrayGetValueAtIndex(cf_array.get(), 0);

  // TODO: better handling of attributes which return the wrong type.
  if (CFGetTypeID(cf_ith_value) != AXUIElementGetTypeID())
    return AXAPINode();

  return AXAPINode((AXUIElementRef)CFRetain(cf_ith_value));
}

}  // namespace mac_inspect
