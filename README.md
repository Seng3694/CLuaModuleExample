# Example for creating a Lua module in C #

Let's assume we want to create an unnecessary `custommath` module for Lua.

## Goal ##

```lua
local custommath = require "custommath"

print(custommath.add(10, 20))
```

## How to reach our goal? ##

```C
#ifndef CUSTOM_MATH_H
#define CUSTOM_MATH_H

//c++ compatability
#ifdef __cplusplus
#define C_API_BEGIN extern "C" {
#define C_API_END }
#else
#define C_API_BEGIN
#define C_API_END
#endif // !__cplusplus

C_API_BEGIN

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <math.h>

//the functions we want to implement. names do not matter
int add(lua_State* lua);
int subtract(lua_State* lua);
int multiply(lua_State* lua);
int divide(lua_State* lua);

//the function which will be called when "require "custommath"" is called from lua
int __declspec(dllexport) luaopen_custommath(lua_State* lua);

C_API_END

#endif // !CUSTOM_MATH_H

```

The key part in this header file is this function:
```C
int __declspec(dllexport) luaopen_custommath(lua_State* lua);
```

First of all you need the `_declspec(dllexport)` because we want to create a shared library.
It is also required to have this specific signature `int luaopen[MODULE](lua_State*)` so Lua can find the function. In our case `[MODULE]` is `custommath`.

**Note**: The shared library has to have the same name as the module. In this case `custommath`.

I won't go into implementation details of the actual math functions. These are just basic Lua stack manipulations. If you are struggling with these please read the manual.

The `int luaopen_custommath(lua_State*)` implementation:

```C
int luaopen_custommath(lua_State* lua)
{
    //create table with 4 entries
    lua_createtable(lua, 0, 4);

    //set key value pairs of the table
    lua_pushstring(lua, "add");
    lua_pushcfunction(lua, &add);
    lua_settable(lua, -3);

    lua_pushstring(lua, "subtract");
    lua_pushcfunction(lua, &subtract);
    lua_settable(lua, -3);

    lua_pushstring(lua, "multiply");
    lua_pushcfunction(lua, &multiply);
    lua_settable(lua, -3);

    lua_pushstring(lua, "divide");
    lua_pushcfunction(lua, &divide);
    lua_settable(lua, -3);

    //there should now be a table on the stack with our 4 functions
    return 1;
}
```

Running the following Lua script:

```lua
local custommath = require "custommath"

local a = 1.1
local b = 2.2

print(tostring(a) .. " + " .. tostring(b) .. " = " .. tostring(custommath.add(a, b)))
print(tostring(a) .. " - " .. tostring(b) .. " = " .. tostring(custommath.subtract(a, b)))
print(tostring(a) .. " * " .. tostring(b) .. " = " .. tostring(custommath.multiply(a, b)))
print(tostring(a) .. " / " .. tostring(b) .. " = " .. tostring(custommath.divide(a, b)))

```

will result in following output:
```
1.1 + 2.2 = 3.3
1.1 - 2.2 = -1.1
1.1 * 2.2 = 2.42
1.1 / 2.2 = 0.5
```

**Note**: The Lua module can only be imported if the Lua version of the interpreter is compatible with the Lua version of the used API libraries.

This example builds a `lua.exe` and runs the [test.lua][1] script as post build process. The Lua versions are therefore exactly the same.

**Note**: You can create modules like this in C++ too. Just wrap a `extern "C"` around your code and especially around the lua includes like I did in the header file.

## External ##
- [Lua][3]

## Build ##
This project uses [CMake][2] to generate platform and compiler-specific build files. 

Build just tested on Windows. Will most likely not work on other platforms. You had to atleast change the `__declspec(dllexport)` when you are using GCC to ```__attribute__((dllexport))``` or ```__attribute__((visibility("default")))``` when GCC version is greater equal than 4. But for simplicity I decided not to do it.

1. Clone the repository with Lua submodule
    ```
    git clone --recurse-submodules https://github.com/Seng3694/CLuaModuleExample
    ```
2. Generate the build files
    ```
    mkdir bin
    cd bin
    cmake -G"Your Generator" ../CLuaModuleExample
    ```
3. Build the files
    ```
    cmake --build . --config Release
    ``` 

If everything went correct you should see this after building:
```
1.1 + 2.2 = 3.3
1.1 - 2.2 = -1.1
1.1 * 2.2 = 2.42
1.1 / 2.2 = 0.5
```

If there are errors while building, remove the `post_build` custom command in the [CMakeLists.txt][4]. You have to run the `lua` executable on your own and pass the `test.lua` script file as an argument.

[1]:scripts/test.lua
[2]:https://cmake.org/
[3]:https://github.com/lua/lua
[4]:CMakeLists.txt
