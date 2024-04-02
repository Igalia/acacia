const atspi = require('./atspi_inspect');

root = atspi.findRootAtspiNodeForName("_invalid_add_name__", 0);
if (!root.isNull())
    throw ("Not reachable");
