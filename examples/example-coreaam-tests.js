/*
`cooltest` is a wrapper around ava.

In some other file, for this test suite, we would find the code that starts
the browser get the pid.

`cooltest` will load the file passed in before getting the root accessible
and passing it to the appropriate test (for example ATSPI, if running on linux).
The root accessible is provided to the test in `t.context.rootAccessibe`.

 */

// Test of role
// Spec: https://w3c.github.io/core-aam/#role-map-checkbox

/* tests/checkbox.html
 *
 * <!DOCTYPE html>
 * <html lang="en-US">
 *     <div role='checkbox' id='test'>content</div>
 * </html>
 */

cooltest({
  file: 'tests/checkbox-mixed.html',
  name: "role=checkbox",
  ATSPI: async (t) => {

    // *findAccessibleById* is from our library, it finds the node by DOM  ID
    let checkbox = t.context.rootAccessible().findAccessibleById('test');

    // Alternatively, we might end up doing:
    let checkboxByChild = t.context.rootAccessible().child().child()...;

    // Or by name (not gaurenteed to be unique, so maybe returns list)
    let checkboxByName = t.context.rootAccessible().findAccessibleByName('content')[0];

    // checkbox == checkboxByChild == checkboxByName, and
    // *findAccessibleById*, *child*, *findAccessibleByName* would be cross platform?

    t.is(checkbox.atspi_accessible_get_role(), 'ROLE_CHECK_BOX');

    // notes:
    // *atspi_accessible_get_role* is exposed by our library and
    // matches the ATSPI API.

  },
  AXAPI: async (t) => {

    let checkbox = t.context.rootAccessible().findAccessibleById('test');

    t.is(checkbox.AXRole, 'AXCheckBox');
    t.is(checkbox.AXSubrole, '<nil>');

    // notes:
    // I'm not sure how important the different between `nil` and the empty string is.

  },
  IA2: async (t) => {

    let checkbox = t.context.rootAccessible().findAccessibleById('test');

    t.is(checkbox.get_accRole, 'ROLE_SYSTEM_CHECKBUTTON');
    t.is(checkbox.queryInterfaceIA2.role, '');

    // notes:
    // IA2 has the concept of "interfaces" which have different information about the
    // object. *QueryInterfaceIA2* does not match the API, it looks more like:
    // https://learn.microsoft.com/en-us/windows/win32/api/unknwn/nf-unknwn-iunknown-queryinterface(refiid_void)
  },
  UIA: async (t) => {

    let checkbox = t.context.rootAccessible().findAccessibleById('test');

    t.is(checkbox.GetCachedPropertyValue('UIA_ControlTypePropertyId'), 'Checkbox')
    // notes:
    // I'm the least familiar with this API, I really don't know if this the part
    // of the API we want to expose.
  },
});

// Test of attribute aria-checked=true
// Spec: https://w3c.github.io/core-aam/#ariaCheckedTrue

/* tests/aria-checked-true.html
 *
 * <!DOCTYPE html>
 * <html lang="en-US">
 *     <div role='checkbox' id='test' aria-checked='true'>content</div>
 * </html>
 */

cooltest({
  file: 'tests/aria-checked-true.html',
  name: "aria-checked=true",
  ATSPI: async (t) => {

    let checkbox = t.context.rootAccessible().findAccessibleById('test');

    t.true(checkbox.atspi_state_set_get_states()['STATE_CHECKABLE'];
    t.true(checkbox.atspi_state_set_get_states()['STATE_CHECKED']);

    // notes:
    // *atspi_state_set_get_states* is exposed by our library and
    // matches the ATSPI API name. It returns an array of strings.

  },
  AXAPI: async (t) => {

    let checkbox = t.context.rootAccessible().findAccessibleById('test');

    t.is(checkbox.AXValue, 1);
  },
  IA2: async (t) => {

    let checkbox = t.context.rootAccessible().findAccessibleById('test');

    t.true(checkbox.get_accState()['STATE_SYSTEM_CHECKED']);
    t.is(checkbox.queryInterfaceIA2.get_attributes()['checkable'], 'true');
  },
  UIA: async (t) => {

    // TODO

  },
});


// Test of accessible events when the aria-checked attribute changes
// Spec: https://w3c.github.io/core-aam/#event-aria-checked

/* tests/checkbox.html
 *
 * <!DOCTYPE html>
 * <html lang="en-US">
 *     <div role='checkbox' id='test' aria-checked='false'>content</div>
 *     <button onclick="run_test">Run Test</button>
 *     <script>
 *          function run_test () {
 *              document.getElementById('test').setAttribute('aria-checked', 'true');
 *          }
 *     </script>
 * </html>
 */

// CAVEOT:
// I really don't know how to test events, I'm very unfamiliar with them.
// Here is an example of the chromium tests and their expectation files
// are right next to them:
// https://source.chromium.org/chromium/chromium/src/+/main:content/test/data/accessibility/event/checked-state-changed.html

cooltest({
  file: 'tests/aria-checked-true.html',
  name: "aria-checked=true",
  ATSPI: async (t) => {

    let checkbox = t.context.rootAccessible().findAccessibleById('test');
    // These are webdriver commands, where "session" is the webdriver
    // session.
    await t.context.session.findElement(By.id('run_test')).click();
    t.true(await checkbox.expectEvent('STATE-CHANGE:CHECKED:TRUE'));

  },
  AXAPI: async (t) => {

    let checkbox = t.context.rootAccessible().findAccessibleById('test');
    await t.context.session.findElement(By.id('run_test')).click();
    t.true(await checkbox.expectEventWithValue('AXValueChanged', 1));
  },
  IA2: async (t) => {

    let checkbox = t.context.rootAccessible().findAccessibleById('test');
    await t.context.session.findElement(By.id('run_test')).click();
    t.true(await checkbox.expectEventWithValues('EVENT_OBJECT_STATECHANGE'));
  },
  UIA: async (t) => {

    // TODO
  },
});
