# FLTK Dockable Group

This library uses code by Ian MacArthur implementing dockable toolbars in a portable, cross-platform manner.
Relevant fltk-general discussion:
https://groups.google.com/g/fltkgeneral/c/DX7DpKaoxh4

## Building

- If you have an installed version of CMake, you can run `cmake -Bbin` then `cmake --build bin --parallel` which will build the library along with the example.
- To disable building the example, pass `-DFL_DOCK_BUILD_EXAMPLE=OFF` to your cmake configure command, i.e. `cmake -Bbin -DFL_DOCK_BUILD_EXAMPLE=OFF`
- The build script assumes you have an installed copy of FLTK and uses CMake's find_package() command.

![image](https://user-images.githubusercontent.com/37966791/192384894-8f74f33a-6131-45d0-b50c-5916f15a6b13.png)