import ApplicationServices

public func logInfoForPID(_ pid: pid_t) {
    let application = AXUIElementCreateApplication(pid)

    let attributes: [String] = getAttributeNames(application)
    for attribute in attributes {
        switch attribute {
        case kAXTitleAttribute:
            let title = getStringAttribute(application, kAXTitleAttribute)
            if let title {
                print("title is: \(title)")
            }
        case kAXRoleAttribute:
            let role = getStringAttribute(application, kAXRoleAttribute)
            if let role {
                print("role is: \(role)")
            }
        default:
            break
        }
    }
}

func getAttributeNames(_ element: AXUIElement) -> [String] {
    var attributes: CFArray?
    let result = AXUIElementCopyAttributeNames(element, &attributes)
    guard result == .success else {
        print("Couldn't get attributes")
        return []
    }

    return attributes! as! [String]
}

func getStringAttribute(_ element: AXUIElement, _ attribute: String) -> String? {
    var value: CFTypeRef?
    let result = AXUIElementCopyAttributeValue(element, attribute as CFString, &value)
    guard result == .success else {
        print("Couldn't get \(attribute)")
        return nil
    }
    if let string_value = value as? String {
        return string_value
    }
    return nil
}
