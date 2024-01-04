import AXAccess;
import AXAAxapi;

var PID = Number(process.argv[2]);
let application = AXAccess.findApplication(PID);
let axapiRoot = AXAxapi.getAxapiNodeFor(application);

/********************* Checkbox *********************/

let checkboxNode = axapiRoot.findAccessibleByDOMId('checkbox_test');

// https://developer.apple.com/documentation/axapiRootservices/1459475-axuielementcopyattributenames
// Set of: https://developer.apple.com/documentation/axapiRootservices/axattributeconstants_h/miscellaneous_defines
// https://developer.apple.com/documentation/axapiRootservices/kaxroleattribute
let attributes = checkboxNode.AXUIElementCopyAttributeNames() // [kAXRoleAttribute, ...] -> ['AXRole', ...] ??

// Provide these constants?
checkboxNode.AXUIElementCopyAttributeValue(AXAAxapi.kAXRoleAttribute);    // 'AXCheckBox'
checkboxNode.AXUIElementCopyAttributeValue(AXAAxapi.kAXSubroleAttribute); // undefined
checkboxNode.AXUIElementCopyAttributeValue(AXAAxapi.kAXValueAttribute);   // 1

/********************* Navigation *********************/

let navigationNode = axapiRoot.findAccessibleByDOMId('navigation_test');

navigationNode.AXUIElementCopyAttributeValue(AXAAxapi.kAXRoleAttribute);    // 'AXGroup'
navigationNode.AXUIElementCopyAttributeValue(AXAAxapi.kAXSubroleAttribute); // 'AXLandmarkNavigation'

/********************* Error Message *********************/

let withErrorNode = axapiRoot.findAccessibleByDOMId('error_msg_test');

// There is no documentation in apple for this for this attribute
let axapisNodes = checkboxNode.AXUIElementCopyAttributeValue(
  AXAAxapi.NSAccessibilityErrorMessageElementsAttribute);

// https://developer.apple.com/documentation/appkit/nsaccessibilityprotocol/1526882-accessibilityvalue
axapisNodes[0].accessibilityValue() // 'hello world'

/********************* Listbox *********************/

let listboxNode = axapiRoot.findAccessibleByDOMId('listbox_test');
listboxNode.AXUIElementCopyAttributeValue(AXAAxapi.kAXRoleAttribute);    // 'AXList'
listboxNode.AXUIElementCopyAttributeValue(AXAAxapi.kAXSubroleAttribute); // undefined

// https://developer.apple.com/documentation/axapiRootservices/kaxselectedchildrenattribute
let selectedOptions = listboxNode.AXUIElementCopyAttributeValue(AXAAxapi.kAXSelectedChildrenAttribute);

// https://developer.apple.com/documentation/appkit/nsaccessibility/1534981-accessibilityselected
selectedOptions[0].accessibilitySelected(); // true

/********************* Progressbar *********************/

let progressbarNode = axapiRoot.findAccessibleByDOMId('progressbar_test');
progressbarNode.AXUIElementCopyAttributeValue(AXAAxapi.kAXRoleAttribute);    // 'AXList'
progressbarNode.AXUIElementCopyAttributeValue(AXAAxapi.kAXSubroleAttribute); // undefined
progressbarNode.AXUIElementCopyAttributeValue(AXAAxapi.kAXValueAttribute);   // 20


/********************* Readonly Textbox *********************/

let textboxNode = axapiRoot.findAccessibleByDOMId('textbox_test');
textboxNode.AXUIElementCopyAttributeValue(AXAAxapi.kAXRoleAttribute); // 'AXTextField'

/********************* Insetion *********************/

let insertionNode = axapiRoot.findAccessibleByDOMId('insertion_test');
insetionNode.AXUIElementCopyAttributeValue(AXAAxapi.kAXRoleAttribute);    // 'AXGroup'
insetionNode.AXUIElementCopyAttributeValue(AXAAxapi.kAXSubroleAttribute); // 'AXInsertStyleGroup'

// Concept in apple: https://developer.apple.com/documentation/foundation/attributedstring
let range = insertion.AXUIElementCopyParameterizedAttributeValue('AXTextMarkerRangeForUIElement', insertion);
let attributed = insertion.AXUIElementCopyParameterizedAttributeValue('AXAttributedStringForTextMarkerRange', range);

// To do: how to inspect this object? In chrome, the AttributeString is converted to an dictionary
// object here: https://source.chromium.org/chromium/chromium/src/+/main:ui/accessibility/platform/inspect/ax_transform_mac.mm;l=206?q=AXNSObjectToBaseValue&ss=chromium%2Fchromium%2Fsrc
