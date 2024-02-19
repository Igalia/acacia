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

* Python3 bindings: `-DAXA_PYTHON_MODULE=<ON/OFF>`, ON by default.
* NodeJS bindings: `-DAXA_NODEJS_MODULE=<ON/OFF>`, ON by default.

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

For the nodeJS bindings, you will need to download and build node-gyp app and put the executable on your path. One way to do this is through npm:

```
npm install -g node-gyp
```

#### Build steps

```
% mkdir build
% cd build
% cmake .. -G 'Ninja' --fresh
% ninja
```

#### Output files

The outputs will show up at the same relative path under `build/` as the path to the `CMakeLists.txt` file which defined the target, e.g. for a target defined in `lib/mac/CMakeLists.txt`, the output will be in `build/lib/mac/<target>`.

Currently, we build the executable:
```
% build/examples/mac/dump_tree_mac
```

As well as a python module:
```
% cd build/lib/mac/
% python3
>>> import mac_inspect
>>> app = mac_inspect.AXAPINode.CreateForPID(12345)
>>> attribute_names = app.CopyAttributeNames()
>>> role = app.CopyStringAttributeValue('AXRole')
>>> title = app.CopyStringAttributeValue('AXTitle')
>>> children_count = app.GetListAttributeValueCount('AXChildren')
>>> if children_count > 0:
...   first_child = app.CopyNodeListAttributeValueAtIndex('AXChildren', 0)
>>> children = CopyNodeListAttributeValue('AXChildren')
>>> if first_child.HasAttribute('AXRoleDescription)
...   role_description = first_child.CopyStringAttributeValue('AXRoleDescription')
```

And a node C++ add-on:
```
% cd build/lib/mac/
% node
> const axapi_inspect = require("./axapi_inspect");
> let app = axapi_inspect.AXAPINode.CreateForPID(12345);
> const title = app.CopyStringAttributeValue('AXTitle');
> let children_count = 0;
> if (app.HasAttribute('AXChildren'))
... children_count = app.GetListAttributeValueCount('AXChildren');
> let first_child;
> if (children_count > 0)
... first_child = app.CopyNodeListAttributeValueAtIndex('AXChildren', 0);
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

