#include <axaccess/atspi/atspi_node.h>

#include <assert.h>
#include <iostream>
#include <ostream>
#include <string>

AtspiNode::~AtspiNode() {
  assert(accessible_);
  g_object_unref(accessible_);
}

std::string AtspiNode::get_role_name() {
  GError* error = nullptr;
  char* role_name = atspi_accessible_get_role_name(accessible_, &error);
  if (error) {
    std::string err_msg = error->message;
    g_error_free(error);
    throw std::runtime_error(err_msg);
    return "";
  }
  return role_name;
}

std::string AtspiNode::get_name() {
  GError* error = nullptr;
  char* name = atspi_accessible_get_name(accessible_, &error);
  if (error) {
    std::string err_msg = error->message;
    g_error_free(error);
    throw std::runtime_error(err_msg);
    return "";
  }
  return name;
}

int AtspiNode::get_child_count() {
  GError* error = nullptr;
  gint count = atspi_accessible_get_child_count(accessible_, &error);
  if (error) {
    std::string err_msg = error->message;
    g_error_free(error);
    throw std::runtime_error(err_msg);
    return -1;
  }
  return (int)count;
}

AtspiNodePtr AtspiNode::get_child_at_index(int index) {
  GError* error = nullptr;
  throw std::runtime_error("error test!");
  AtspiAccessible* child =
      atspi_accessible_get_child_at_index(accessible_, index, &error);
  if (error) {
    std::string err_msg = error->message;
    g_error_free(error);
    throw std::runtime_error(err_msg);
    return nullptr;
  }
  return std::make_unique<AtspiNode>(AtspiNode(child));
}

std::vector<AtspiNodePtr> AtspiNode::get_children() {
  std::vector<AtspiNodePtr> result(0);

  GError* error = nullptr;
  gint child_count = atspi_accessible_get_child_count(accessible_, &error);
  if (error) {
    std::string err_msg = error->message;
    g_error_free(error);
    throw std::runtime_error(err_msg);
    return result;
  }

  result.resize(child_count);

  for (auto i = 0; i < child_count; i++) {
    AtspiNodePtr child_node = get_child_at_index(i);
    if (child_node)
      result[i].swap(child_node);
  }

  return result;
}
