/* lmem.c - Lua 4.0.1's memory manager as the game rewrote it.
 * See Copyright Notice in src/third_party/lua/lua.h.
 *
 * luaM_growaux is stock. luaM_realloc replaces the C library calls: a state with a pool allocates
 * from that pool, and everything else goes through the engine's default buffer functions. */
#include <stdlib.h>

#include "lua.h"

#include "ldo.h"
#include "lmem.h"
#include "lobject.h"
#include "lstate.h"
#include "dw4/lua_game_state.h"

extern "C" {
void *Memory_AllocateDefaultBuffer(size_t size);
void *thunk_Memory_ReallocateBuffer(void *block, size_t size);
void Memory_FreeBufferAliasA(void *block);
}


void *luaM_growaux (lua_State *L, void *block, size_t nelems,
               int inc, size_t size, const char *errormsg, size_t limit) {
  size_t newn = nelems+inc;
  if (nelems >= limit-inc) lua_error(L, errormsg);
  if ((newn ^ nelems) <= nelems ||  /* still the same power-of-2 limit? */
       (nelems > 0 && newn < MINPOWER2))  /* or block already is MINPOWER2? */
      return block;  /* do not need to reallocate */
  else  /* it crossed a power-of-2 boundary; grow to next power */
    return luaM_realloc(L, block, luaO_power2(newn)*size);
}


/*
** generic allocation routine.
*/
void *luaM_realloc (lua_State *L, void *block, lint32 size) {
  if (size >= MAX_SIZET) {
    lua_error(L, "memory allocation error: block too big");
    return NULL;
  }
  if (L != NULL) {
    igMemoryPoolView *pool = ((GameLuaState *)L)->pool;
    /* lua_open allocates the state itself before it has a pool, so that block never goes back
       to the pool: lua_close frees it through the default path below. */
    if (pool != NULL && block != L) {
      if (size == 0) {
        pool->Free(block);
        return NULL;
      }
      if (block != NULL)
        block = pool->Reallocate(block, size);
      else
        block = pool->Allocate(size);
      if (block == NULL)
        luaD_breakrun(L, LUA_ERRMEM);  /* break run without error message */
      return block;
    }
  }
  if (size == 0) {
    Memory_FreeBufferAliasA(block);
    return NULL;
  }
  if (block != NULL)
    return thunk_Memory_ReallocateBuffer(block, size);
  return Memory_AllocateDefaultBuffer(size);
}
