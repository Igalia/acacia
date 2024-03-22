import argparse
import sys
import atspi_inspect


def PrintNode(node, level):
    sep = "--" * level
    print(
        f"{sep}> {node.getRoleName()} Name='{node.getName()}' "
        f"Description='{node.getDescription()}'\n"
        f"{'  ' * level}* States={tuple(sorted(node.getStates()))}\n"
        f"{'  ' * level}* Interfaces={tuple(sorted(node.getInterfaces()))}\n"
        f"{'  ' * level}* Attributes={tuple(sorted(node.getAttributes()))}"
    )

    relations = node.getRelations()
    # We dump this conditionally because most objects lack relations.
    if relations:
        print(f"{'  ' * level}* Relations={tuple(sorted(relations))}")

    # We don't check if this is null because pretty much everything implements it.
    component = node.queryComponent()
    print(f"{'  ' * level}* Component: {component.toString()}")

    for i in range(node.getChildCount()):
         PrintNode(node.getChildAtIndex(i), level + 1)

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
        root = atspi_inspect.findRootAtspiNodeFromName(name, pid)
    else:
        print(f"Searching for application with pid {pid}.")
        root = atspi_inspect.findRootAtspiNodeFromPID(pid)
    if root.isNull():
        print("Error: Application not found.")
        sys.exit()

    try:
        PrintNode(root, 0)
    except Exception as error:
        print(f"Error encountered printing node: {error}")

if __name__ == "__main__":
    main()
