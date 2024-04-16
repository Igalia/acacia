#!/usr/bin/env python3

import argparse
import sys
import acacia_axapi

ATTRIBUTES = [
  'AXRoleDescription',
  'AXTitle',
  'AXDescription',
  'AXFocused',
]


def print_node_and_subtree(node, level):
  prefix = "--" * level
  role_and_attributes = serialize_role_and_attributes(node, ATTRIBUTES)
  print(f'{prefix} {role_and_attributes}')

  if not node.hasAttribute('AXChildren'):
    return

  children = get_list_attribute_value(node, 'AXChildren')
  for child in children:
    print_node_and_subtree(child, level + 1)


def serialize_role_and_attributes(node, attributes):
  output = get_attribute_value(node, 'AXRole')

  for attribute in attributes:
    if not node.hasAttribute(attribute):
      continue

    value = get_attribute_value(node, attribute)
    match type(value).__name__:
      case 'NoneType':
        continue
      case 'bool':
        if value:
          output += f' {attribute}'
      case 'str':
        value_utf16 = value.encode('utf-16', 'surrogatepass').decode('utf-16', 'replace')
        output += f' {attribute}="{value_utf16}"'
      case _:
        output += f' {attribute}={value}'

  return output


def get_attribute_value(node, attribute):
  try:
    type = node.getValueType(attribute)
    match type:
      case acacia_axapi.ValueType_LIST:
        return get_list_attribute_value(node, attribute)
      case acacia_axapi.ValueType_BOOLEAN:
        return node.getBooleanValue(attribute)
      case acacia_axapi.ValueType_INT:
        return node.getIntValue(attribute)
      case acacia_axapi.ValueType_FLOAT:
        return node.getFloatValue(attribute)
      case acacia_axapi.ValueType_STRING:
        return node.getStringValue(attribute)
      case acacia_axapi.ValueType_URL:
        return node.getURLValue(attribute)
      case acacia_axapi.ValueType_NODE:
        return node.getNodeValue(attribute)
      case acacia_axapi.ValueType_POINT:
        return node.getPointValue(attribute)
      case acacia_axapi.ValueType_SIZE:
        return node.getSizeValue(attribute)
      case acacia_axapi.ValueType_RECT:
        return node.getRectValue(attribute)
      case acacia_axapi.ValueType_RANGE:
        return node.getRangeValue(attribute)
      case acacia_axapi.ValueType_DICTIONARY:
        return node.getDictionaryValue(attribute)
      case _:
        type_string = acacia_axapi.ValueTypeToString(type)
        print(f'Unsupported type: {type_string} for {attribute}')
        return None
  except Exception as error:
    return f'(error: {error})'


def get_list_attribute_value(node, attribute):
  count = node.getListElementCount(attribute)
  if count == 0:
    return []

  type = node.getListElementType(attribute)
  list = None
  match type:
    case acacia_axapi.ValueType_NODE:
      list = node.getNodeListValue(attribute)
    case acacia_axapi.ValueType_STRING:
      list = node.getStringListValue(attribute)
    case acacia_axapi.ValueType_RANGE:
      list = node.getRangeListValue(attribute)
    case acacia_axapi.ValueType_DICTIONARY:
      list = node.getDictionaryListValue(attribute)
    case _:
      type_string = acacia_axapi.ValueTypeToString(type)
      sys.stderr.write(f'Unsupported list type: {type_string} for {attribute}.')
      return None

  result = []
  for i in range(count):
    result.append(list[i])
  return result


def process_arguments():
  parser = argparse.ArgumentParser(
      description=
      "Dumps the Mac accessibility tree for the specified application.")
  parser.add_argument("--pid", type=int)
  parser.add_argument("--name", type=str)
  args = parser.parse_args()
  if not (args.pid or args.name):
    parser.print_help()
    sys.exit()
  return args


def main():
  args = process_arguments()
  if args.name:
    print(f'Searching for application with name "{args.name}".')
    root = acacia_axapi.findRootAXAPINodeForName(args.name)
  else:
    print(f'Searching for application with pid {args.pid}.')
    root = acacia_axapi.findRootAXAPINodeForPID(args.pid)

  if root.isNull():
    sys.stderr.write("Error: Application not found.")
    sys.exit()

  try:
    print_node_and_subtree(root, 0)
  except Exception as error:
    sys.stderr.write(f"Error encountered printing node: {error}")


if __name__ == "__main__":
    main()
