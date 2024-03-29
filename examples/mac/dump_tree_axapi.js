#!/usr/bin/env node --preserve-symlinks

const kAttributes = [
  'AXRoleDescription',
  'AXTitle',
  'AXDescription',
  'AXFocused',
];


const {name, pid} = processArguments();

const axapi_inspect = require('./axapi_inspect');
const kSupportedListTypes = new Set([
  axapi_inspect.ValueType_NODE, axapi_inspect.ValueType_STRING,
  axapi_inspect.ValueType_RANGE, axapi_inspect.ValueType_DICTIONARY
]);

const root = getRootAXAPINode(name, pid);
printNodeAndSubtree(root, 0);

function printNodeAndSubtree(node, level) {
  if (!node.hasAttribute('AXRole'))
    return;
  if (node.getValueType('AXRole') == axapi_inspect.ValueType_UNKNOWN)
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
    let root = axapi_inspect.findRootAXAPINodeForName(name);
    if (root.isNull()) {
      console.error(`No running application found with name ${name}.`)
      process.exit();
    }
    return root;
  }

  if (pid !== undefined) {
    let root = axapi_inspect.findRootAXAPINodeForPID(pid);
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
      case axapi_inspect.ValueType_LIST:
        return getListAttributeValue(node, attribute);
      case axapi_inspect.ValueType_BOOLEAN:
        return node.getBooleanValue(attribute);
      case axapi_inspect.ValueType_INT:
        return node.getIntValue(attribute);
      case axapi_inspect.ValueType_FLOAT:
        return node.getFloatValue(attribute);
      case axapi_inspect.ValueType_STRING:
        return node.getStringValue(attribute);
      case axapi_inspect.ValueType_URL:
        return node.getURLValue(attribute);
      case axapi_inspect.ValueType_NODE:
        return node.getNodeValue(attribute);
      case axapi_inspect.ValueType_POINT:
        return node.getPointValue(attribute);
      case axapi_inspect.ValueType_SIZE:
        return node.getSizeValue(attribute);
      case axapi_inspect.ValueType_RECT:
        return node.getRectValue(attribute);
      case axapi_inspect.ValueType_RANGE:
        return node.getRangeValue(attribute);
      case axapi_inspect.ValueType_DICTIONARY:
        return node.getDictionaryValue(attribute);
      default:
        const typeString = axapi_inspect.ValueTypeToString(type);
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
    const typeString = axapi_inspect.ValueTypeToString(type);
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
    case axapi_inspect.ValueType_NODE:
      return node.getNodeListValueAtIndex(attribute, index);
    case axapi_inspect.ValueType_STRING:
      return node.getStringListValueAtIndex(attribute, index);
    case axapi_inspect.ValueType_RANGE:
      return node.getRangeListValueAtIndex(attribute, index);
    case axapi_inspect.ValueType_DICTIONARY:
      return node.getDictionaryListValueAtIndex(attribute, index);
    default:
      return undefined;
  }
}
