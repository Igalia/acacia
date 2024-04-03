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

  let children = getListAttribute(node, 'AXChildren');
  for (let child of children)
    printNodeAndSubtree(child, level + 1);
}

function serializeRoleAndAttributes(node, attributes) {
  let output = getAttribute(node, 'AXRole');

  for (let attribute of attributes) {
    if (!node.hasAttribute(attribute))
      continue;

    let value = getAttribute(node, attribute);
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

function getAttribute(node, attribute) {
  try {
    const type = node.getValueType(attribute);
    switch (type) {
      case axapi_inspect.ValueType_LIST:
        return getListAttribute(node, attribute);
      case axapi_inspect.ValueType_BOOLEAN:
        return node.getBooleanAttribute(attribute);
      case axapi_inspect.ValueType_INT:
        return node.getIntAttribute(attribute);
      case axapi_inspect.ValueType_FLOAT:
        return node.getFloatAttribute(attribute);
      case axapi_inspect.ValueType_STRING:
        return node.getStringAttribute(attribute);
      case axapi_inspect.ValueType_URL:
        return node.getURLAttribute(attribute);
      case axapi_inspect.ValueType_NODE:
        return node.getNodeAttribute(attribute);
      case axapi_inspect.ValueType_POINT:
        return node.getPointAttribute(attribute);
      case axapi_inspect.ValueType_SIZE:
        return node.getSizeAttribute(attribute);
      case axapi_inspect.ValueType_RECT:
        return node.getRectAttribute(attribute);
      case axapi_inspect.ValueType_RANGE:
        return node.getRangeAttribute(attribute);
      case axapi_inspect.ValueType_DICTIONARY:
        return node.getDictionaryAttribute(attribute);
      default:
        const typeString = axapi_inspect.ValueTypeToString(type);
        console.error(`Unsupported type: ${typeString} for ${attribute}`);
        return undefined;
    }
  } catch (e) {
    return `(error: ${e})`;
  }
}

function getListAttribute(node, attribute) {
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
    array.push(getListAttributeAtIndex(node, type, attribute, i));

  return array;
}

function getListAttributeAtIndex(node, type, attribute, index) {
  switch (type) {
    case axapi_inspect.ValueType_NODE:
      return node.getNodeListAttribute(attribute, index);
    case axapi_inspect.ValueType_STRING:
      return node.getStringListAttribute(attribute, index);
    case axapi_inspect.ValueType_RANGE:
      return node.getRangeListAttribute(attribute, index);
    case axapi_inspect.ValueType_DICTIONARY:
      return node.getDictionaryListAttribute(attribute, index);
    default:
      return undefined;
  }
}
