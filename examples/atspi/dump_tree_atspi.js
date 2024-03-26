// NodeJS example that dumps the accessible tree of a running process using
// AXAccess AT-SPI API backend.

let name = '';
let pid = 0;

i = 2;
while (i < process.argv.length) {
  if (process.argv[i] == '--name') {
    name = process.argv[i + 1];
    i += 2;
  } else if (process.argv[i] == '--pid') {
    pid = parseInt(process.argv[i + 1], 10);
    i += 2;
  } else {
    i++
  }
}

if (!name.length && pid === 0) {
  console.log(
      'Usage: \n' +
      '  node dump_tree_atspi.js --name NAME\n' +
      '  node dump_tree_atspi.js --pid PID\n' +
      '  node dump_tree_atspi.js --name NAME --pid PID\n');
  process.exit();
}

const atspi = require('./atspi_inspect');
let root;
if (name.length) {
  msg = 'Searching for application with name \'' + name + '\'';
  if (pid !== 0) {
    msg += ' and pid ' + pid;
  }
  console.log(msg + '.');
  root = atspi.findRootAtspiNodeForName(name, pid);
} else {
  console.log('Searching for application with pid ' + pid + '.');
  root = atspi.findRootAtspiNodeForPID(pid);
}


if (root.isNull()) {
  console.log('Application not found.');
  process.exit();
}

// C++ vectors are not wrapped as JavaScript array primitives.
function VectorToString(vector) {
  let string = '(';
  for (let i = 0; i < vector.size(); i++) {
    string += vector.get(i) + ', ';
  }
  return string.slice(0, -2) + ')';
}

function PrintNode(node, level) {
  let sep = '';
  for (var i = 0; i < level; i++)
    sep += '--';
  console.log(
      sep + '> ' + node.getRoleName() + ' Name=\'' + node.getName() +
      '\' Description=\'' + node.getDescription() + '\'');

  console.log(
      '  '.repeat(level) + '* States=' + VectorToString(node.getStates()));
  console.log(
      '  '.repeat(level) +
      '* Interfaces=' + VectorToString(node.getInterfaces()));
  console.log(
      '  '.repeat(level) +
      '* Attributes=' + VectorToString(node.getAttributes()));

  relations = node.getRelations();
  // We dump this conditionally because most objects lack relations.
  if (relations.size() > 0) {
    console.log(
        '  '.repeat(level) +
        '* Relations=' + VectorToString(node.getRelations()));
  }

  // We don't check if this is null because pretty much everything implements
  // it.
  component = node.queryComponent();
  console.log('  '.repeat(level) + '* Component:' + component.toString());

  action = node.queryAction();
  if (!action.isNull()) {
    console.log('  '.repeat(level) + '* Action:' + action.toString());
  }

  document = node.queryDocument();
  if (!document.isNull()) {
    console.log('  '.repeat(level) + '* Document:' + document.toString());
  }

  table = node.queryTable();
  if (!table.isNull()) {
    console.log('  '.repeat(level) + '* Table:' + table.toString());
  }

  tableCell = node.queryTableCell();
  if (!tableCell.isNull()) {
    console.log('  '.repeat(level) + '* Table Cell:' + tableCell.toString());
  }

  text = node.queryText();
  if (!text.isNull()) {
    console.log('  '.repeat(level) + '* Text:' + text.toString());
  }

  value = node.queryValue();
  if (!value.isNull()) {
    console.log('  '.repeat(level) + '* Value:' + value.toString());
  }

  for (let i = 0; i < node.getChildCount(); i++) {
    PrintNode(node.getChildAtIndex(i), level + 1);
  }
}

try {
  PrintNode(root, 0);
} catch (e) {
  console.log(e);
}
