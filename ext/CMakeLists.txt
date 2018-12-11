
#lua
add_library(lib_lua
    lua/lapi.c
    lua/lcode.c
    lua/lctype.c
    lua/ldebug.c
    lua/ldo.c
    lua/ldump.c
    lua/lfunc.c
    lua/lgc.c
    lua/llex.c
    lua/lmem.c
    lua/lobject.c
    lua/lopcodes.c
    lua/lparser.c
    lua/lstate.c
    lua/lstring.c
    lua/ltable.c
    lua/ltm.c
    lua/lundump.c
    lua/lvm.c
    lua/lzio.c
    lua/ltests.c)
add_library(lib_lauxlib lua/lauxlib.c)
add_library(lib_lualib
    lua/lbaselib.c
    lua/lcorolib.c
    lua/ldblib.c
    lua/linit.c
    lua/liolib.c
    lua/lmathlib.c
    lua/loadlib.c
    lua/loslib.c
    lua/lstrlib.c
    lua/ltablib.c
    lua/lutf8lib.c)

target_compile_definitions(lib_lua PUBLIC LUA_FLOORN2I=1)
target_include_directories(lib_lua PUBLIC lua)
target_include_directories(lib_lauxlib PUBLIC lua)
target_include_directories(lib_lualib PUBLIC lua)
target_link_libraries(lib_lauxlib lib_lua)
