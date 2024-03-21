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
  root = atspi.find_root_accessible_from_name(name, pid);
} else {
  console.log('Searching for application with pid ' + pid + '.');
  root = atspi.find_root_accessible_from_pid(pid);
}


if (root.is_null()) {
  console.log('Application not found.');
  process.exit();
}

function printNode(node, level) {
  let sep = '';
  for (var i = 0; i < level; i++)
    sep += '--';
  console.log(sep + '> ' + node.get_role_name() + ' (' + node.get_name() + ')');
  for (let i = 0; i < node.get_child_count(); i++) {
    printNode(node.get_child_at_index(i), level + 1);
  }
}

try {
  printNode(root, 0);
} catch (e) {
  console.log(e);
}
