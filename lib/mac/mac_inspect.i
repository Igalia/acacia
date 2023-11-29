%module mac_inspect
%{
#include <axaccess/mac/mac_inspect.h>
%}

%include "std_string.i"

void logInfoForPID(int32_t pid);
