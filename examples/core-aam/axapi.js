import AXAAxapi;

var PID = Number(process.argv[2]);
let application = AXAAxapi.findApplication(PID);

/********************* Checkbox *********************/

let checkboxNode = application.findAccessibleByDomId('checkbox_test');

// https://developer.apple.com/documentation/applicationservices/1459475-axuielementcopyattributenames
// Set of: https://developer.apple.com/documentation/applicationservices/axattributeconstants_h/miscellaneous_defines
// https://developer.apple.com/documentation/applicationservices/kaxroleattribute
let attributes = checkboxNode.AXUIElementCopyAttributeNames() // [kAXRoleAttribute, ...] -> ['AXRole', ...] ??

// Provide these constants?
checkboxNode.AXUIElementCopyAttributeValue(AXAAxapi.kAXRoleAttribute);    // 'AXCheckBox'
checkboxNode.AXUIElementCopyAttributeValue(AXAAxapi.kAXSubroleAttribute); // undefined
checkboxNode.AXUIElementCopyAttributeValue(AXAAxapi.kAXValueAttribute);   // 1

/********************* Navigation *********************/

let navigationNode = application.findAccessibleByDomId('navigation_test');

navigationNode.AXUIElementCopyAttributeValue(AXAAxapi.kAXRoleAttribute);    // 'AXGroup'
navigationNode.AXUIElementCopyAttributeValue(AXAAxapi.kAXSubroleAttribute); // 'AXLandmarkNavigation'

/********************* Error Message *********************/

let withErrorNode = application.findAccessibleByDomId('error_msg_test');

// There is no documentation in apple for this for this attribute
let axapisNodes = checkboxNode.AXUIElementCopyAttributeValue(
  AXAAxapi.NSAccessibilityErrorMessageElementsAttribute);

// https://developer.apple.com/documentation/appkit/nsaccessibilityprotocol/1526882-accessibilityvalue
axapisNodes[0].accessibilityValue() // 'hello world'

/********************* Listbox *********************/

let listboxNode = application.findAccessibleByDomId('listbox_test');
listboxNode.AXUIElementCopyAttributeValue(AXAAxapi.kAXRoleAttribute);    // 'AXList'
listboxNode.AXUIElementCopyAttributeValue(AXAAxapi.kAXSubroleAttribute); // undefined

// https://developer.apple.com/documentation/applicationservices/kaxselectedchildrenattribute
let selectedOptions = listboxNode.AXUIElementCopyAttributeValue(AXAAxapi.kAXSelectedChildrenAttribute);

// https://developer.apple.com/documentation/appkit/nsaccessibility/1534981-accessibilityselected
selectedOptions[0].accessibilitySelected(); // true

/********************* Progressbar *********************/

let progressbarNode = application.findAccessibleByDomId('progressbar_test');
progressbarNode.AXUIElementCopyAttributeValue(AXAAxapi.kAXRoleAttribute);    // 'AXList'
progressbarNode.AXUIElementCopyAttributeValue(AXAAxapi.kAXSubroleAttribute); // undefined
progressbarNode.AXUIElementCopyAttributeValue(AXAAxapi.kAXValueAttribute);   // 20


/********************* Readonly Textbox *********************/

let textboxNode = application.findAccessibleByDomId('textbox_test');
textboxNode.AXUIElementCopyAttributeValue(AXAAxapi.kAXRoleAttribute); // 'AXTextField'

/********************* Insetion *********************/

let insertionNode = application.findAccessibleByDomId('insetion_test');
insetionNode.AXUIElementCopyAttributeValue(AXAAxapi.kAXRoleAttribute);    // 'AXGroup'
insetionNode.AXUIElementCopyAttributeValue(AXAAxapi.kAXSubroleAttribute); // 'AXInsertStyleGroup'

// Concept in apple: https://developer.apple.com/documentation/foundation/attributedstring
let range = insertion.AXUIElementCopyParameterizedAttributeValue('AXTextMarkerRangeForUIElement', insertion);
let attributed = insertion.AXUIElementCopyParameterizedAttributeValue('AXAttributedStringForTextMarkerRange', range);

// To do: how to inspect this object? In chrome, the AttributeString is converted to an dictionary
// object here: https://source.chromium.org/chromium/chromium/src/+/main:ui/accessibility/platform/inspect/ax_transform_mac.mm;l=206?q=AXNSObjectToBaseValue&ss=chromium%2Fchromium%2Fsrc
