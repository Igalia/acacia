## How to build

```
% mkdir build && cmake -B build
% cd build
% make
```

The outputs will show up at the same relative path under `build/` as the path to the `CMakeLists.txt` file which defined the target, e.g. for a target defined in `lib/atspi/CMakeLists.txt`, the output will be in `build/lib/atspi/<target>`.