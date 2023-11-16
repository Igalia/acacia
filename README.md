## How to build

### On Linux

#### Dependencies

`sudo apt install libatspi2.0-dev`

For swig:
* `sudo apt install swig`

For NodeJS module (optional):

* `sudo apt install node-gyp`

#### Build steps
```
% mkdir build
% cd build
% cmake <feature-flags> .. --fresh
% make
```

This will produce the executable:
```
% build/lib/atspi/dump_tree_atspi
```

As well as a python module.
```
% cd build/lib/atspi/
% python
>>> import atspi_inspect
>>> node = atspi_inspect.find_root_accessible_from_pid(1244182)
>>> node.accessible_get_role_name()
'application'
>>> node.accessible_get_name()
'Google Chrome'
```

An optionally a NodeJS module `atspi_inspect.node`.
```
% cd build/lib/atspi/
% nodejs
> const atspi_inspect = require("./atspi_inspect");
> let node = atspi_inspect.find_root_accessible_from_pid(<pid>);
> node.accessible_get_role_name();
'application'
> node.accessible_get_name();
'Chromium'
```

#### Feature flags

* NodeJS bindings: `-DATSPI_NODEJS_MODULE=<ON/OFF>`, ON by default.

### On Mac

Ensure you have XCode, including Swift support, and Ninja installed.

```
% mkdir build
% cd build
% cmake .. -G 'Ninja' --fresh
% ninja
```

## Output files

The outputs will show up at the same relative path under `build/` as the path to the `CMakeLists.txt` file which defined the target, e.g. for a target defined in `lib/atspi/CMakeLists.txt`, the output will be in `build/lib/atspi/<target>`.
