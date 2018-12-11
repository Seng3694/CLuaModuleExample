#ifndef CUSTOM_MATH_H
#define CUSTOM_MATH_H

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

int add(lua_State* lua);
int subtract(lua_State* lua);
int multiply(lua_State* lua);
int divide(lua_State* lua);

int __declspec(dllexport) luaopen_custommath(lua_State* lua);

C_API_END

#endif // !CUSTOM_MATH_H
