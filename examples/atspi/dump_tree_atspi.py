import argparse
import sys
import atspi_inspect


def printNode(node, level):
    sep = "--" * level
    print(
        f"{sep}> {node.get_role_name()} Name='{node.get_name()}' "
        f"Description='{node.get_description()}'\n"
        f"{'  ' * level}* States={tuple(sorted(node.get_states()))}\n"
        f"{'  ' * level}* Interfaces={tuple(sorted(node.get_interfaces()))}\n"
        f"{'  ' * level}* Attributes={tuple(sorted(node.get_attributes()))}"
    )

    relations = node.get_relations()
    # We dump this conditionally because most objects lack relations.
    if relations:
        print(f"{'  ' * level}* Relations={tuple(sorted(relations))}")

    # We don't check if this is null because pretty much everything implements it.
    component = node.query_component()
    print(f"{'  ' * level}* Component: {component.to_string()}")

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
        msg = f"Searching for application with name '{name}'"
        if pid:
            msg += f" and pid {pid}"
        print(f"{msg}.")
        root = atspi_inspect.find_root_accessible_from_name(name, pid)
    else:
        print(f"Searching for application with pid {pid}.")
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
