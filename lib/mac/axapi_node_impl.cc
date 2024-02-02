
// TODO: use the C++ API in AXAPINode
std::string AXAPINodeImpl::Role() {
  /*
  CFTypeRef cf_role = nullptr;
  if (AXUIElementCopyAttributeValue(ax_ui_element_, kAXRoleAttribute,
                                    &cf_role) != kAXErrorSuccess) {
    return "";
  }

  return CFStringRefToStdString((CFStringRef)cf_role);
*/
  return "";
}

std::string AXAPINodeImpl::Title() {
  /*
  CFStringRef cf_title = nullptr;
  if (AXUIElementCopyAttributeValue(ax_ui_element_, kAXTitleAttribute,
                                    (CFTypeRef*)&cf_title) != kAXErrorSuccess) {
    return "";
  }

  return CFStringRefToStdString(cf_title);
  */
  return "";
}

long AXAPINodeImpl::ChildCount() {
  /*
  CFArrayRef children_ref;
  if ((AXUIElementCopyAttributeValue(ax_ui_element_, kAXChildrenAttribute,
                                     (CFTypeRef*)&children_ref)) !=
      kAXErrorSuccess) {
    return 0;
  }
  return CFArrayGetCount(children_ref);
  */
  return 0;
}

AXAPINodePtr AXAPINodeImpl::ChildAt(long index) {
  /*
  CFArrayRef children_ref;
  if ((AXUIElementCopyAttributeValue(ax_ui_element_, kAXChildrenAttribute,
                                     (CFTypeRef*)&children_ref)) !=
      kAXErrorSuccess) {
    return nullptr;
  }
  AXUIElementRef child_ref =
      (AXUIElementRef)CFArrayGetValueAtIndex(children_ref, index);
  if (!child_ref)
    return nullptr;
  return AXAPINodePtr(new AXAPINode(child_ref));
  */
  return std::make_unique<AXAPINodeImpl>()
}