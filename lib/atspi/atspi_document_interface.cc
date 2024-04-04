#include <acacia/atspi/atspi_document_interface.h>

#include <assert.h>
#include <iostream>
#include <stdexcept>
#include <string>

#include "../utils.h"

std::string AtspiDocumentInterface::toString() const {
  if (isNull())
    return "Not implemented";

  return "Attributes=" + StringVectorToString(getDocumentAttributes()) +
         " Locale=" + getLocale();
}

std::vector<std::string> AtspiDocumentInterface::getDocumentAttributes() const {
  GError* error = nullptr;
  GHashTable* attributes_hash =
      atspi_document_get_document_attributes(interface_, &error);
  std::vector<std::string> attributes;
  if (error) {
    std::string err_msg = error->message;
    g_error_free(error);
    throw std::runtime_error(err_msg);
  }

  GHashTableIter iter;
  gpointer key, value;
  g_hash_table_iter_init(&iter, attributes_hash);
  while (g_hash_table_iter_next(&iter, &key, &value)) {
    std::string attr_entry =
        static_cast<char*>(key) + std::string(":") + static_cast<char*>(value);
    attributes.push_back(attr_entry);
  }

  g_hash_table_destroy(attributes_hash);
  return attributes;
}

std::string AtspiDocumentInterface::getLocale() const {
  if (isNull())
    std::string();

  GError* error = nullptr;
  char* locale = atspi_document_get_locale(interface_, &error);
  if (error) {
    std::string err_msg = error->message;
    g_error_free(error);
    throw std::runtime_error(err_msg);
  }
  std::string result(locale);
  g_free(locale);
  return result;
}
