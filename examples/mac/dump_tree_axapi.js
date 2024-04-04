#!/usr/bin/env node --preserve-symlinks

const kAttributes = [
  'AXRoleDescription',
  'AXTitle',
  'AXDescription',
  'AXFocused',
];


const {name, pid} = processArguments();

const acacia_axapi = require('./acacia_axapi');
const kSupportedListTypes = new Set([
  acacia_axapi.ValueType_NODE, acacia_axapi.ValueType_STRING,
  acacia_axapi.ValueType_RANGE, acacia_axapi.ValueType_DICTIONARY
]);

const root = getRootAXAPINode(name, pid);
printNodeAndSubtree(root, 0);

function printNodeAndSubtree(node, level) {
  if (!node.hasAttribute('AXRole'))
    return;
  if (node.getValueType('AXRole') == acacia_axapi.ValueType_UNKNOWN)
    return;

  const prefix = '--'.repeat(level) + '>';
  const roleAndAttributes = serializeRoleAndAttributes(node, kAttributes);
  console.log(`${prefix} ${roleAndAttributes}`);

  if (!node.hasAttribute('AXChildren'))
    return;

  let children = getListAttributeValue(node, 'AXChildren');
  for (let child of children)
    printNodeAndSubtree(child, level + 1);
}

function serializeRoleAndAttributes(node, attributes) {
  let output = getAttributeValue(node, 'AXRole');

  for (let attribute of attributes) {
    if (!node.hasAttribute(attribute))
      continue;

    let value = getAttributeValue(node, attribute);
    switch (typeof value) {
      case 'undefined':
        continue;
      case 'boolean':
        if (value)
          output += ` ${attribute}`;
        break;
      case 'string':
        output += ` ${attribute}='${value}'`;
        break;
      default:
        output += ` ${attribute}=${value}`;
        break;
    }
  }

  return output;
}

function getRootAXAPINode(name, pid) {
  if (name !== undefined) {
    let root = acacia_axapi.findRootAXAPINodeForName(name);
    if (root.isNull()) {
      console.error(`No running application found with name ${name}.`)
      process.exit();
    }
    return root;
  }

  if (pid !== undefined) {
    let root = acacia_axapi.findRootAXAPINodeForPID(pid);
    if (!root.isNull()) {
      console.error(`No running application found with PID ${pid}.`)
      process.exit();
    }
    return root;
  }

  printUsageAndExit();
}

function processArguments() {
  let args = process.argv.slice(2);

  if (args.length === 1)
    return {name: args[0]};

  if (args.length === 2) {
    if (args[0] !== '-p')
      printUsageAndExit();
    if (!args[1].match(/\d+/))
      printUsageAndExit();
    return {pid: Number(args[1])};
  }

  printUsageAndExit();
}

function printUsageAndExit() {
  const script_name = process.argv[1];
  console.error(`Usage: ${script_name} [-p <pid> | <name>]`);
  process.exit();
}

function getAttributeValue(node, attribute) {
  try {
    const type = node.getValueType(attribute);
    switch (type) {
      case acacia_axapi.ValueType_LIST:
        return getListAttributeValue(node, attribute);
      case acacia_axapi.ValueType_BOOLEAN:
        return node.getBooleanValue(attribute);
      case acacia_axapi.ValueType_INT:
        return node.getIntValue(attribute);
      case acacia_axapi.ValueType_FLOAT:
        return node.getFloatValue(attribute);
      case acacia_axapi.ValueType_STRING:
        return node.getStringValue(attribute);
      case acacia_axapi.ValueType_URL:
        return node.getURLValue(attribute);
      case acacia_axapi.ValueType_NODE:
        return node.getNodeValue(attribute);
      case acacia_axapi.ValueType_POINT:
        return node.getPointValue(attribute);
      case acacia_axapi.ValueType_SIZE:
        return node.getSizeValue(attribute);
      case acacia_axapi.ValueType_RECT:
        return node.getRectValue(attribute);
      case acacia_axapi.ValueType_RANGE:
        return node.getRangeValue(attribute);
      case acacia_axapi.ValueType_DICTIONARY:
        return node.getDictionaryValue(attribute);
      default:
        const typeString = acacia_axapi.ValueTypeToString(type);
        console.error(`Unsupported type: ${typeString} for ${attribute}`);
        return undefined;
    }
  } catch (e) {
    return `(error: ${e})`;
  }
}

function getListAttributeValue(node, attribute) {
  let count = node.getListElementCount(attribute);
  if (count === 0)
    return [];

  const type = node.getListElementType(attribute);
  if (!kSupportedListTypes.has(type)) {
    const typeString = acacia_axapi.ValueTypeToString(type);
    console.error(`Unsupported list type: ${typeString} for ${attribute}`);
    return undefined;
  }

  let array = [];
  for (let i = 0; i < count; i++)
    array.push(getListAttributeValueAtIndex(node, type, attribute, i));

  return array;
}

function getListAttributeValueAtIndex(node, type, attribute, index) {
  switch (type) {
    case acacia_axapi.ValueType_NODE:
      return node.getNodeListValueAtIndex(attribute, index);
    case acacia_axapi.ValueType_STRING:
      return node.getStringListValueAtIndex(attribute, index);
    case acacia_axapi.ValueType_RANGE:
      return node.getRangeListValueAtIndex(attribute, index);
    case acacia_axapi.ValueType_DICTIONARY:
      return node.getDictionaryListValueAtIndex(attribute, index);
    default:
      return undefined;
  }
}
