import ApplicationServices

public class AXAPINode {
    let ax_element: AXUIElement

    init(_ ax_element: AXUIElement) {
      self.ax_element = ax_element
    }

    public var role: String? {
      return getStringAttribute(kAXRoleAttribute)
    }

    public var title: String? {
      return getStringAttribute(kAXTitleAttribute)
    }

    func getAttributeNames() -> [String] {
        var attributes: CFArray?
        let result = AXUIElementCopyAttributeNames(ax_element, &attributes)
        guard result == .success else {
            print("Couldn't get attributes")
            return []
        }

        return attributes! as! [String]
    }

    func getStringAttribute(_ attribute: String) -> String? {
        var value: CFTypeRef?
        let result = AXUIElementCopyAttributeValue(ax_element,
                                                   attribute as CFString,
                                                   &value)
        guard result == .success else {
            print("Couldn't get \(attribute)")
            return nil
        }
        if let string_value = value as? String {
            return string_value
        }
        print("\(attribute) could not be converted to String")
        return nil
    }
}

public func createAXAPINodeForApplication(_ pid: pid_t) -> AXAPINode {
  let pid_ax_element = AXUIElementCreateApplication(pid)
  return AXAPINode(pid_ax_element)
}
