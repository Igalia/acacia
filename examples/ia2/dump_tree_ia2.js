const ia2_inspect = require('./ia2_inspect');

let name = '';
let pid = 0;

i = 2;
while (i < process.argv.length) {
  if (process.argv[i] == '--name') {
    name = process.argv[i + 1];
    i += 2;
  } else if (process.argv[i] == '--pid') {
    pid = process.argv[i + 1];
    i += 2;
  } else {
    i++
  }
}

if (!name.length) {
  console.log(
      'Usage: \n' +
      '  nodejs dump_tree_atspi.js' +
      ' --name <name-of-program>' +
      ' (--pid <pid>)\n');

  console.log('Error: name argument mandatory argument.');
  process.exit();
}

const root = ia2_inspect.IA2Node.CreateRootForName(name, pid);
if (root.IsNull()) {
  let errormsg = 'Error: no accessible application found for name: ' + name;
  if (pid)
    errormsg += ' and pid: ' + pid;
  console.log(errormsg);
  process.exit();
}

function printNode(node, level) {
  let sep = '';
  for (var i = 0; i < level; i++)
    sep += '--';
  console.log(
      sep + '> ' + node.get_accRole() + ' (' + node.get_accName() + ')');
  for (let i = 0; i < node.get_accChildCount(); i++) {
    printNode(node.AccessibleChildAt(i), level + 1);
  }
}

printNode(root, 0);
