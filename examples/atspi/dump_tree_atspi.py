import argparse
import sys
import atspi_inspect


def printNode(node, level):
    sep = "--" * level
    print(f"{sep}> {node.get_role_name()} ({node.get_name()})")
    for i in range(node.get_child_count()):
         printNode(node.get_child_at_index(i), level + 1)

def main():
    parser = argparse.ArgumentParser(
        description="Dumps the AT-SPI accessibility tree for the specified application")
    parser.add_argument("--pid", type=int)
    parser.add_argument("--name", type=str)
    args = parser.parse_args()

    name = args.name or ""
    pid = 0
    if args.pid is not None:
        pid = args.pid

    if not (pid or name):
      parser.print_help()
      sys.exit()

    if name:
        root = atspi_inspect.find_root_accessible_from_name(name, pid)
        msg = f"Searching for app with name '{name}'"
        if pid:
            msg += f" and pid {pid}"
        print(f"{msg}.")
    else:
        root = atspi_inspect.find_root_accessible_from_pid(pid)
    if root.is_null():
        print("Error: Application not found.")
        sys.exit()

    try:
        printNode(root, 0)
    except Exception as error:
        print(f"Error encountered printing node: {error}")

if __name__ == "__main__":
    main()
