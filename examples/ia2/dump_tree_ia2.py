import argparse
import sys

import ia2_inspect

def print_tree(node, level):
  print(("--" * level) + "> ", end="")
  msaa_role = node.get_accRole()
  ia2 = ia2_inspect.IA2(node)
  ia2_role = ia2.role()
  if (not ia2_role or msaa_role == ia2_role):
    print(msaa_role, end="")
  else:
    print(ia2_role + " " + msaa_role, end="")

  print(
      f" Name='{node.get_accName()}',"
      f" Description='{node.get_accDescription()}',",
      f" States={tuple(sorted(node.GetStates() + ia2.GetStates()))}")

  properties = ia2.GetProperties()
  if properties:
      print("  " * level + "* " + properties)

  action = ia2_inspect.IAAction(node)
  properties = action.GetProperties()
  if properties:
      print("  " * level + "* " + properties)

  component = ia2_inspect.IAComponent(node)
  properties = component.GetProperties()
  if properties:
      print("  " * level + "* " + properties)

  hyperlink = ia2_inspect.IAHyperlink(node)
  properties = hyperlink.GetProperties()
  if properties:
      print("  " * level + "* " + properties)

  table2 = ia2_inspect.IATable2(node)
  properties = table2.GetProperties()
  if properties:
      print("  " * level + "* " + properties)

  table_cell = ia2_inspect.IATableCell(node)
  properties = table_cell.GetProperties()
  if properties:
      print("  " * level + "* " + properties)

  text = ia2_inspect.IAText(node)
  properties = text.GetProperties()
  if properties:
      print("  " * level + "* " + properties)

  value = ia2_inspect.IAValue(node)
  properties = value.GetProperties()
  if properties:
      print("  " * level + "* " + properties)

  count = node.get_accChildCount()
  for i in range(count):
    child = node.AccessibleChildAt(i)
    print_tree(child, level+1)
  return

def main():
    parser = argparse.ArgumentParser(
      description='Dumps the IA2 accessibility tree for an application specified by PID')
    parser.add_argument('--pid', type=int)
    parser.add_argument('--name', type=str)
    args = parser.parse_args()

    if not args.pid and not args.name:
      parser.print_help()
      sys.exit()

    if (args.name):
      app = ia2_inspect.IANode.CreateRootForName(args.name)
    else:
      app = ia2_inspect.IANode.CreateRootForPID(args.pid)

    if (app.IsNull()):
      print("Couldn't find application")
      sys.exit()

    print_tree(app, 0)

if __name__ == "__main__":
    main()
