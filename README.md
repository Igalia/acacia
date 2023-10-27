## How to build

### On Linux

#### Dependencies

`sudo apt install libatspi2.0-dev`

For swig:
* `sudo apt install swig`

#### Build steps
```
% mkdir build
% cd build
% cmake .. --fresh
% make
```

This will produce the executable:
```
% build/lib/atspi/dump_tree_atspi
```

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