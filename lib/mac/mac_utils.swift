import ApplicationServices

public func logInfoForPID(_ pid: pid_t) {
    let application_ax_element = AXUIElementCreateApplication(pid)
    let application = AXAPINode(application_ax_element)
    let title = application.title
    print("Title: \(String(describing:title))")
    let role = application.role
    print("Role: \(String(describing:role))")

    let attributes: [String] = application.getAttributeNames()
    for attribute in attributes {
        switch attribute {
        case kAXTitleAttribute, kAXRoleAttribute:
            break
        default:
            let attribute_value = application.getStringAttribute(attribute)
            if let attribute_value {
              print("\(attribute) is \(attribute_value)")
            }
        }
    }
}


