#include "axaccess/ia2/ia_node.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

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

}  // Namespace

Microsoft::WRL::ComPtr<IServiceProvider> IANode::GetServiceProvider() {
  if (IsNull()) {
    return nullptr;
  }
  Microsoft::WRL::ComPtr<IServiceProvider> service_provider;
  HRESULT hr = root_->QueryInterface(IID_PPV_ARGS(&service_provider));
  if (FAILED(hr)) {
    throw std::runtime_error(
        "Attempting to get service provider produced error code " +
        HResultErrorToString(hr));
  }
  return service_provider;
}

IANode IANode::CreateRootForName(const std::string& app_name, const int pid) {
  Microsoft::WRL::ComPtr<IAccessible> root = GetAccessibleRoot(app_name, pid);
  if (!root) {
    return nullptr;
  }

  return IANode(root);
}

IANode IANode::CreateRootForPID(const int pid) {
  Microsoft::WRL::ComPtr<IAccessible> root = GetAccessibleRoot("", pid);
  if (!root) {
    return nullptr;
  }

  return IANode(root);
}

IA2 IANode::QueryIA2() {
  Microsoft::WRL::ComPtr<IAccessible2> iface;
  if (auto service_provider = GetServiceProvider()) {
    service_provider->QueryService(IID_IAccessible, IID_PPV_ARGS(&iface));
  }
  return IA2(iface);
}

IAAction IANode::QueryAction() {
  Microsoft::WRL::ComPtr<IAccessibleAction> iface;
  if (auto service_provider = GetServiceProvider()) {
    service_provider->QueryService(IID_IAccessible, IID_PPV_ARGS(&iface));
  }
  return IAAction(iface);
}

IAComponent IANode::QueryComponent() {
  Microsoft::WRL::ComPtr<IAccessibleComponent> iface;
  if (auto service_provider = GetServiceProvider()) {
    service_provider->QueryService(IID_IAccessible, IID_PPV_ARGS(&iface));
  }
  return IAComponent(iface);
}

IAHyperlink IANode::QueryHyperlink() {
  Microsoft::WRL::ComPtr<IAccessibleHyperlink> iface;
  if (auto service_provider = GetServiceProvider()) {
    service_provider->QueryService(IID_IAccessible, IID_PPV_ARGS(&iface));
  }
  return IAHyperlink(iface);
}

IATableCell IANode::QueryTableCell() {
  Microsoft::WRL::ComPtr<IAccessibleTableCell> iface;
  if (auto service_provider = GetServiceProvider()) {
    service_provider->QueryService(IID_IAccessible, IID_PPV_ARGS(&iface));
  }
  return IATableCell(iface);
}

IATable2 IANode::QueryTable2() {
  Microsoft::WRL::ComPtr<IAccessibleTable2> iface;
  if (auto service_provider = GetServiceProvider()) {
    service_provider->QueryService(IID_IAccessible, IID_PPV_ARGS(&iface));
  }
  return IATable2(iface);
}

IAText IANode::QueryText() {
  Microsoft::WRL::ComPtr<IAccessibleText> iface;
  if (auto service_provider = GetServiceProvider()) {
    service_provider->QueryService(IID_IAccessible, IID_PPV_ARGS(&iface));
  }
  return IAText(iface);
}

IAValue IANode::QueryValue() {
  Microsoft::WRL::ComPtr<IAccessibleValue> iface;
  if (auto service_provider = GetServiceProvider()) {
    service_provider->QueryService(IID_IAccessible, IID_PPV_ARGS(&iface));
  }
  return IAValue(iface);
}

bool IANode::IsNull() {
  if (!root_)
    return true;
  return false;
}

std::string IANode::get_accRole() {
  VARIANT ia_role_variant;
  HRESULT hr = root_->get_accRole(child_id_, &ia_role_variant);
  if (FAILED(hr)) {
    throw std::runtime_error(
        "Attempting to call get_accRole produced error code " +
        HResultErrorToString(hr));
  }
  return MSAARoleToString(ia_role_variant.lVal);
}

std::string IANode::get_accName() {
  BSTR bstr_name;
  HRESULT hr = root_->get_accName(child_id_, &bstr_name);
  if (FAILED(hr)) {
    throw std::runtime_error(
        "Attempting to call get_accName produced error code " +
        HResultErrorToString(hr));
  }
  std::string str_name = BstrToString(bstr_name);
  SysFreeString(bstr_name);
  return str_name;
}

std::string IANode::get_accDescription() {
  VARIANT child;
  child.vt = VT_I4;
  child.lVal = V_I4(&child_id_);
  BSTR bstr_description;
  HRESULT hr = root_->get_accDescription(child, &bstr_description);
  if (FAILED(hr) && hr != DISP_E_MEMBERNOTFOUND) {
    throw std::runtime_error(
        "Attempting to call get_accDescription produced error code " +
        HResultErrorToString(hr));
  }
  std::string str_description = BstrToString(bstr_description);
  SysFreeString(bstr_description);
  return str_description;
}

long IANode::get_accChildCount() {
  if (child_id_.intVal != CHILDID_SELF)
    return 0;

  long child_count;
  HRESULT hr;

  hr = root_->get_accChildCount(&child_count);
  if (FAILED(hr)) {
    throw std::runtime_error(
        "Attempting to get accessible child count produced error code " +
        HResultErrorToString(hr));
  }
  return child_count;
}

IANode IANode::AccessibleChildAt(int index) {
  if (child_id_.intVal != CHILDID_SELF) {
    return IANode();
  }

  std::unique_ptr<VARIANT[]> children(new VARIANT[1]);
  HRESULT hr;
  long returnCount;
  hr =
      ::AccessibleChildren(root_.Get(), index, 1, children.get(), &returnCount);
  if (FAILED(hr)) {
    throw std::runtime_error("Attempting to get accessible child at index " +
                             std::to_string(index) + " produced error code " +
                             HResultErrorToString(hr));
  }
  VARIANT vt_child = children[0];

  if (vt_child.vt != VT_DISPATCH) {
    // This is a "partial child", which can have a name and role but not much
    // else
    return IANode(root_, vt_child);
  }

  IDispatch* pdisp = vt_child.pdispVal;
  Microsoft::WRL::ComPtr<IAccessible> accessible;
  hr =
      pdisp->QueryInterface(IID_IAccessible, (void**)accessible.GetAddressOf());
  pdisp->Release();
  if (FAILED(hr)) {
    throw std::runtime_error(
        "Attempting to get IAccessible interface for child at index " +
        std::to_string(index) + " produced error code " +
        HResultErrorToString(hr));
  }
  return IANode(accessible);
}

long IANode::get_accState() {
  HRESULT hr;
  VARIANT state;
  VARIANT child;
  child.vt = VT_I4;
  child.lVal = V_I4(&child_id_);
  hr = root_->get_accState(child, &state);
  if (FAILED(hr)) {
    throw std::runtime_error(
        "Attempting to get accessible state produced error code " +
        HResultErrorToString(hr));
  }
  return V_I4(&state);
}

std::vector<std::string> IANode::GetStates() {
  long states = get_accState();
  std::vector<std::string> state_strings;
  if (states & STATE_SYSTEM_ALERT_HIGH) {
    state_strings.push_back("ALERT_HIGH");
  }
  if (states & STATE_SYSTEM_ALERT_MEDIUM) {
    state_strings.push_back("ALERT_MEDIUM");
  }
  if (states & STATE_SYSTEM_ALERT_LOW) {
    state_strings.push_back("ALERT_LOW");
  }
  if (states & STATE_SYSTEM_ANIMATED) {
    state_strings.push_back("ANIMATED");
  }
  if (states & STATE_SYSTEM_BUSY) {
    state_strings.push_back("BUSY");
  }
  if (states & STATE_SYSTEM_CHECKED) {
    state_strings.push_back("CHECKED");
  }
  if (states & STATE_SYSTEM_COLLAPSED) {
    state_strings.push_back("COLLAPSED");
  }
  if (states & STATE_SYSTEM_DEFAULT) {
    state_strings.push_back("DEFAULT");
  }
  if (states & STATE_SYSTEM_EXPANDED) {
    state_strings.push_back("EXPANDED");
  }
  if (states & STATE_SYSTEM_EXTSELECTABLE) {
    state_strings.push_back("EXTSELECTABLE");
  }
  if (states & STATE_SYSTEM_FLOATING) {
    state_strings.push_back("FLOATING");
  }
  if (states & STATE_SYSTEM_FOCUSABLE) {
    state_strings.push_back("FOCUSABLE");
  }
  if (states & STATE_SYSTEM_FOCUSED) {
    state_strings.push_back("FOCUSED");
  }
  if (states & STATE_SYSTEM_HASPOPUP) {
    state_strings.push_back("HASPOPUP");
  }
  if (states & STATE_SYSTEM_HOTTRACKED) {
    state_strings.push_back("HOTTRACKED");
  }
  if (states & STATE_SYSTEM_INVISIBLE) {
    state_strings.push_back("INVISIBLE");
  }
  if (states & STATE_SYSTEM_LINKED) {
    state_strings.push_back("LINKED");
  }
  if (states & STATE_SYSTEM_MARQUEED) {
    state_strings.push_back("MARQUEED");
  }
  if (states & STATE_SYSTEM_MIXED) {
    state_strings.push_back("MIXED");
  }
  if (states & STATE_SYSTEM_MOVEABLE) {
    state_strings.push_back("MOVEABLE");
  }
  if (states & STATE_SYSTEM_MULTISELECTABLE) {
    state_strings.push_back("MULTISELECTABLE");
  }
  if (states & STATE_SYSTEM_OFFSCREEN) {
    state_strings.push_back("OFFSCREEN");
  }
  if (states & STATE_SYSTEM_PRESSED) {
    state_strings.push_back("PRESSED");
  }
  if (states & STATE_SYSTEM_PROTECTED) {
    state_strings.push_back("PROTECTED");
  }
  if (states & STATE_SYSTEM_READONLY) {
    state_strings.push_back("READONLY");
  }
  if (states & STATE_SYSTEM_SELECTABLE) {
    state_strings.push_back("SELECTABLE");
  }
  if (states & STATE_SYSTEM_SELECTED) {
    state_strings.push_back("SELECTED");
  }
  if (states & STATE_SYSTEM_SELFVOICING) {
    state_strings.push_back("SELFVOICING");
  }
  if (states & STATE_SYSTEM_SIZEABLE) {
    state_strings.push_back("SIZEABLE");
  }
  if (states & STATE_SYSTEM_TRAVERSED) {
    state_strings.push_back("TRAVERSED");
  }
  if (states & STATE_SYSTEM_UNAVAILABLE) {
    state_strings.push_back("UNAVAILABLE");
  }

  return state_strings;
}
