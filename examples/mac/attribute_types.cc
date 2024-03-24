#include <cstdlib>
#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <string>

#include "include/axaccess/mac/axapi_node.h"
#include "include/axaccess/mac/mac_data_types.h"

using std::map;
using std::set;
using std::string;
using std::vector;

using mac_inspect::AXAPINode;
using mac_inspect::ValueType;
using mac_inspect::ValueTypeToString;

void print_usage(std::string& program_name) {
  std::cout << "Usage: " << program_name << " <pid>\n";
}

static std::set<ValueType> supported_types = {
    ValueType::LIST,   ValueType::BOOLEAN, ValueType::INT,  ValueType::FLOAT,
    ValueType::STRING, ValueType::URL,     ValueType::NODE, ValueType::POINT,
    ValueType::SIZE,   ValueType::RECT,    ValueType::RANGE};

static std::set<ValueType> supported_list_types = {
    ValueType::NODE,
    ValueType::STRING,
    ValueType::RANGE,
    ValueType::DICTIONARY,
};

void AddListValueExample(ValueType type,
                         ValueType list_type,
                         string type_string,
                         string attribute,
                         AXAPINode node,
                         map<string, map<string, string>>& examples) {
  if (supported_list_types.find(list_type) == supported_list_types.end())
    return;

  string value_string;
  switch (list_type) {
    case ValueType::NODE: {
      int num_elements = node.GetListAttributeValueCount(attribute);
      value_string = "[" + std::to_string(num_elements) + " node" +
                     (num_elements == 1 ? "" : "s") + "]";
      break;
    }
    case ValueType::STRING: {
      vector<string> values = node.CopyStringListAttributeValue(attribute);
      if (values.empty()) {
        value_string = "[]";
        break;
      }
      value_string = "[";
      for (int i = 0; i < values.size() - 1; i++) {
        value_string += values[i];
        value_string += ", ";
      }
      value_string += values.back();
      value_string += "]";
      break;
    }
    case ValueType::RANGE: {
      vector<mac_inspect::Range> values =
          node.CopyRangeListAttributeValue(attribute);
      if (values.empty()) {
        value_string = "[]";
        break;
      }
      value_string = "[";
      for (int i = 0; i < values.size() - 1; i++) {
        value_string += values[i].ToString();
        value_string += ", ";
      }
      value_string += values.back().ToString();
      value_string += "]";
      break;
    }
    case ValueType::DICTIONARY: {
      mac_inspect::Dictionary dict =
          node.CopyDictionaryListAttributeValueAtIndex(attribute, 0);
      vector<string> keys = dict.keys();
      value_string = "first value: {\n";
      for (string& key : keys) {
        ValueType type = dict.getValueType(key);
        switch (type) {
          case ValueType::STRING: {
            std::string value = dict.getStringValue(key);
            value_string += "  \"" + key + "\": \"" + value + "\"\n";
            break;
          }
          case ValueType::NODE: {
            AXAPINode value = dict.getNodeValue(key);
            value_string += "  \"" + key + "\": ";
            if (value.HasAttribute("AXTitle"))
              value_string +=
                  "(" + value.CopyStringAttributeValue("AXTitle") + ")";
            else
              value_string += "[unnamed node]";
            value_string += "\n";
            break;
          }
          default:
            break;
        }
      }
      value_string += "}";
      break;
    }
    default:
      break;
  }

  if (examples.find(type_string) == examples.end())
    examples[type_string] = map<string, string>();

  map<string, string>& type_examples = examples[type_string];
  type_examples[attribute] = value_string;
}

void AddValueExample(ValueType type,
                     string type_string,
                     string attribute,
                     AXAPINode node,
                     map<string, map<string, string>>& examples,
                     ValueType list_type = ValueType::NOT_PRESENT) {
  if (supported_types.find(type) == supported_types.end())
    return;

  if (examples.find(type_string) != examples.end()) {
    map<string, string>& type_examples = examples[type_string];
    if (type_examples.find(attribute) != type_examples.end())
      return;
  }

  if (type == ValueType::LIST && list_type != ValueType::NOT_PRESENT) {
    AddListValueExample(type, list_type, type_string, attribute, node,
                        examples);
    return;
  }

  string value_string;
  switch (type) {
    case ValueType::BOOLEAN: {
      bool value = node.CopyBooleanAttributeValue(attribute);
      value_string = value ? "true" : "false";
      break;
    }
    case ValueType::INT: {
      int value = node.CopyIntAttributeValue(attribute);
      value_string = std::to_string(value);
      break;
    }
    case ValueType::FLOAT: {
      float value = node.CopyFloatAttributeValue(attribute);
      value_string = std::to_string(value);
      break;
    }
    case ValueType::STRING: {
      value_string = "\"" + node.CopyStringAttributeValue(attribute) + "\"";
      break;
    }
    case ValueType::URL: {
      value_string = "\"" + node.CopyURLAttributeValue(attribute) + "\"";
      break;
    }
    case ValueType::NODE: {
      AXAPINode value = node.CopyNodeAttributeValue(attribute);
      if (value.HasAttribute("AXTitle"))
        value_string = "(" + value.CopyStringAttributeValue("AXTitle") + ")";
      break;
    }
    case ValueType::POINT: {
      mac_inspect::Point value = node.CopyPointAttributeValue(attribute);
      value_string = value.ToString();
      break;
    }
    case ValueType::SIZE: {
      mac_inspect::Size value = node.CopySizeAttributeValue(attribute);
      value_string = value.ToString();
      break;
    }
    case ValueType::RECT: {
      mac_inspect::Rect value = node.CopyRectAttributeValue(attribute);
      value_string = value.ToString();
      break;
    }
    case ValueType::RANGE: {
      mac_inspect::Range value = node.CopyRangeAttributeValue(attribute);
      value_string = value.ToString();
      break;
    }
    default:
      break;
  }
  if (value_string.empty())
    return;

  if (examples.find(type_string) == examples.end())
    examples[type_string] = map<string, string>();

  map<string, string>& type_examples = examples[type_string];
  type_examples[attribute] = value_string;
}

void CollectAttributeTypes(AXAPINode node,
                           map<string, string>& attribute_types,
                           map<string, map<string, string>>& examples) {
  vector<string> attributes = node.CopyAttributeNames();
  for (const string& attribute : attributes) {
    try {
      // TODO: Some attributes map to *multiple* types. This should map to a
      // vector of string, and only skip if we've already logged the type.
      if (attribute_types.count(attribute) > 0)
        continue;

      ValueType type = node.GetAttributeValueType(attribute);

      std::string type_string;
      if (type != ValueType::NOT_PRESENT) {
        if (type == ValueType::LIST) {
          ValueType list_type = node.GetListAttributeElementType(attribute);
          if (list_type != ValueType::UNKNOWN) {
            type_string = ValueTypeToString(type) + "<" +
                          ValueTypeToString(list_type) + ">";
            AddValueExample(type, type_string, attribute, node, examples,
                            list_type);
          }
        } else {
          type_string = ValueTypeToString(type);
          AddValueExample(type, type_string, attribute, node, examples);
        }
        if (!type_string.empty())
          attribute_types[attribute] = type_string;
      }
    } catch (std::runtime_error e) {
      std::cerr << "caught: " << e.what() << "\n";
    } catch (std::invalid_argument e) {
      std::cerr << "caught: " << e.what() << "\n";
    } catch (...) {
      std::cerr << "caught something else??\n";
    }
  }

  if (!node.HasAttribute("AXChildren"))
    return;

  try {
    vector<AXAPINode> children = node.CopyNodeListAttributeValue("AXChildren");
    for (AXAPINode& child : children)
      CollectAttributeTypes(child, attribute_types, examples);
  } catch (...) {
  }
}

void LogAllAttributeValueTypesAndExamples(pid_t pid) {
  AXAPINode application = AXAPINode::CreateForPID(pid);
  map<string, string> attribute_types;
  map<string, map<string, string>> examples;

  CollectAttributeTypes(application, attribute_types, examples);

  std::cout << "\n\n"
            << "Attributes in name order:\n"
            << "------------------------\n";
  for (const auto& [attribute, type] : attribute_types)
    std::cout << attribute << ": " << type << "\n";

  std::cout << "\n\n"
            << "Attributes sorted by type:\n"
            << "-------------------------\n";
  std::vector<std::pair<string, string>> attribute_types_vector(
      attribute_types.begin(), attribute_types.end());
  std::sort(attribute_types_vector.begin(), attribute_types_vector.end(),
            [](auto& left, auto& right) { return left.second < right.second; });
  for (const auto& [attribute, type] : attribute_types_vector)
    std::cout << attribute << ": " << type << "\n";

  std::cout << "\n\n"
            << "Examples of each supported attribute by type:\n"
            << "--------------------------------------------";
  for (const auto& [type, attributes] : examples) {
    std::cout << "\n" << type << ":\n";
    for (const auto& [attribute, example] : attributes) {
      std::cout << attribute << ": " << example << "\n";
    }
  }
  std::cout << "\n";
}

int main(int argc, char** argv) {
  std::string program_name(argv[0]);

  if (argc != 2) {
    print_usage(program_name);
    return 1;
  }

  std::string pid_string(argv[1]);
  std::regex number_regex("\\d+");
  if (!std::regex_match(pid_string, number_regex)) {
    print_usage(program_name);
    return 1;
  }

  const int pid = std::stoi(pid_string);
  std::cerr << "Got PID: " << pid << "\n";

  LogAllAttributeValueTypesAndExamples((pid_t)pid);

  return 0;
}
