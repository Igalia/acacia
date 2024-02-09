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

std::vector<AXAPINode> AXAPINode::CopyNodeListAttributeValue(
    const std::string& attribute) const {
  ScopedCFTypeRef<CFStringRef> cf_attribute = StdStringToCFStringRef(attribute);
  ScopedCFTypeRef<CFTypeRef> cf_value;

  AXError err = AXUIElementCopyAttributeValue(
      ax_ui_element_, cf_attribute.get(), cf_value.get_ptr());

  if (err) {
    throw std::invalid_argument("Attempting to copy value for attribute " +
                                attribute + " produced error code " +
                                AXErrorToString(err));
  }

  // TODO: better handling of attributes which return the wrong type.
  // Should throw a useful exception if not an array, or (any?) element is not
  // an AXUIElement.
  std::vector<AXAPINode> value;
  if (CFGetTypeID(cf_value.get()) == CFArrayGetTypeID()) {
    CFArrayRef cf_value_array = (CFArrayRef)cf_value.get();
    for (CFIndex i = 0; i < CFArrayGetCount(cf_value_array); ++i) {
      CFTypeRef cf_ith_value =
          (CFTypeRef)CFArrayGetValueAtIndex(cf_value_array, i);
      if (CFGetTypeID(cf_ith_value) == AXUIElementGetTypeID()) {
        value.push_back(AXAPINode((AXUIElementRef)cf_ith_value));
      }
    }
  }

  return value;
}

AXAPINode AXAPINode::CopyNodeListAttributeValueAtIndex(
    const std::string& attribute,
    int32_t index) const {
  ScopedCFTypeRef<CFStringRef> cf_attribute = StdStringToCFStringRef(attribute);
  ScopedCFTypeRef<CFTypeRef> cf_value;
  AXError err = AXUIElementCopyAttributeValue(
      ax_ui_element_, cf_attribute.get(), cf_value.get_ptr());

  if (err) {
    throw std::invalid_argument("Attempting to copy value for attribute " +
                                attribute + " produced error code " +
                                AXErrorToString(err));
  }

  // TODO: better handling of attributes which return the wrong type
  if (CFGetTypeID(cf_value.get()) != CFArrayGetTypeID())
    return AXAPINode();

  CFArrayRef cf_value_array = (CFArrayRef)cf_value.get();
  CFTypeRef cf_ith_value =
      (CFTypeRef)CFArrayGetValueAtIndex(cf_value_array, index);

  // TODO: better handling of attributes which return the wrong type
  if (CFGetTypeID(cf_ith_value) != AXUIElementGetTypeID())
    return AXAPINode();

  return AXAPINode((AXUIElementRef)cf_ith_value);
}

}  // namespace mac_inspect
