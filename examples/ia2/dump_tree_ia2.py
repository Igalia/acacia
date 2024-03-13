import argparse
import sys

import ia2_inspect

def print_tree(node, level):
  print(("--" * level) + "> ", end="")
  msaa_role = node.get_accRole()
  ia2 = node.QueryIA2()
  ia2_role = ia2.role()
  if (not ia2_role or msaa_role == ia2_role):
    print(msaa_role, end="")
  else:
    print(ia2_role + " " + msaa_role, end="")

  print(
      f" Name='{node.get_accName()}',"
      f" Description='{node.get_accDescription()}',",
      f" States={tuple(sorted(node.GetStates() + ia2.GetStates()))}")

  # For the purpose of this example, dump properties even if null.
  properties = ia2.GetProperties()
  if properties:
    print("  " * level + "* " + properties)

  action = node.QueryAction()
  if not action.IsNull():
    print("  " * level + "* " + action.GetProperties())

  component = node.QueryComponent()
  if not component.IsNull():
    print("  " * level + "* " + component.GetProperties())

  hyperlink = node.QueryHyperlink()
  if not hyperlink.IsNull():
    print("  " * level + "* " + hyperlink.GetProperties())

  table2 = node.QueryTable2()
  if not table2.IsNull():
    print("  " * level + "* " + table2.GetProperties())

  table_cell = node.QueryTableCell()
  if not table_cell.IsNull():
    print("  " * level + "* " + table_cell.GetProperties())

  text = node.QueryText()
  if not text.IsNull():
    print("  " * level + "* " + text.GetProperties())

  value = node.QueryValue()
  if not value.IsNull():
    print("  " * level + "* " + value.GetProperties())

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
