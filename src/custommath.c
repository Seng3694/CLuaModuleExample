#include "custommath.h"

int add(lua_State* lua)
{
	if (lua_isnumber(lua, -1) && lua_isnumber(lua, -2))
	{
		LUA_NUMBER b = lua_tonumber(lua, -1);
		lua_pop(lua, 1);
		LUA_NUMBER a = lua_tonumber(lua, -1);
		lua_pop(lua, 1);
		lua_pushnumber(lua, a + b);

		return 1;
	}

	return 0;
}

int subtract(lua_State* lua)
{
	if (lua_isnumber(lua, -1) && lua_isnumber(lua, -2))
	{
		LUA_NUMBER b = lua_tonumber(lua, -1);
		lua_pop(lua, 1);
		LUA_NUMBER a = lua_tonumber(lua, -1);
		lua_pop(lua, 1);
		lua_pushnumber(lua, a - b);

		return 1;
	}

	return 0;
}

int multiply(lua_State* lua)
{
	if (lua_isnumber(lua, -1) && lua_isnumber(lua, -2))
	{
		LUA_NUMBER b = lua_tonumber(lua, -1);
		lua_pop(lua, 1);
		LUA_NUMBER a = lua_tonumber(lua, -1);
		lua_pop(lua, 1);
		lua_pushnumber(lua, a * b);

		return 1;
	}

	return 0;
}

int divide(lua_State* lua) 
{
	if (lua_isnumber(lua, -1) && lua_isnumber(lua, -2))
	{
		LUA_NUMBER b = lua_tonumber(lua, -1);
		lua_pop(lua, 1);
		LUA_NUMBER a = lua_tonumber(lua, -1);
		lua_pop(lua, 1);

		if(b == 0)
			lua_pushnumber(lua, (LUA_NUMBER)NAN);
		else
			lua_pushnumber(lua, a / b);

		return 1;
	}

	return 0;
}

int luaopen_custommath(lua_State* lua)
{
	lua_createtable(lua, 0, 4);

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

	return 1;
}
