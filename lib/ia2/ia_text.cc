#include "axaccess/ia2/ia_text.h"

#include "axaccess/ia2/win_utils.h"

namespace {
std::string ToPrintableString(std::string str) {
  const std::string ufffc = "\xEF\xBF\xBC";
  const std::string printable_ufffc = "[obj]";
  size_t pos = 0;
  while ((pos = str.find(ufffc, pos)) != std::string::npos) {
    str.replace(pos, ufffc.size(), printable_ufffc);
    pos += printable_ufffc.size();
  }

  return str;
}

}  // namespace

using namespace win_utils;

std::string IAText::GetProperties() {
  auto iface = QueryInterface();
  if (!iface) {
    return std::string();
  }

  std::string result = "Text: ";
  long length = get_nCharacters();
  std::string content;
  if (length < 50) {
    content = get_text(0, length);
  } else {
    content = get_text(0, 20) + "[...]" + get_text(length - 20, length);
  }
  result += "'" + ToPrintableString(content) + "'";
  return result;
}

long IAText::get_caretOffset() {
  if (auto iface = QueryInterface()) {
    long offset;
    if (SUCCEEDED(iface->get_caretOffset(&offset))) {
      return offset;
    }
  }
  return -1;
}

long IAText::get_nCharacters() {
  if (auto iface = QueryInterface()) {
    long count;
    if (SUCCEEDED(iface->get_nCharacters(&count))) {
      return count;
    }
  }
  return 0;
}

std::string IAText::get_text(long start_offset, long end_offset) {
  if (auto iface = QueryInterface()) {
    BSTR bstr_result;
    if (SUCCEEDED(iface->get_text(start_offset, end_offset, &bstr_result))) {
      std::string str_result = BstrToString(bstr_result);
      SysFreeString(bstr_result);
      return str_result;
    }
  }
  return std::string();
}

Microsoft::WRL::ComPtr<IAccessibleText> IAText::QueryInterface() {
  if (node_.IsNull() || !node_.GetIAccessible()) {
    return nullptr;
  }

  Microsoft::WRL::ComPtr<IAccessibleText> iface;
  Microsoft::WRL::ComPtr<IServiceProvider> service_provider;
  HRESULT hr =
      node_.GetIAccessible()->QueryInterface(IID_PPV_ARGS(&service_provider));
  return SUCCEEDED(service_provider->QueryService(IID_IAccessible,
                                                  IID_PPV_ARGS(&iface)))
             ? iface
             : nullptr;
}
