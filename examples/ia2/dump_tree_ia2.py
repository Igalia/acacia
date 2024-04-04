import argparse
import sys

import acacia_ia2

def print_tree(node, level):
  print(("--" * level) + "> ", end="")
  msaa_role = node.getAccRole()
  ia2 = node.QueryIA2()
  ia2_role = ia2.role()
  if (not ia2_role or msaa_role == ia2_role):
    print(msaa_role, end="")
  else:
    print(ia2_role + " " + msaa_role, end="")

  print(
      f" Name='{node.getAccName()}',"
      f" Description='{node.getAccDescription()}',",
      f" States={tuple(sorted(node.getStateStrings() + ia2.getStateStrings()))}")

  # For the purpose of this example, dump properties even if null.
  properties = ia2.toString()
  if properties:
    print("  " * level + "* " + properties)

  action = node.QueryAction()
  if not action.isNull():
    print("  " * level + "* " + action.toString())

  component = node.QueryComponent()
  if not component.isNull():
    print("  " * level + "* " + component.toString())

  hyperlink = node.QueryHyperlink()
  if not hyperlink.isNull():
    print("  " * level + "* " + hyperlink.toString())

  table2 = node.QueryTable2()
  if not table2.isNull():
    print("  " * level + "* " + table2.toString())

  table_cell = node.QueryTableCell()
  if not table_cell.isNull():
    print("  " * level + "* " + table_cell.toString())

  text = node.QueryText()
  if not text.isNull():
    print("  " * level + "* " + text.toString())

  value = node.QueryValue()
  if not value.isNull():
    print("  " * level + "* " + value.toString())

  count = node.getAccChildCount()
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
      app = acacia_ia2.findRootIANodeForName(args.name)
    else:
      app = acacia_ia2.findRootIANodeForPID(args.pid)

    if (app.isNull()):
      print("Couldn't find application")
      sys.exit()

    print_tree(app, 0)

if __name__ == "__main__":
    main()
