/* Build configuration of Lua's libraries for Digimon World 4, prefixed to each `lib/` file so the
 * stock text stays untouched. The game's port narrowed these two macros to 32 bits and left the
 * libraries' own `long`s at the EE's 64 (lstrlib's Capture.len is an `ld`, its stride 16). */
#include "lauxlib.h"
#undef luaL_check_long
#undef luaL_opt_long
#define luaL_check_long(L,n)	((int)luaL_check_number(L, n))
#define luaL_opt_long(L,n,d)	((int)luaL_opt_number(L, n,d))
