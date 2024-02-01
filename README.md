## How to build

### On Linux

#### Dependencies

`sudo apt install cmake libatspi2.0-dev`

For Python3 bindings (optional):
* `sudo apt install swig python3-dev`

For NodeJS module (optional):
* `sudo apt install swig node-gyp`

These bindings dependencies are on my default. See *Feature Flags* section below for how to disable them.

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

And a NodeJS module `atspi_inspect.node`.
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

* Python3 bindings: `-DATSPI_PYTHON_MODULE=<ON/OFF>`, ON by default.
* NodeJS bindings: `-DATSPI_NODEJS_MODULE=<ON/OFF>`, ON by default.

### On Mac

#### Dependencies

Ensure you have XCode and Ninja installed.

```
brew install cmake
brew install ninja
brew install swig
```

If you encounter a python3_LIBRARIES not found, try updating python with:

```
brew install python
```

#### Build steps

```
% mkdir build
% cd build
% cmake .. -G 'Ninja' --fresh
% ninja
```

### On Windows

#### Dependencies

First, install Visual Studios to get the Visual Studio installer. You can then find the "Visual Studio Installer" from the windows search box thing.

Through the Visual Studio Installer, install:
- Under individual components: Clang
- Under workloads: Desktop Development

In VS Code, set the compiler:
- view -> command palette -> cmake select kit -> clang with MSVC like command line

Git for windows (this also installs git bash, very nice to have and used by default in VSCode's terminal):
- https://git-scm.com/download/win

#### Build steps

You can build and run any number of was through VS Code, such as through the command pallet (search for "build") or by right clicking on the root directories CMakeLists.txt

You can also run the following from a bash terminal:
```
% mkdir build
% cd build
% cmake ..
% cmake --build .
```

**OUTPUT FILES** for Windows are all in the `build/bin` directory, as shared libraries must be in the same folder as the executable on windows.

## Output files

The outputs will show up at the same relative path under `build/` as the path to the `CMakeLists.txt` file which defined the target, e.g. for a target defined in `lib/atspi/CMakeLists.txt`, the output will be in `build/lib/atspi/<target>`.

Currently, we build the executable:
```
% build/lib/mac/dump_tree_mac
```

As well as a python module:
```
% cd build/lib/mac/
% python
>>> import mac_inspect
```

