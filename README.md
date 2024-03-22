## Contribution Guide

Thes project uses clang-format as specified by the .clang-format config file in the root directory. We recommend setting up a pre-commit hook, which requires python and the following steps:
* `pip install pre-commit`
* `pip install clang-format`
* `pre-commit install`

The pre-submit hook will run clang-format the code in your staging area before commiting. The commit will not succeed if a file is reformatted, and you will have to re-add the file with format changes and re-run git commit.

## How to build

### Supported target languages

This library can build either a Python3 module or a NodeJS c++ addon for any of the currently support accessibility APIs. To control which bindings are build, please provide the following feature flag.

* Python3 bindings: `-DAXA_PYTHON_MODULE=<ON/OFF>`, OFF by default.
* NodeJS bindings: `-DAXA_NODEJS_MODULE=<ON/OFF>`, OFF by default.

If no target language is specified, only the c++ library and examples will be built.

#### Notes on NodeJS bindings

At present, arrays returned by the underlaying c++ functions are not implemented as native javascript array objects. They are objects with the follow accessor functions:
* `equals`
* `size`
* `capacity`
* `reserve`
* `isEmpty`
* `clear`
* `add`
* `get`
* `set`
* `constructor`

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

This will produce the executable `build/lib/atspi/dump_tree_atspi` which can be used with either the
PID of the browser, its name or substring thereof, or both:

```
% build/lib/atspi/dump_tree_atspi --pid=49500
% build/lib/atspi/dump_tree_atspi --name=firefox
% build/lib/atspi/dump_tree_atspi --name=chrom --pid=50319
```

As well as a python module.
```
% cd build/lib/atspi/
% python
>>> import atspi_inspect
>>> node = atspi_inspect.findRootAtspiNodeFromPID(1244182)
>>> node.getRoleName()
'application'
>>> node.getName()
'Google Chrome'
>>> child = node.getChildAtIndex(0)
>>> child.getStates()
('ATSPI_STATE_ENABLED', 'ATSPI_STATE_SENSITIVE', 'ATSPI_STATE_SHOWING', 'ATSPI_STATE_VISIBLE')
>>> child.getRelations()
('ATSPI_RELATION_EMBEDS',)
>>> component = child.queryComponent()
>>> component.getSize()
(3840, 2160)
```

And a NodeJS module `atspi_inspect.node`.
```
% cd build/lib/atspi/
% node
> const atspi_inspect = require("./atspi_inspect");
> let node = atspi_inspect.findRootAtspiNodeFromPID(49500);
> node.getRoleName();
'application'
> node.getName();
'Firefox'
> let child = node.getChildAtIndex(0);
> let states = child.getStates();
> states.getSize()
> states.get(0)
'ATSPI_STATE_ENABLED'
> let relations = child.getRelations();
> relations.size()
2
> relations.get(0)
'ATSPI_RELATION_NODE_CHILD_OF'
> relations.get(1)
'ATSPI_RELATION_EMBEDS'
> component = child.queryComponent()
> component.getSize()
_exports_AtspiPairIntInt { second: 2098, first: 3840 }
```

#### Examples

An `examples/atspi` folder will be created under the build directory
containing example programs that show how the API can be used.

* `dump_tree_atspi`: Dumps the accessible tree of a running application given
                     its process ID and/or name as shown in the build steps.
* `dump_tree_atspi.js`: If the NodeJS bindings feature is enabled, this program
                     can be run using the same arguments as the executable via
                     `node examples/atspi/dump_tree_atspi.js`.
* `dump_tree_atspi.py`: If the Python bindings feature is enabled, this program
                     can be run using the same arguments as the executable via
                     `python examples/atspi/dump_tree_atspi.py`.


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
> const mac_inspect = require("./mac_inspect");
> let app = mac_inspect.AXAPINode.CreateForPID(12345);
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
- Under individual components: C++/CLI support for v143 build tools (latest)
   - This is only necessary for buildings NodeJS bindings

Through the Microsoft Store, download Python.

Git for windows (this also installs git bash, very nice to have and used by default in VSCode's terminal):
- https://git-scm.com/download/win

For package management, you can use scoop (https://scoop.sh/) or the windows package manager of your choice.

IMPORTANT: This project was not designed for a multi-configuration generator, like Visual Studios. Instead, please use a single configuration generator. The recommended generator is [Ninja](https://ninja-build.org/) and the following instructions will assume Ninja will be used. You can install `ninja` through scoop.

[SWIG](https://www.swig.org/) and python3 are also necessary to build both the nodejs and python3 bindings.
```
scoop install swig python ninja
```

For the nodeJS bindings, you will need to download and build node-gyp app and put the executable on your path. One way to do this is through npm:
```
npm install -g node-gyp
```

#### Build steps

##### VS Code

Add the following to your settings.json:
```
    "cmake.configureArgs": [
        "-DAXA_PYTHON_MODULE=ON"
        "-DAXA_NODEJS_MODULE=ON"
    ],
    "cmake.generator": "Ninja",
```

If you are using MSVC to compile, you will need to specify the "release" build, otherwise you will need a debug version of the python library. In VSCode, you can use the command pallet option "Cmake: select variant", and choose "Release". If you want to build python bindings with a "Debug" build with visual studios, you will need to create a debug build of the python library to link against.

You can then build and run any number of was through VS Code, such as through the command pallet (search for "build") or by right clicking on the root directories CMakeLists.txt

##### Powershell

To build from PowerShell, first you have to import and run the DevShell module:
```
Import-Module "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\Microsoft.VisualStudio.DevShell.dll"
Enter-VsDevShell -arch amd64  -VsInstallPath "C:\Program Files\Microsoft Visual Studio\2022\Community\"
```

Then, to build:
```
% mkdir build
% cd build
% cmake -DCMAKE_BUILD_TYPE=Release <binding-flags> .. -G "Ninja" --fresh
% ninja
```

Note: `-DCMAKE_BUILD_TYPE=Release` is necessary if you are using msvc and only have the Release version of Python.

To turn on the Python3 and NodeJS bindings, run cmake with the following flags:
```
% cmake -DCMAKE_BUILD_TYPE=Release -DAXA_PYTHON_MODULE=ON -DAXA_NODEJS_MODULE=ON .. -G "Ninja" --fresh
```

**OUTPUT FILES** for Windows are all in the `build/bin` directory, as shared libraries must be in the same folder as the executable on windows.

Currently produces the following executable:
```
./build/bin/dump_tree_ia2.exe <pid>
```

To use the python library, navigate to `build/bin`:
```
% python3
>>> import ia2_inspect
>>> app = ia2_inspect.IANode.CreateRootForName("firefox")
>>> app.get_accRole()
>>> app.get_accChildCount()
>>> child = app.AccessibleChildAt(3)
>>> child.get_accRole()
>>> action = child.QueryAction()
>>> action.nActions()
>>> action.getName(0)
>>> component = child.QueryComponent()
>>> component.get_locationInParent()
>>> text = child.QueryText()
>>> text.get_nCharacters()
>>> text.get_text(0, -1)
>>> ia2 = child.QueryIA2()
>>> ia2.get_attributes()
>>> ia2.GetRelations()
```

Or run the script:
```
% python3 ./dump_tree_ia2.py --name chrome
```

NodeJS also has an example dump tree which can be run from the bin folder:
```
% node ./dump_tree_ia2.js --name chrome
```

## Documentation

Documentation for the different backend APIs can be automatically generated from source code via [Doxygen](https://www.doxygen.nl/download.html), which must be install locally. It is off by default; to enable it, pass `-DAXA_BUILD_DOC=ON` to cmake.

The resulting documentation can be found in: `build/docs/docs/html`

## Experimental features

### Cross-platform API

This is a native C++ library that will eventually abstract the other, platform-specifc APIs, so that developers can target a single API regardless
of that provided by the platform. This may be useful for some use-cases (e.g, to dump the accessible tree of an
application in a cross-platform way).

The feature is governed by the feature flag `AXA_LIBAXACCESS`, currently OFF by default. To enable it,
simply pass `-DAXA_LIBAXACCESS=ON` to cmake.
