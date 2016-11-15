/*
 * http://www.cnblogs.com/stephen-liu74/archive/2012/07/18/2433428.html
 * 
 * How to build:
 * g++ cpp_call_lua_loadbuffer.cpp -lm /usr/local/lib/liblua.a -ldl
 *
 * lua.h defines the basic functions provided by Lua
 *    - creat a new Lua environment (i.e. lua_open)
 *    - invoke Lua functions (i.e. lua_pcall)
 *    - read and write global variables in the Lua env
 *    - register new functions to be called by Lua
 *    - ...
 * luaxlib.h defines the functions provided by the auxiliary library (auxlib)
 * All its definitions start with "luaL_"
 * The lib uses the basic API provided by lua.h to provide a higher abstraction level
 */
#include <iostream>
#include <string.h>

using namespace std;

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

int main (int argc, char** argv)
{
   const char* buff = "print(\"Called from c++: Hello Lua!\")";
   int error;
   /*
    * lua_open function creates a new environment (or state)
    * When lua_open creats a fresh env, this env contains no predefined functions, not even print
    * To keep Lua small, all standard lib are provided as separated packages, so that you do not 
    * have to use them if you do not need.
    * Function lua_open was replaced by lua_newstate to allow the user to set a memory-allocation function.
    * You could use luaL_newstate from the standard lib to create a state with a standard allocation function
    * (based on realloc)
    */
   lua_State* L = luaL_newstate();
   // open all standard Lua lib into the given state
   luaL_openlibs(L);

   error = luaL_loadbuffer(L, buff, strlen(buff), "line") || lua_pcall(L, 0, 0, 0);
   int s = lua_gettop(L);
   if (error)
   {
      cout << lua_tostring(L, -1) << endl;
      lua_pop(L, 1);
   }

   lua_close(L);
   return 0;
}
