## How to build

### On Linux

```
% mkdir build
% cd build
% cmake .. --fresh
% make
```

### On Mac

Ensure you have XCode, including Swift support, and Ninja installed.

```
% mkdir build
% cd build
% cmake .. -G 'Ninja' --fresh
% ninja
```

The outputs will show up at the same relative path under `build/` as the path to the `CMakeLists.txt` file which defined the target, e.g. for a target defined in `lib/atspi/CMakeLists.txt`, the output will be in `build/lib/atspi/<target>`.