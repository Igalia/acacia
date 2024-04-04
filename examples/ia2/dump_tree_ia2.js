const acacia_ia2 = require('./acacia_ia2');

let name = '';
let pid = 0;

i = 2;
while (i < process.argv.length) {
  if (process.argv[i] == '--name') {
    name = process.argv[i + 1];
    i += 2;
  } else if (process.argv[i] == '--pid') {
    pid = Number(process.argv[i + 1]);
    i += 2;
  } else {
    i++
  }
}

if (!name.length && pid === 0) {
  console.log(
      'Usage: \n' +
      '  node dump_tree_ia2.js' +
      ' --name <name-of-program>' +
      ' --pid <pid>\n');

  console.log('Error: name or pid argument mandatory argument.');
  process.exit();
}

let root;
if (name) {
  root = acacia_ia2.findRootIANodeForName(name, pid);
} else {
  root = acacia_ia2.findRootIANodeForPID(pid);
}
if (root.isNull()) {
  let errormsg = 'Error: no accessible application found for name: ' + name;
  if (pid)
    errormsg += ' and pid: ' + pid;
  console.log(errormsg);
  process.exit();
}

function printNode(node, level) {
  let output = '--'.repeat(level) + '>';

  let msaa_role = node.getAccRole();
  let ia2 = node.QueryIA2();
  let ia2_role = ia2.role();

  if (!ia2_role.length || msaa_role === ia2_role) {
    output += msaa_role;
  } else {
    output += ia2_role + ' ' + msaa_role;
  }

  output += ` Name='${node.getAccName()}',`;
  output += ` Description='${node.getAccDescription()}',`;

  // Note: C++ vectors are not wrapped as javascript array primatives.
  // See README for more information.
  let states = '';
  let ia_states = node.getStateStrings();
  for (let i = 0; i < ia_states.size(); i++) {
    states += ia_states.get(i) + ', ';
  }
  let ia2_states = ia2.getStateStrings();
  for (let i = 0; i < ia2_states.size(); i++) {
    states += ia2_states.get(i) + ', ';
  }

  output += ` States=[${states.slice(0, -2)}],`;

  let pos = ia2.getGroupPosition();

  if (!pos.IsEmpty()) {
    output += '\n' +
        '  '.repeat(level + 1) + 'Group position: ' +
        `{level: ${pos.level}, setsize: ${pos.setsize}, position: ${
                  pos.position}}`;
  }

  console.log(output);

  for (let i = 0; i < node.getAccChildCount(); i++) {
    printNode(node.AccessibleChildAt(i), level + 1);
  }
}

printNode(root, 0);
