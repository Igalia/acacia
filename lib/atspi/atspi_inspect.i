%module atspi_inspect
%{
#include <axaccess/atspi/atspi_node.h>
#include <axaccess/atspi/linux_utils.h>
%}

%include "std_string.i"
%include <std_unique_ptr.i>
%unique_ptr(AtspiNode)

%include <axaccess/atspi/atspi_node.h>
%include <axaccess/atspi/linux_utils.h>
