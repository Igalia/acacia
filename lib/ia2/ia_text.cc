#include "acacia/ia2/ia_text.h"

#include <stdexcept>

#include "lib/ia2/win_utils.h"

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

namespace acacia {

std::string IAText::toString() {
  if (isNull()) {
    return "Text: Not implemented";
  }

  std::string result = "Text: ";
  long length = getNCharacters();
  std::string content;
  if (length < 50) {
    content = getText(0, length);
  } else {
    content = getText(0, 20) + "[...]" + getText(length - 20, length);
  }
  result += "'" + ToPrintableString(content) + "'";
  return result;
}

long IAText::getCaretOffset() {
  if (iface_) {
    long offset;
    HRESULT hr = iface_->get_caretOffset(&offset);
    if (FAILED(hr)) {
      throw std::runtime_error("ERROR: get_caretOffset failed: " +
                               HResultErrorToString(hr));
    }
    return offset;
  }
  return -1;
}

long IAText::getNCharacters() {
  if (iface_) {
    long count;
    HRESULT hr = iface_->get_nCharacters(&count);
    if (FAILED(hr)) {
      throw std::runtime_error("ERROR: get_nCharacters failed: " +
                               HResultErrorToString(hr));
    }
    return count;
  }
  return 0;
}

std::string IAText::getText(long start_offset, long end_offset) {
  if (iface_) {
    BSTR bstr_result;
    HRESULT hr = iface_->get_text(start_offset, end_offset, &bstr_result);
    if (FAILED(hr)) {
      throw std::runtime_error("ERROR: get_background failed: " +
                               HResultErrorToString(hr));
    }
    std::string str_result = BstrToString(bstr_result);
    SysFreeString(bstr_result);
    return str_result;
  }
  return std::string();
}

}  // namespace acacia
