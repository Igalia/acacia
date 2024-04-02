import atspi_inspect

root = atspi_inspect.findRootAtspiNodeForName("__invalid_app_name_", 0)
assert root.isNull()
