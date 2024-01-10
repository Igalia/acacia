import AXAccess;

var PID = Number(process.argv[2]);

/* The following code will work on all platforms */

let application = AXAccess.findApplication(PID);

let checkboxNode = application.findAccessibleByDOMId('checkbox_test');
let role = checkboxNode.role;
let name = checkboxNode.name;

let navigation = application.findFirstAccessibleWithName('cool nav');

// Contains role and name information only
checkboxNode.toString()

let listboxNode = application.findAccessibleByDOMId('listbox_test');
let child = listboxNode.child();
child.parent() === listboxNode;

/* However, the API for the platform is still available based on platform */
// For example, if on linux:
let stateSet = checkboxNode.get_state_set();
stateSet.contains('ATSPI_STATE_CHECKED');
