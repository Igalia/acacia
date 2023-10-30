%module atspi_inspect
%{
#include "atspi_node.h"
#include "linux_utils.h"
%}

%include "std_string.i"
%include <std_unique_ptr.i>
%unique_ptr(AtspiNode)

%include "atspi_node.h"
%include "linux_utils.h"
