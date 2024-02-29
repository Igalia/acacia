## Contribution Guide

Thes project uses clang-format as specified by the .clang-format config file in the root directory. We recommend setting up a pre-commit hook, which requires python and the following steps:
* `pip install pre-commit`
* `pip install clang-format`
* `pre-commit install`

The pre-submit hook will run clang-format the code in your staging area before commiting. The commit will not succeed if a file is reformatted, and you will have to re-add the file with format changes and re-run git commit.

## How to build

### Supported target languages

This library can build either a Python3 module or a NodeJS c++ addon for any of the currently support accessibility APIs (except on windows, remove this parenthetical at the appropriate time). To control which bindings are build, please provide the following feature flag.

* Python3 bindings: `-DAXA_PYTHON_MODULE=<ON/OFF>`, OFF by default.
* NodeJS bindings: `-DAXA_NODEJS_MODULE=<ON/OFF>`, OFF by default.

If no target language is specified, only the c++ library and examples will be built.

### On Linux

#### Dependencies

On Debian-like systems:

`sudo apt install cmake libatspi2.0-dev`

For Python3 bindings (optional):
* `sudo apt install swig python3-dev`

For NodeJS module (optional):
* `sudo apt install swig libnode-dev node-gyp`

There is a known issue linking the NodeJS module with the Debian default linker. So using the gold linker
is recommended:

```
$ sudo ln -sf /usr/bin/ld.gold /usr/bin/ld
```

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
>>> node.get_role_name()
'application'
>>> node.get_name()
'Google Chrome'
```

And a NodeJS module `atspi_inspect.node`.
```
% cd build/lib/atspi/
% nodejs
> const atspi_inspect = require("./atspi_inspect");
> let node = atspi_inspect.find_root_accessible_from_pid(<pid>);
> node.get_role_name();
'application'
> node.get_name();
'Chromium'
```

#### Examples

An `examples/atspi` folder will be created under the build directory
containing example programs that show how the API can be used.

* *dump_tree_atspi*: Dumps the accessible tree of a running application given
                     its process ID. For now it shows only Role and Name of
                     each node.
                     If NodeJS bindings feature is enabled, there is also a
                     `dump_tree_atspi.js` program which can be run as
                     `nodejs examples/atspi/dump_tree_atspi.js <pid>`.

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

For `pre-commit`:
* `pip install pre-commit`
* `pip install clang-format`
* `pre-commit install`

#### Build steps

```
% mkdir build
% cd build
% cmake <feature-flags> .. -G 'Ninja' --fresh
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

First, install Visual Studios to get the Visual Studio installer. You can then find the "Visual Studio Installer" from the start menu.

Through the Visual Studio Installer, install:
- Under workloads: Desktop Development

Git for windows (this also installs git bash, very nice to have and used by default in VSCode's terminal):
- https://git-scm.com/download/win

For package management, you can use scoop: https://scoop.sh/

```
scoop install swig python
```

If you are using MSVC to compile, you will need to specify the "release" build, otherwise you will need a debug version of the python library. In VSCode, you can use the command pallet option "Cmake: select variant", and choose "Release".

#### Build steps

You can build and run any number of was through VS Code, such as through the command pallet (search for "build") or by right clicking on the root directories CMakeLists.txt

You can also run the following from a bash terminal:
```
% mkdir build
% cd build
% cmake ..
% cmake --build . --config Release
```

Note: If you want to build python bindings with a "Debug" build with visual studios, you will need to create a debug build of the python library to link against.

**OUTPUT FILES** for Windows are all in the `build/bin` directory, as shared libraries must be in the same folder as the executable on windows.

Currently produces the following executable:
```
./build/bin/Release/dump_tree_ia2.exe <pid>
```

To use the python library, navigate to `build/bin/Release`:
```
$ python3
>>> import ia2_inspect
>>> app = ia2_inspect.IA2Node.CreateForPID(4956)
>>> role = app.get_accName()
>>> child_count = app.get_accChildCount()
>>> child = app.AccessibleChildAt(0)
>>> child.get_accRole()
```

## Experimental features

### Cross-platform API

This is a native C++ library that will eventually abstract the other, platform-specifc APIs, so that developers can target a single API regardless
of that provided by the platform. This may be useful for some use-cases (e.g, to dump the accessible tree of an
application in a cross-platform way).

The feature is governed by the feature flag `AXA_LIBAXACCESS`, currently OFF by default. To enable it,
simply pass `-DAXA_LIBAXACCESS=ON` to cmake.
