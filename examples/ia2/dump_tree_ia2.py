import argparse
import sys

import ia2_inspect

def print_tree(node, level):
  print(("--" * level) + "> ", end="")
  msaa_role = node.get_accRole()
  ia2_role = node.ia2_role()
  if (not ia2_role or msaa_role == ia2_role):
    print(msaa_role, end="")
  else:
    print(ia2_role + " " + msaa_role, end="")

  name = node.get_accName()
  if name:
    print(" (" + name + ")", end="")
  states = node.GetStates()
  if states:
      print(f" {states}", end="")
  print()

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
