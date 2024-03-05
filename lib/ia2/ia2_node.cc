#include "axaccess/ia2/ia2_node.h"

#include <iostream>
#include <stdexcept>
#include <string>

#include "axaccess/ia2/win_utils.h"
#include "third_party/ia2/include/ia2/ia2_api_all.h"

using namespace win_utils;

namespace {

std::string MSAARoleToString(LONG role) {
  switch (role) {
    case ROLE_SYSTEM_TITLEBAR:
      return "ROLE_SYSTEM_TITLEBAR";
    case ROLE_SYSTEM_MENUBAR:
      return "ROLE_SYSTEM_MENUBAR";
    case ROLE_SYSTEM_SCROLLBAR:
      return "ROLE_SYSTEM_SCROLLBAR";
    case ROLE_SYSTEM_GRIP:
      return "ROLE_SYSTEM_GRIP";
    case ROLE_SYSTEM_SOUND:
      return "ROLE_SYSTEM_SOUND";
    case ROLE_SYSTEM_CURSOR:
      return "ROLE_SYSTEM_CURSOR";
    case ROLE_SYSTEM_CARET:
      return "ROLE_SYSTEM_CARET";
    case ROLE_SYSTEM_ALERT:
      return "ROLE_SYSTEM_ALERT";
    case ROLE_SYSTEM_WINDOW:
      return "ROLE_SYSTEM_WINDOW";
    case ROLE_SYSTEM_CLIENT:
      return "ROLE_SYSTEM_CLIENT";
    case ROLE_SYSTEM_MENUPOPUP:
      return "ROLE_SYSTEM_MENUPOPUP";
    case ROLE_SYSTEM_MENUITEM:
      return "ROLE_SYSTEM_MENUITEM";
    case ROLE_SYSTEM_TOOLTIP:
      return "ROLE_SYSTEM_TOOLTIP";
    case ROLE_SYSTEM_APPLICATION:
      return "ROLE_SYSTEM_APPLICATION";
    case ROLE_SYSTEM_DOCUMENT:
      return "ROLE_SYSTEM_DOCUMENT";
    case ROLE_SYSTEM_PANE:
      return "ROLE_SYSTEM_PANE";
    case ROLE_SYSTEM_CHART:
      return "ROLE_SYSTEM_CHART";
    case ROLE_SYSTEM_DIALOG:
      return "ROLE_SYSTEM_DIALOG";
    case ROLE_SYSTEM_BORDER:
      return "ROLE_SYSTEM_BORDER";
    case ROLE_SYSTEM_GROUPING:
      return "ROLE_SYSTEM_GROUPING";
    case ROLE_SYSTEM_SEPARATOR:
      return "ROLE_SYSTEM_SEPARATOR";
    case ROLE_SYSTEM_TOOLBAR:
      return "ROLE_SYSTEM_TOOLBAR";
    case ROLE_SYSTEM_STATUSBAR:
      return "ROLE_SYSTEM_STATUSBAR";
    case ROLE_SYSTEM_TABLE:
      return "ROLE_SYSTEM_TABLE";
    case ROLE_SYSTEM_COLUMNHEADER:
      return "ROLE_SYSTEM_COLUMNHEADER";
    case ROLE_SYSTEM_ROWHEADER:
      return "ROLE_SYSTEM_ROWHEADER";
    case ROLE_SYSTEM_COLUMN:
      return "ROLE_SYSTEM_COLUMN";
    case ROLE_SYSTEM_ROW:
      return "ROLE_SYSTEM_ROW";
    case ROLE_SYSTEM_CELL:
      return "ROLE_SYSTEM_CEL";
    case ROLE_SYSTEM_LINK:
      return "ROLE_SYSTEM_LINK";
    case ROLE_SYSTEM_HELPBALLOON:
      return "ROLE_SYSTEM_HELPBALLOON";
    case ROLE_SYSTEM_CHARACTER:
      return "ROLE_SYSTEM_CHARACTER";
    case ROLE_SYSTEM_LIST:
      return "ROLE_SYSTEM_LIST";
    case ROLE_SYSTEM_LISTITEM:
      return "ROLE_SYSTEM_LISTITEM";
    case ROLE_SYSTEM_OUTLINE:
      return "ROLE_SYSTEM_OUTLINE";
    case ROLE_SYSTEM_OUTLINEITEM:
      return "ROLE_SYSTEM_OUTLINEITEM";
    case ROLE_SYSTEM_PAGETAB:
      return "ROLE_SYSTEM_PAGETAB";
    case ROLE_SYSTEM_PROPERTYPAGE:
      return "ROLE_SYSTEM_PROPERTYPAGE";
    case ROLE_SYSTEM_INDICATOR:
      return "ROLE_SYSTEM_INDICATOR";
    case ROLE_SYSTEM_GRAPHIC:
      return "ROLE_SYSTEM_GRAPHIC";
    case ROLE_SYSTEM_STATICTEXT:
      return "ROLE_SYSTEM_STATICTEXT";
    case ROLE_SYSTEM_TEXT:
      return "ROLE_SYSTEM_TEXT";
    case ROLE_SYSTEM_PUSHBUTTON:
      return "ROLE_SYSTEM_PUSHBUTTON";
    case ROLE_SYSTEM_CHECKBUTTON:
      return "ROLE_SYSTEM_CHECKBUTTON";
    case ROLE_SYSTEM_RADIOBUTTON:
      return "ROLE_SYSTEM_RADIOBUTTON";
    case ROLE_SYSTEM_COMBOBOX:
      return "ROLE_SYSTEM_COMBOBOX";
    case ROLE_SYSTEM_DROPLIST:
      return "ROLE_SYSTEM_DROPLIST";
    case ROLE_SYSTEM_PROGRESSBAR:
      return "ROLE_SYSTEM_PROGRESSBAR";
    case ROLE_SYSTEM_DIAL:
      return "ROLE_SYSTEM_DIAL";
    case ROLE_SYSTEM_HOTKEYFIELD:
      return "ROLE_SYSTEM_HOTKEYFIELD";
    case ROLE_SYSTEM_SLIDER:
      return "ROLE_SYSTEM_SLIDER";
    case ROLE_SYSTEM_SPINBUTTON:
      return "ROLE_SYSTEM_SPINBUTTON";
    case ROLE_SYSTEM_DIAGRAM:
      return "ROLE_SYSTEM_DIAGRAM";
    case ROLE_SYSTEM_ANIMATION:
      return "ROLE_SYSTEM_ANIMATION";
    case ROLE_SYSTEM_EQUATION:
      return "ROLE_SYSTEM_EQUATION";
    case ROLE_SYSTEM_BUTTONDROPDOWN:
      return "ROLE_SYSTEM_BUTTONDROPDOWN";
    case ROLE_SYSTEM_BUTTONMENU:
      return "ROLE_SYSTEM_BUTTONMENU";
    case ROLE_SYSTEM_BUTTONDROPDOWNGRID:
      return "ROLE_SYSTEM_BUTTONDROPDOWNGRID";
    case ROLE_SYSTEM_WHITESPACE:
      return "ROLE_SYSTEM_WHITESPACE";
    case ROLE_SYSTEM_PAGETABLIST:
      return "ROLE_SYSTEM_PAGETABLIST";
    case ROLE_SYSTEM_CLOCK:
      return "ROLE_SYSTEM_CLOCK";
    case ROLE_SYSTEM_SPLITBUTTON:
      return "ROLE_SYSTEM_SPLITBUTTON";
    case ROLE_SYSTEM_IPADDRESS:
      return "ROLE_SYSTEM_IPADDRESS";
    case ROLE_SYSTEM_OUTLINEBUTTON:
      return "ROLE_SYSTEM_OUTLINEBUTTON";
    default:
      return "";
  }
}

std::string IA2RoleToString(LONG role) {
  std::string msaa_role = MSAARoleToString(role);
  if (!msaa_role.empty()) {
    return msaa_role;
  }
  switch (role) {
    case IA2_ROLE_CANVAS:
      return "IA2_ROLE_CANVAS";
    case IA2_ROLE_CAPTION:
      return "IA2_ROLE_CAPTION";
    case IA2_ROLE_CHECK_MENU_ITEM:
      return "IA2_ROLE_CHECK_MENU_ITEM";
    case IA2_ROLE_COLOR_CHOOSER:
      return "IA2_ROLE_COLOR_CHOOSER";
    case IA2_ROLE_DATE_EDITOR:
      return "IA2_ROLE_DATE_EDITOR";
    case IA2_ROLE_DESKTOP_ICON:
      return "IA2_ROLE_DESKTOP_ICON";
    case IA2_ROLE_DESKTOP_PANE:
      return "IA2_ROLE_DESKTOP_PANE";
    case IA2_ROLE_DIRECTORY_PANE:
      return "IA2_ROLE_DIRECTORY_PANE";
    case IA2_ROLE_EDITBAR:
      return "IA2_ROLE_EDITBAR";
    case IA2_ROLE_EMBEDDED_OBJECT:
      return "IA2_ROLE_EMBEDDED_OBJECT";
    case IA2_ROLE_ENDNOTE:
      return "IA2_ROLE_ENDNOTE";
    case IA2_ROLE_FILE_CHOOSER:
      return "IA2_ROLE_FILE_CHOOSER";
    case IA2_ROLE_FONT_CHOOSER:
      return "IA2_ROLE_FONT_CHOOSER";
    case IA2_ROLE_FOOTER:
      return "IA2_ROLE_FOOTER";
    case IA2_ROLE_FOOTNOTE:
      return "IA2_ROLE_FOOTNOTE";
    case IA2_ROLE_FORM:
      return "IA2_ROLE_FORM";
    case IA2_ROLE_FRAME:
      return "IA2_ROLE_FRAME";
    case IA2_ROLE_GLASS_PANE:
      return "IA2_ROLE_GLASS_PANE";
    case IA2_ROLE_HEADER:
      return "IA2_ROLE_HEADER";
    case IA2_ROLE_HEADING:
      return "IA2_ROLE_HEADING";
    case IA2_ROLE_ICON:
      return "IA2_ROLE_ICON";
    case IA2_ROLE_IMAGE_MAP:
      return "IA2_ROLE_IMAGE_MAP";
    case IA2_ROLE_INPUT_METHOD_WINDOW:
      return "IA2_ROLE_INPUT_METHOD_WINDOW";
    case IA2_ROLE_INTERNAL_FRAME:
      return "IA2_ROLE_INTERNAL_FRAME";
    case IA2_ROLE_LABEL:
      return "IA2_ROLE_LABEL";
    case IA2_ROLE_LAYERED_PANE:
      return "IA2_ROLE_LAYERED_PANE";
    case IA2_ROLE_NOTE:
      return "IA2_ROLE_NOTE";
    case IA2_ROLE_OPTION_PANE:
      return "IA2_ROLE_OPTION_PANE";
    case IA2_ROLE_PAGE:
      return "IA2_ROLE_PAGE";
    case IA2_ROLE_PARAGRAPH:
      return "IA2_ROLE_PARAGRAPH";
    case IA2_ROLE_RADIO_MENU_ITEM:
      return "IA2_ROLE_RADIO_MENU_ITEM";
    case IA2_ROLE_REDUNDANT_OBJECT:
      return "IA2_ROLE_REDUNDANT_OBJECT";
    case IA2_ROLE_ROOT_PANE:
      return "IA2_ROLE_ROOT_PANE";
    case IA2_ROLE_RULER:
      return "IA2_ROLE_RULER";
    case IA2_ROLE_SCROLL_PANE:
      return "IA2_ROLE_SCROLL_PANE";
    case IA2_ROLE_SECTION:
      return "IA2_ROLE_SECTION";
    case IA2_ROLE_SHAPE:
      return "IA2_ROLE_SHAPE";
    case IA2_ROLE_SPLIT_PANE:
      return "IA2_ROLE_SPLIT_PANE";
    case IA2_ROLE_TEAR_OFF_MENU:
      return "IA2_ROLE_TEAR_OFF_MENU";
    case IA2_ROLE_TERMINAL:
      return "IA2_ROLE_TERMINAL";
    case IA2_ROLE_TEXT_FRAME:
      return "IA2_ROLE_TEXT_FRAME";
    case IA2_ROLE_TOGGLE_BUTTON:
      return "IA2_ROLE_TOGGLE_BUTTON";
    case IA2_ROLE_UNKNOWN:
      return "IA2_ROLE_UNKNOWN";
    case IA2_ROLE_VIEW_PORT:
      return "IA2_ROLE_VIEW_PORT";
    case IA2_ROLE_COMPLEMENTARY_CONTENT:
      return "IA2_ROLE_COMPLEMENTARY_CONTENT";
    case IA2_ROLE_LANDMARK:
      return "IA2_ROLE_LANDMARK";
    case IA2_ROLE_LEVEL_BAR:
      return "IA2_ROLE_LEVEL_BAR";
    case IA2_ROLE_CONTENT_DELETION:
      return "IA2_ROLE_CONTENT_DELETION";
    case IA2_ROLE_CONTENT_INSERTION:
      return "IA2_ROLE_CONTENT_INSERTION";
    case IA2_ROLE_BLOCK_QUOTE:
      return "IA2_ROLE_BLOCK_QUOTE";
    case IA2_ROLE_MARK:
      return "IA2_ROLE_MARK";
    case IA2_ROLE_SUGGESTION:
      return "IA2_ROLE_SUGGESTION";
    case IA2_ROLE_COMMENT:
      return "IA2_ROLE_COMMENT";
    default:
      return "";
  }
}
}  // Namespace

IA2NodePtr IA2Node::CreateRootForName(const std::string& app_name,
                                      const int pid) {
  Microsoft::WRL::ComPtr<IAccessible> root = GetAccessibleRoot(app_name, pid);
  if (!root) {
    return nullptr;
  }

  return std::make_unique<IA2Node>(IA2Node(root));
}

IA2NodePtr IA2Node::CreateRootForPID(const int pid) {
  Microsoft::WRL::ComPtr<IAccessible> root = GetAccessibleRoot("", pid);
  if (!root) {
    return nullptr;
  }

  return std::make_unique<IA2Node>(IA2Node(root));
}

std::string IA2Node::get_accRole() {
  VARIANT ia_role_variant;
  if (SUCCEEDED(root_->get_accRole(child_id_, &ia_role_variant))) {
    return MSAARoleToString(ia_role_variant.lVal);
  }
  return "";
}

std::string IA2Node::get_accName() {
  BSTR bstr_name;
  if (SUCCEEDED(root_->get_accName(child_id_, &bstr_name))) {
    std::string str_name = BstrToString(bstr_name);
    SysFreeString(bstr_name);
    return str_name;
  }
  return "";
}

// TODO: Break these out to it's own IAccessible2 wrapper object. #94
// Additionally, getting the interface should be it's own utility function.
std::string IA2Node::ia2_role() {
  Microsoft::WRL::ComPtr<IAccessible2> ia2;

  Microsoft::WRL::ComPtr<IServiceProvider> service_provider;
  HRESULT hr = root_->QueryInterface(IID_PPV_ARGS(&service_provider));
  hr = service_provider->QueryService(IID_IAccessible, IID_PPV_ARGS(&ia2));

  // TODO: for objects outside of "OBJID_CLIENT", IA2 is not implemented.
  // We will get hr == E_INVALIDARG. However, we would still like to get
  // MSAA the role and name. Fail silently for now.
  if (hr == S_OK) {
    LONG role = 0;
    if (SUCCEEDED(ia2->role(&role))) {
      return IA2RoleToString(role);
    }
  }
  return "";
}

long IA2Node::get_accChildCount() {
  if (child_id_.intVal != CHILDID_SELF)
    return 0;

  long child_count;
  HRESULT hr;

  hr = root_->get_accChildCount(&child_count);
  if (FAILED(hr)) {
    throw std::invalid_argument(
        "Attempting to get accessible child count produced error code " +
        HResultErrorToString(hr));
  }
  return child_count;
}

IA2NodePtr IA2Node::AccessibleChildAt(int index) {
  if (child_id_.intVal != CHILDID_SELF) {
    return nullptr;
  }

  std::unique_ptr<VARIANT[]> children(new VARIANT[1]);
  HRESULT hr;
  long returnCount;
  hr = AccessibleChildren(root_.Get(), index, 1, children.get(), &returnCount);
  if (hr != S_OK) {
    throw std::invalid_argument(
        "Attempting to get accessible child at index " + std::to_string(index) +
        " produced error code " + HResultErrorToString(hr));
  }
  VARIANT vt_child = children[0];

  if (vt_child.vt != VT_DISPATCH) {
    // This is a "partial child", which can have a name and role but not much
    // else
    return std::make_unique<IA2Node>(IA2Node(root_, vt_child));
  }

  IDispatch* pdisp = vt_child.pdispVal;
  IAccessible* accessible = NULL;
  hr = pdisp->QueryInterface(IID_IAccessible, (void**)&accessible);
  pdisp->Release();
  if (hr != S_OK) {
    throw std::invalid_argument(
        "Attempting to get IAccessible interface for child at index " +
        std::to_string(index) + " produced error code " +
        HResultErrorToString(hr));
  }
  return std::make_unique<IA2Node>(IA2Node(accessible));
}
