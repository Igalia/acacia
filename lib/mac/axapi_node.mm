#include "include/axaccess/mac/axapi_node.h"

#import <Foundation/Foundation.h>

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using std::cerr;

namespace {

template <typename T>
class ScopedCFTypeRef {
 public:
  ScopedCFTypeRef() = default;
  ScopedCFTypeRef(T ref) : ref_(ref) {}

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
}  // namespace

namespace mac_inspect {

AXAPINode::AXAPINode() {}

AXAPINode::AXAPINode(AXUIElementRef ax_ui_element)
    : ax_ui_element_((AXUIElementRef)CFRetain(ax_ui_element)) {}

AXAPINode::AXAPINode(const AXAPINode& other)
    : ax_ui_element_((AXUIElementRef)CFRetain(other.ax_ui_element_)) {}

AXAPINode::~AXAPINode() {
  CFRelease(ax_ui_element_);
}

AXAPINode AXAPINode::CreateForPID(int pid) {
  AXUIElementRef root_ax_ui_element = AXUIElementCreateApplication((pid_t)pid);
  return AXAPINode(root_ax_ui_element);
}

std::vector<std::string> AXAPINode::CopyAttributeNames() const {
  ScopedCFTypeRef<CFArrayRef> cf_attributes;
  AXError err =
      AXUIElementCopyAttributeNames(ax_ui_element_, cf_attributes.get_ptr());
  std::vector<std::string> attributes;
  if (err) {
    throw std::invalid_argument(
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
    throw std::invalid_argument(
        "Attempting to check for presence of attribute " +
        CFStringRefToStdString(attribute) + " produced error code " +
        AXErrorToString(err));
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

std::string AXAPINode::CopyStringAttributeValue(
    const std::string& attribute) const {
  ScopedCFTypeRef<CFStringRef> cf_attribute = StdStringToCFStringRef(attribute);
  ScopedCFTypeRef<CFTypeRef> cf_value;
  AXError err = AXUIElementCopyAttributeValue(
      ax_ui_element_, cf_attribute.get(), cf_value.get_ptr());

  if (err == kAXErrorNoValue)
    return "";

  if (err) {
    throw std::invalid_argument("Attempting to copy value for attribute " +
                                attribute + " produced error code " +
                                AXErrorToString(err));
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
  if (!HasAttribute(cf_attribute.get()))
    return 0;

  CFIndex count;
  AXError err = AXUIElementGetAttributeValueCount(ax_ui_element_,
                                                  cf_attribute.get(), &count);
  if (err) {
    throw std::invalid_argument("Attempting to get value count for attribute " +
                                attribute + " produced error code " +
                                AXErrorToString(err));
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
    throw std::invalid_argument("Attempting to copy value for attribute " +
                                attribute + " produced error code " +
                                AXErrorToString(err));
  }

  // TODO: better handling of attributes which return the wrong type.
  // Should throw a useful exception if not an array, or (any?) element is not
  // an AXUIElement.
  std::vector<AXAPINode> value;
  for (CFIndex i = 0; i < CFArrayGetCount(cf_array.get()); ++i) {
    CFTypeRef cf_ith_value =
        (CFTypeRef)CFArrayGetValueAtIndex(cf_array.get(), i);
    if (CFGetTypeID(cf_ith_value) == AXUIElementGetTypeID()) {
      value.push_back(AXAPINode((AXUIElementRef)cf_ith_value));
    }
  }

  return value;
}

AXAPINode AXAPINode::CopyNodeListAttributeValueAtIndex(
    const std::string& attribute,
    int32_t index) const {
  ScopedCFTypeRef<CFStringRef> cf_attribute = StdStringToCFStringRef(attribute);
  ScopedCFTypeRef<CFArrayRef> cf_array;
  AXError err =
      AXUIElementCopyAttributeValues(ax_ui_element_, cf_attribute.get(),
                                     (CFIndex)index, 1l, cf_array.get_ptr());

  if (err) {
    throw std::invalid_argument("Attempting to copy value for attribute " +
                                attribute + " produced error code " +
                                AXErrorToString(err));
  }

  if (CFArrayGetCount(cf_array.get()) != 1l) {
    throw std::runtime_error("Couldn't get array");
  }
  CFTypeRef cf_ith_value = (CFTypeRef)CFArrayGetValueAtIndex(cf_array.get(), 0);

  // TODO: better handling of attributes which return the wrong type
  if (CFGetTypeID(cf_ith_value) != AXUIElementGetTypeID())
    return AXAPINode();

  return AXAPINode((AXUIElementRef)cf_ith_value);
}

}  // namespace mac_inspect
