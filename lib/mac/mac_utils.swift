import ApplicationServices

public func logInfoForPID(_ pid: pid_t) {
    let application = AXUIElementCreateApplication(pid)

    var attributes: CFArray?
    let result = AXUIElementCopyAttributeNames(application, &attributes)
    guard result == .success else {
        print("Couldn't get attributes")
        return
    }

    for attribute in attributes! as! [String] {
        switch attribute {
        case kAXTitleAttribute:
            printAttribute(application, kAXTitleAttribute)
        case kAXRoleAttribute:
            printAttribute(application, kAXRoleAttribute)
        default:
            break
        }
    }
}

func printAttribute(_ element: AXUIElement, _ attribute: String) {
    var value: CFTypeRef?
    let result = AXUIElementCopyAttributeValue(element, attribute as CFString, &value)
    guard result == .success else {
        print("Couldn't get \(attribute)")
        return
    }
    print("\(attribute) is \(value!)")
}