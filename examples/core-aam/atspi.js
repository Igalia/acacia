import AXAccess;

var PID = Number(process.argv[2]);
let application = AXAccess.findAtspiApplication(PID);
let atspiRootNode = application.getAtspiRootNode();

/********************* Checkbox *********************/

let checkboxNode = application.findAccessibleByDOMId('checkbox_test');

// Role
// https://docs.gtk.org/atspi2/method.Accessible.get_role_name.html
// https://docs.gtk.org/atspi2/enum.Role.html
checkboxNode.get_role_name();  // 'ATSPI_ROLE_CHECK_BOX'

// Name
// https://docs.gtk.org/atspi2/method.Accessible.get_name.html
checkboxNode.get_name();  // 'content'

// States
// https://docs.gtk.org/atspi2/method.Accessible.get_state_set.html
// https://docs.gtk.org/atspi2/enum.StateType.html
let stateSet = checkboxNode.get_state_set(); // Array or StateSet type?

// Do we want stateSet to be a custom object?
// https://docs.gtk.org/atspi2/method.StateSet.contains.html
stateSet.contains('ATSPI_STATE_CHECKED'); // true

// Or, do we want "stateSets" to simply be an array?
stateSet.includes('ATSPI_STATE_CHECKED'); // true

/********************* Navigation *********************/

let navigationNode = application.findAccessibleByDOMId('navigation_test');
navigationNode.get_role_name(); // 'ATSPI_ROLE_LANDMARK'

// https://docs.gtk.org/atspi2/method.Accessible.get_attributes.html
let attrs = navigationNode.get_attributes(); // dictionary
attrs['xml-roles']; // 'navigation'

/********************* Error Message *********************/

let withErrorNode = application.findAccessibleByDOMId('error_msg_test');

// https://docs.gtk.org/atspi2/method.Accessible.get_relation_set.html
// https://docs.gtk.org/atspi2/class.Relation.html
let relationObjs = withErrorNode.get_relation_set();

// https://docs.gtk.org/atspi2/enum.RelationType.html
relationObjs[0].get_relation_type();                    // 'ATSPI_RELATION_ERROR_MESSAGE'
relationObjs[0].get_n_relations();                      // 1
let errorNode = relationObjs[0].get_target(0);          // atspiNode
errorNode === application.findAccessibleByDomId('error'); // true

newRelationObjs = errorNode.get_relation_set();
newRelationObjs[0].get_relation_type();          // 'ATSPI_RELATION_ERROR_MESSAGE_FOR'
newRelationObjs[0].get_n_relations();            // 1
let node = relationObjs[0].get_target(0);        // atspiNode
node === withErrorNode;                          // true

/********************* Listbox *********************/

let listboxNode = application.findAccessibleByDOMId('listbox_test');
listboxNode.get_role_name(); // 'ATSPI_ROLE_LIST_BOX'

// https://docs.gtk.org/atspi2/method.Accessible.get_selection_iface.html
let selectionIface = listboxNode.get_selection_iface();
selectionIface.get_n_selected_children();                 // 1
let selectedChild = selectionIface.get_selected_child(0);
selectedChild.get_name();                                 // 'selected option'

// https://docs.gtk.org/atspi2/method.Selection.clear_selection.html
// These functions should not "work" in ARIA scenario, see:
// https://w3c.github.io/core-aam/#role-map-listbox
selectionIface.clear_selection();  // false, inaccessible per CORE-AAM.

/********************* Progressbar *********************/

let progressbarNode = application.findAccessibleByDOMId('progressbar_test');
progressbarNode.get_role_name(); // 'ATSPI_ROLE_PROGRESS_BAR'

// https://docs.gtk.org/atspi2/method.Accessible.get_value_iface.html
let valueIface = progressbarNode.get_value_iface();

// https://docs.gtk.org/atspi2/method.Value.get_current_value.html
valueIface.get_current_value(); // 20

// https://w3c.github.io/core-aam/#role-map-progressbar
valueIface.set_current_value(1); // false, not settable per CORE-AAM.

/********************* Readonly Textbox *********************/

let textboxNode = application.findAccessibleByDOMId('textbox_test');
textboxNode.get_role_name(); // 'ATSPI_ROLE_ENTRY'

// https://w3c.github.io/core-aam/#role-map-textbox
// when aria-readonly=true, do not have editableText iface
let editableTextIface = progressbarNode.get_editable_text_iface();
editableTextIface === null;  // true

/********************* Insetion *********************/

let insertionNode = application.findAccessibleByDOMId('insertion_test');
insertionNode.get_role_name(); // ATSPI_ROLE_INSERTION

let attrs = insertionNode.get_attributes();
attrs['xml-roles']; // 'insertion'
