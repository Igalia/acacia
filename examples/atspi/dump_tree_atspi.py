import sys
import atspi_inspect

def printUsage():
    print("Usage: \npython dump_tree_atspi.py <pid>\n")

pid = sys.argv[1] if len(sys.argv) > 1 else None
if pid is None:
    printUsage()
    print ("Error: missing <pid> argument.")
    sys.exit()

try:
    pid = int(pid)
except:
    printUsage()
    print (f"Error: invalid <pid> argument '{pid}'.")
    sys.exit()

root = atspi_inspect.find_root_accessible_from_pid(int(pid))
if root.is_null():
    print(f"Error: no accessible application found for pid '{pid}'.");
    sys.exit()

def printNode(node, level):
    sep = "--" * level
    print(f"{sep}> {node.get_role_name()} ({node.get_name()})")
    for i in range(node.get_child_count()):
         printNode(node.get_child_at_index(i), level + 1)

try:
    printNode(root, 0)
except RuntimeError:
    print("Runtime error")
