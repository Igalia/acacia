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

const root = ia2_inspect.IANode.CreateRootForName(name, pid);
if (root.IsNull()) {
  let errormsg = 'Error: no accessible application found for name: ' + name;
  if (pid)
    errormsg += ' and pid: ' + pid;
  console.log(errormsg);
  process.exit();
}

function printNode(node, level) {
  let output = '--'.repeat(level) + '>';

  let msaa_role = node.get_accRole();
  let ia2 = node.QueryIA2();
  let ia2_role = ia2.role();

  if (!ia2_role.length || msaa_role === ia2_role) {
    output += msaa_role;
  } else {
    output += ia2_role + ' ' + msaa_role;
  }

  output += ` Name='${node.get_accName()}',`;
  output += ` Description='${node.get_accDescription()}',`;

  // TODO: doesn't work, investigate
  // let states = node.GetStates().join(", ") + ", " + ia2.GetStates().join(",
  // "); output += ` States=[${states}],`;

  for (let i = 0; i < node.get_accChildCount(); i++) {
    printNode(node.AccessibleChildAt(i), level + 1);
  }
}

printNode(root, 0);
