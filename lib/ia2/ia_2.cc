#include "axaccess/ia2/ia_2.h"

#include "axaccess/ia2/win_utils.h"

namespace {
std::string RoleToString(LONG role) {
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
}  // namespace

using namespace win_utils;

IA2::IA2(IANode node) {
  if (auto service_provider = node.GetServiceProvider()) {
    service_provider->QueryService(IID_IAccessible, IID_PPV_ARGS(&iface_));
  }
}

std::string IA2::GetProperties() {
  if (IsNull()) {
    return "IAccessible2: Not implemented";
  }

  std::string result = "IAccessible2: ";
  GroupPosition group_position = get_groupPosition();
  if (!group_position.IsEmpty()) {
    result += "Position=" + std::to_string(group_position.position) + ", " +
              "Setsize=" + std::to_string(group_position.setsize) + ", " +
              "Level=" + std::to_string(group_position.level) + "; ";
  }

  std::vector<std::string> relations = GetRelations();
  if (!relations.empty()) {
    result += "Relations=";
    for (auto relation : relations) {
      result += relation + ", ";
    }
    size_t pos = result.find_last_not_of(", ");
    if (pos != std::string::npos) {
      result = result.substr(0, pos + 1);
    }
    result += "; ";
  }

  result += "Attributes=" + get_attributes();
  return result;
}

std::string IA2::get_attributes() {
  if (iface_) {
    BSTR bstr_result;
    if SUCCEEDED (iface_->get_attributes(&bstr_result)) {
      std::string str_result = BstrToString(bstr_result);
      SysFreeString(bstr_result);
      return str_result;
    }
  }

  return std::string();
}

GroupPosition IA2::get_groupPosition() {
  if (iface_) {
    GroupPosition result;
    long level, setsize, position;
    if SUCCEEDED (iface_->get_groupPosition(&level, &setsize, &position)) {
      return GroupPosition(level, setsize, position);
    }
  }
  return GroupPosition();
}

std::vector<std::string> IA2::GetRelations() {
  std::vector<std::string> relation_strings;
  if (!iface_) {
    return relation_strings;
  }

  long count;
  if (FAILED(iface_->get_nRelations(&count))) {
    return relation_strings;
  }

  for (long i = 0; i < count; ++i) {
    Microsoft::WRL::ComPtr<IAccessibleRelation> relation;
    if (SUCCEEDED(iface_->get_relation(i, &relation))) {
      BSTR bstr_type;
      if (SUCCEEDED(relation->get_relationType(&bstr_type))) {
        relation_strings.push_back(BstrToString(bstr_type));
        SysFreeString(bstr_type);
      }
    }
  }
  return relation_strings;
}

std::string IA2::role() {
  if (iface_) {
    LONG role = 0;
    if (SUCCEEDED(iface_->role(&role))) {
      return RoleToString(role);
    }
  }
  return "";
}

long IA2::get_states() {
  if (iface_) {
    long result;
    if SUCCEEDED (iface_->get_states(&result)) {
      return result;
    }
  }
  return 0;
}

std::vector<std::string> IA2::GetStates() {
  long state = get_states();
  std::vector<std::string> state_strings;
  if (state & IA2_STATE_ACTIVE) {
    state_strings.push_back("ACTIVE");
  }
  if (state & IA2_STATE_ARMED) {
    state_strings.push_back("ARMED");
  }
  if (state & IA2_STATE_CHECKABLE) {
    state_strings.push_back("CHECKABLE");
  }
  if (state & IA2_STATE_DEFUNCT) {
    state_strings.push_back("DEFUNCT");
  }
  if (state & IA2_STATE_EDITABLE) {
    state_strings.push_back("EDITABLE");
  }
  if (state & IA2_STATE_HORIZONTAL) {
    state_strings.push_back("HORIZONTAL");
  }
  if (state & IA2_STATE_ICONIFIED) {
    state_strings.push_back("ICONIFIED");
  }
  if (state & IA2_STATE_INVALID_ENTRY) {
    state_strings.push_back("INVALID_ENTRY");
  }
  if (state & IA2_STATE_MANAGES_DESCENDANTS) {
    state_strings.push_back("MANAGES_DESCENDANTS");
  }
  if (state & IA2_STATE_MODAL) {
    state_strings.push_back("MODAL");
  }
  if (state & IA2_STATE_MULTI_LINE) {
    state_strings.push_back("MULTI_LINE");
  }
  if (state & IA2_STATE_OPAQUE) {
    state_strings.push_back("OPAQUE");
  }
  if (state & IA2_STATE_PINNED) {
    state_strings.push_back("PINNED");
  }
  if (state & IA2_STATE_REQUIRED) {
    state_strings.push_back("REQUIRED");
  }
  if (state & IA2_STATE_SELECTABLE_TEXT) {
    state_strings.push_back("SELECTABLE_TEXT");
  }
  if (state & IA2_STATE_SINGLE_LINE) {
    state_strings.push_back("SINGLE_LINE");
  }
  if (state & IA2_STATE_STALE) {
    state_strings.push_back("STALE");
  }
  if (state & IA2_STATE_SUPPORTS_AUTOCOMPLETION) {
    state_strings.push_back("SUPPORTS_AUTOCOMPLETION");
  }
  if (state & IA2_STATE_TRANSIENT) {
    state_strings.push_back("TRANSIENT");
  }
  if (state & IA2_STATE_VERTICAL) {
    state_strings.push_back("VERTICAL");
  }

  return state_strings;
}
