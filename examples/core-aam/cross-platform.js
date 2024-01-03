import AXAccess;

var PID = Number(process.argv[2]);

// Application is a wrapper node with some cross platform functionality.
let application = AXAccess.findApplication(PID);

let checkboxNode = application.findAccessibleByDomId('checkbox_test');
let role = checkboxNode.getRole();
let name = checkboxNode.getName();

let navigation = application.findFirstAccessibleWithName('cool nav');

// For a tree?
let accessibilityData = checkboxNode.dataDump();

let listboxNode = application.findAccessibleByDomId('listbox_test');
let child = listboxNode.child();
child.parent() === listboxNode;

// Then, if you are on a linux:
import AXAAtspi;

let atspiNode = AXAAtspi.getAtspiNodeFor(checkboxNode);
let stateSet = checkboxNode.get_state_set();
stateSet.contains('ATSPI_STATE_CHECKED');
