# Acacia

Acacia is a library for accessing accessibility APIs. The goal of this library to make it easier to test or inspect the accessibility APIs on any platform for any application. The library provides a thin C++ wrapper around each supported API which can be exposed in a Python C++ extension module and a NodeJS C++ addon.

Supported APIs:
* Mac's [NSAccessibility Protocol](https://developer.apple.com/documentation/appkit/nsaccessibility) (also referred to as AXAPI)
* Window's [MSAA with IAccessible2 1.3](https://wiki.linuxfoundation.org/accessibility/iaccessible2/)
* Linux's [AT-SPI](https://docs.gtk.org/atspi2/class.Accessible.html)

This library is a work in progress, no API is completely supported, yet! :) To see the supported APIs, peruse the [documentation ADD LINK TO PAGES]() or take a look at the [examples](https://github.com/Igalia/acacia/tree/main/examples).

## Contribution Guide

These project uses clang-format as specified by the .clang-format config file in the root directory. We recommend setting up a pre-commit hook, which requires python and the following steps:
* `pip install pre-commit`
* `pip install clang-format`
* `pre-commit install`

Note: on Debian, you can install with apt: `sudo apt install pre-commit clang-format`

The pre-submit hook will run clang-format the code in your staging area before committing. The commit will not succeed if a file is reformatted, and you will have to re-add the file with format changes and re-run git commit.

## Building and using the library

### Supported target languages

This library can build either a Python3 module or a NodeJS c++ addon for any of the currently support accessibility APIs. To control which bindings are build, please provide the following feature flag.

* Python3 bindings: `-DACACIA_PYTHON=<ON/OFF>`, OFF by default.
* NodeJS bindings: `-DACACIA_NODEJS=<ON/OFF>`, OFF by default.

If no target language is specified, only the c++ library and examples will be built.

#### Notes on NodeJS bindings

At present, arrays returned by the underlying c++ functions are not implemented as native JavaScript array objects. They are objects with the follow accessor functions:
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

#### Output files

This will produce a shared library, python module and node module in `build/lib/atspi/` and examples in `build/examples/`.

##### Examples

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

All examples can be used to dump information in an accessibility tree using the
PID of the browser, its name or substring thereof, or both:

```
% build/lib/atspi/dump_tree_atspi --pid=49500
% build/lib/atspi/dump_tree_atspi --name=firefox
% build/lib/atspi/dump_tree_atspi --name=chrome --pid=50319
```

##### Python module

To use the Python module:
```
% cd build/example/atspi/
% python
>>> import acacia_atspi
>>> node = acacia_atspi.findRootAtspiNodeForName("chromium")
>>> node.getRoleName()
'application'
>>> node.getName()
'Google Chrome'
>>> child = node.getChildAtIndex(0)
>>> child.getStates()
('ATSPI_STATE_ENABLED', 'ATSPI_STATE_SENSITIVE', 'ATSPI_STATE_SHOWING', 'ATSPI_STATE_VISIBLE')
>>> child.getRelations()
('ATSPI_RELATION_EMBEDS',)
>>> document = child.getTargetForRelationAtIndex(0)
>>> document.getRoleName()
'document web'
>>> action = document.queryAction()
>>> action.toString()
'doDefault, scrollBackward, scrollDown, scrollForward, scrollLeft, scrollRight, scrollUp, showContextMenu'
>>> component = document.queryComponent()
>>> component.getSize()
(3840, 2011)
>>> document.queryDocument().getDocumentAttributes()
('Title:Wikipedia, the free encyclopedia', 'MimeType:text/html', 'DocType:html', 'URI:https://en.wikipedia.org/wiki/Main_Page')
>>> link = document.getChildAtIndex(0)
>>> text = link.queryText()
>>> text.getText(0, -1)
'Jump to content'

```

##### NodeJS module

To use the NodeJS module:
```
% cd build/example/atspi/
% node
> const acacia_atspi = require("./acacia_atspi");
> let node = acacia_atspi.findRootAtspiNodeForName('firefox');
> node.getRoleName();
'application'
> node.getName();
'Firefox'
> let child = node.getChildAtIndex(0);
> let states = child.getStates();
> states.getSize();
> states.get(0);
'ATSPI_STATE_ENABLED'
> let relations = child.getRelations();
> relations.size();
2
> relations.get(0);
'ATSPI_RELATION_NODE_CHILD_OF'
> relations.get(1);
'ATSPI_RELATION_EMBEDS'
> let document = child.getTargetForRelationAtIndex(1);
> document.getRoleName();
'document web'
> document.queryDocument().getDocumentAttributes().get(1);
'DocURL:https://en.wikipedia.org/wiki/Main_Page'
> let link = document.getChildAtIndex(0);
> let text = link.queryText();
> text.getText(0, -1);
'Jump to content'
> let action = link.queryAction();
> action.toString();
'jump'
> let component = child.queryComponent();
> component.getSize();
_exports_AtspiPairIntInt { second: 2098, first: 3840 }
```

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

For the NodeJS bindings, you will need to download and build node-gyp app and put the executable on your path. One way to do this is through npm:

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
>>> import acacia_axapi
>>> app = acacia_axapi.findRootAXAPINodeForPID(12345)
>>> attribute_names = app.getAttributeNames()
>>> role = app.getStringValue('AXRole')
>>> title = app.getStringValue('AXTitle')
>>> children_count = app.getListElementCount('AXChildren')
>>> if children_count > 0:
...   first_child = app.getNodeListValueAtIndex('AXChildren', 0)
>>> children = app.getNodeListValue('AXChildren')
>>> if first_child.hasAttribute('AXRoleDescription'):
...   role_description = first_child.getStringValue('AXRoleDescription')
```

And a node C++ add-on:
```
% cd build/lib/mac/
% node
> const acacia_axapi = require("./acacia_axapi");
> let app = acacia_axapi.findRootAXAPINodeForPID(1693);
> const title = app.getStringValue('AXTitle');
> let children_count = 0;
> if (app.hasAttribute('AXChildren'))
... children_count = app.getListElementCount('AXChildren');
> let first_child;
> if (children_count > 0)
... first_child = app.getNodeListValueAtIndex('AXChildren', 0);
```

### On Windows

#### Dependencies

First, install Visual Studios to get the Visual Studio installer. You can then find the "Visual Studio Installer" from the start menu.

Through the Visual Studio Installer, install:
- Under workloads: Desktop Development
- Under individual components: C++/CLI support for v143 build tools (latest)
   - This is only necessary for buildings NodeJS bindings

Through the Microsoft Store, download Python.

Git for windows:
- https://git-scm.com/download/win

For package management, you can use scoop (https://scoop.sh/) or the windows package manager of your choice.

IMPORTANT: This project was not designed for a multi-configuration generator, like Visual Studios. Instead, please use a single configuration generator. The recommended generator is [Ninja](https://ninja-build.org/) and the following instructions will assume Ninja will be used. You can install `ninja` through scoop.

[SWIG](https://www.swig.org/) and python3 are also necessary to build both the NodeJS and python3 bindings.

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
        "-DACACIA_PYTHON=ON"
        "-DACACIA_NODEJS=ON"
    ],
    "cmake.generator": "Ninja",
```

If you are using MSVC to compile, you will need to specify the "Release" build, otherwise you will need a debug version of the Python library. In VSCode, you can use the command pallet option "Cmake: select variant", and choose "Release". If you want to build python bindings with a "Debug" build with visual studios, you will need to create a debug build of the python library to link against.

You can then build and run any number of was through VS Code, such as through the command pallet (search for "build") or by right clicking on the root directories CMakeLists.txt

##### PowerShell

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

Note: `-DCMAKE_BUILD_TYPE=Release` is necessary if you are using MSVC and only have the Release version of Python.

To turn on the Python3 and NodeJS bindings, run cmake with the following flags:
```
% cmake -DCMAKE_BUILD_TYPE=Release -DACACIA_PYTHON=ON -DACACIA_NODEJS=ON .. -G "Ninja" --fresh
```

##### OUTPUT FILES

All output files on Windows are in the `build/bin` directory, as shared libraries must be in the same folder as the executable on windows.

Currently produces the following executable:
```
./build/bin/dump_tree_ia2.exe <pid>
```

To use the python library, navigate to `build/bin`:
```
% python3
>>> import acacia_ia2
>>> app = acacia_ia2.findRootIANodeForName("firefox")
>>> app.getAccRole()
>>> app.getAccChildCount()
>>> child = app.AccessibleChildAt(3)
>>> child.getAccRole()
>>> action = child.QueryAction()
>>> action.nActions()
>>> action.getName(0)
>>> component = child.QueryComponent()
>>> component.getLocationInParent()
>>> text = child.QueryText()
>>> text.getNCharacters()
>>> text.getText(0, -1)
>>> ia2 = child.QueryIA2()
>>> ia2.getAttributes()
>>> ia2.getRelations()
```

Or run the script:
```
% python3 ./dump_tree_ia2.py --name chrome
```

NodeJS also has an example dump tree which can be run from the bin folder:
```
% node ./dump_tree_ia2.js --name chrome
```

## Testing

There is basic unit-test infrastructure, for now only available on Linux. To run the tests, simple do `make test` after a successful build.

The tests are built by default. To disable them, pass `-DACACIA_TESTS=off` to cmake.

## Installing

After building your targets successfully with `make`, simply do:

```
make install
```

Use the CMAKE variable `CMAKE_INSTALL_PREFIX` to define the root directory where the different artifacts will be placed. For example:

```
$ cmake -DCMAKE_INSTALL_PREFIX=/usr ..
```

### On Linux

On Linux, the default prefix is `/usr/local`.

Before installing, please make sure that the user has write permissions on the destination dir. Also, before using the library from the installation dir, make sure your that `<PREFIX>/lib` is added to ld.so configuration (e.g, via `LD_LIBRARY_PATH` environment variable).

### On Mac

*Not yet supported*.

### On Windows

*Not yet supported*.

## Documentation

Documentation for the different backend APIs can be automatically generated from source code via [Doxygen](https://www.doxygen.nl/download.html), which must be install locally. It is off by default; to enable it, pass `-DACACIA_DOCS=ON` to cmake.

The resulting documentation can be found in: `build/docs/docs/html`

## Experimental features

### Cross-platform Accessibility Tree (CAT) API

This is a native C++ library that will eventually abstract the other, platform-specific APIs, so that developers can target a single API regardless
of that provided by the platform. This may be useful for some use-cases (e.g, to dump the accessible tree of an
application in a cross-platform way).

The feature is governed by the feature flag `ACACIA_CAT`, currently OFF by default. To enable it,
simply pass `-DACACIA_CAT=ON` to cmake.

## License

[GNU Library General Public License version 2.1](https://www.gnu.org/licenses/old-licenses/lgpl-2.1.html), see [LICENSE](https://www.gnu.org/licenses/old-licenses/lgpl-2.1.html) file.
