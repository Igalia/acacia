import ApplicationServices

public func logInfoForPID(_ pid: pid_t) {
    let application: AXAPINode = createAXAPINodeForApplication(pid)
    let attributes: [String] = application.getAttributeNames()
    if (attributes.isEmpty) {
      print("No application with PID \(pid)")
      return
    }
    let title = application.title
    print("Title: \(String(describing:title))")
    let role = application.role
    print("Role: \(String(describing:role))")

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


