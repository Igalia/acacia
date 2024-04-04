import acacia_atspi

root = acacia_atspi.findRootAtspiNodeForName("__invalid_app_name_", 0)
assert root.isNull()
