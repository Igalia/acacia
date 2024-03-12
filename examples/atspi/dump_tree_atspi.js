// NodeJS example that dumps the accessible tree of a running process using
// AXAccess AT-SPI API backend.

let pid = process.argv[2];
pid = parseInt(pid);

if (!pid || typeof(pid) != "number") {
    console.log("Usage: \n" + "  nodejs dump_tree_atspi.js" + " <pid>\n");

    console.log ("Error: missing <pid> argument.");
    process.exit();
}

const atspi = require("../../lib/atspi/atspi_inspect");

const root = atspi.find_root_accessible_from_pid(pid);
if (!root) {
    console.log("Error: no accessible application found for pid '" + pid + "'.");
    process.exit();
}

function printNode(node, level) {
    let sep = "";
    for (var i = 0; i < level; i++)
        sep += "--";
    console.log (sep + "> " + node.get_role_name() + " (" +
                 node.get_name() + ")");
    for (let i = 0; i < node.get_child_count(); i++) {
        printNode(node.get_child_at_index(i), level + 1);
    }
}

try {
    printNode(root, 0);
} catch(e) {
    console.log(e);
}

// TODO: delete this line, for testing errors
console.log("Executing the rest of the program.");
