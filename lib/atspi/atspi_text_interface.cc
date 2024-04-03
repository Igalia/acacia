#include <acacia/atspi/atspi_text_interface.h>

#include <assert.h>
#include <iostream>
#include <stdexcept>
#include <string>

static std::string ToPrintableString(std::string str) {
  const std::string ufffc = "\xEF\xBF\xBC";
  const std::string printable_ufffc = "[obj]";
  size_t pos = 0;
  while ((pos = str.find(ufffc, pos)) != std::string::npos) {
    str.replace(pos, ufffc.size(), printable_ufffc);
    pos += printable_ufffc.size();
  }

  return str;
}

std::string AtspiTextInterface::toString() const {
  if (isNull())
    return "Not implemented";

  std::string result;
  int length = getCharacterCount();
  std::string content;
  if (length < 50)
    content = getText(0, length);
  else
    content = getText(0, 20) + "[...]" + getText(length - 20, length);
  result += "'" + ToPrintableString(content) + "'";
  return result;
}

int AtspiTextInterface::getCaretOffset() const {
  if (isNull())
    return -1;

  GError* error = nullptr;
  int result = atspi_text_get_caret_offset(interface_, &error);
  if (error) {
    std::string err_msg = error->message;
    g_error_free(error);
    throw std::runtime_error(err_msg);
  }
  return result;
}

int AtspiTextInterface::getCharacterCount() const {
  if (isNull())
    return -1;

  GError* error = nullptr;
  int result = atspi_text_get_character_count(interface_, &error);
  if (error) {
    std::string err_msg = error->message;
    g_error_free(error);
    throw std::runtime_error(err_msg);
  }
  return result;
}

std::string AtspiTextInterface::getText(int start_offset,
                                        int end_offset) const {
  if (isNull())
    return std::string();

  GError* error = nullptr;
  char* text =
      atspi_text_get_text(interface_, start_offset, end_offset, &error);
  if (error) {
    std::string err_msg = error->message;
    g_error_free(error);
    throw std::runtime_error(err_msg);
  }
  std::string result(text);
  g_free(text);
  return result;
}
