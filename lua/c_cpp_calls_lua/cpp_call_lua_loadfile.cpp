/*
 * http://www.cnblogs.com/stephen-liu74/archive/2012/04/20/2460634.html
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

void load(lua_State* L, const char* fname, int* w, int* h)
{
   if (luaL_loadfile(L, fname) || lua_pcall(L, 0, 0, 0))
   {
      cout << "Error message is: " << lua_tostring(L, -1) << endl;
      return;
   }
   lua_getglobal(L, "width");
   lua_getglobal(L, "heigth");

   if (!lua_isnumber(L, -2))
   {
      cout << "'width' should be a number" << endl;
      return;
   }
   if (!lua_isnumber(L, -1))
   {
      cout << "'height' should be a number" << endl;
      return;
   }

   *w = lua_tointeger(L, -2);
   *h = lua_tointeger(L, -1);
}

int main(int argc, char** argv)
{
   if (argc != 2)
   {
      cout << argv[0] << " config.lua" << endl;
      return 1;
   }
   const char* fname = argv[1];

   lua_State* L = luaL_newstate();
   int width = 1400, height = 900;
   load(L, fname, &width, &height);

   cout << "width = " << width << ", heigth = " << height << endl;
   lua_close(L);

   return 0;
}
