/* lstate.c - Lua 4.0.1's global state as the game rewrote it. See Copyright Notice in lua.h. The
 * one change from stock is lua_open's second argument, the memory pool the state allocates from
 * (the only caller is beLuaState's setup). Stock lua.h declares the one-argument lua_open, so this
 * definition is an overload of that declaration. */
#include <stdio.h>

#include "lua.h"

#include "ldo.h"
#include "lgc.h"
#include "llex.h"
#include "lmem.h"
#include "lstate.h"
#include "lstring.h"
#include "ltable.h"
#include "ltm.h"
#include "dw4/lua_game_state.h"

/*
** built-in implementation for ERRORMESSAGE. In a "correct" environment
** ERRORMESSAGE should have an external definition, and so this function
** would not be used.
*/
static int errormessage (lua_State *L) {
  const char *s = lua_tostring(L, 1);
  if (s == NULL) s = "(no message)";
  fprintf(stderr, "error: %s\n", s);
  return 0;
}

/*
** open parts that may cause memory-allocation errors
*/
static void f_luaopen (lua_State *L, void *ud) {
  int stacksize = *(int *)ud;
  if (stacksize == 0)
    stacksize = DEFAULT_STACK_SIZE;
  else
    stacksize += LUA_MINSTACK;
  L->gt = luaH_new(L, 10);  /* table of globals */
  luaD_init(L, stacksize);
  luaS_init(L);
  luaX_init(L);
  luaT_init(L);
  lua_newtable(L);
  lua_ref(L, 1);  /* create registry */
  lua_register(L, LUA_ERRORMESSAGE, errormessage);
}

lua_State *lua_open (int stacksize, igMemoryPoolView *pool) {
  GameLuaState *L = luaM_new(NULL, GameLuaState);
  if (L == NULL) return NULL;  /* memory allocation error */
  L->stack = NULL;
  L->strt.size = L->udt.size = 0;
  L->strt.nuse = L->udt.nuse = 0;
  L->strt.hash = NULL;
  L->udt.hash = NULL;
  L->Mbuffer = NULL;
  L->Mbuffsize = 0;
  L->rootproto = NULL;
  L->rootcl = NULL;
  L->roottable = NULL;
  L->TMtable = NULL;
  L->last_tag = -1;
  L->refArray = NULL;
  L->refSize = 0;
  L->refFree = NONEXT;
  L->nblocks = sizeof(GameLuaState);
  L->GCthreshold = MAX_INT;  /* to avoid GC during pre-definitions */
  L->callhook = NULL;
  L->linehook = NULL;
  L->allowhooks = 1;
  L->errorJmp = NULL;
  L->pool = pool;
  if (luaD_runprotected(L, f_luaopen, &stacksize) != 0) {
    /* memory allocation error: free partial state */
    lua_close(L);
    return NULL;
  }
  L->GCthreshold = 2*L->nblocks;
  return L;
}

void lua_close (lua_State *L) {
  luaC_collect(L, 1);  /* collect all elements */
  luaS_freeall(L);
  if (L->stack)
    L->nblocks -= (L->stack_last - L->stack + 1)*sizeof(TObject);
  luaM_free(L, L->stack);
  L->nblocks -= (L->last_tag+1)*sizeof(struct TM);
  luaM_free(L, L->TMtable);
  L->nblocks -= (L->refSize)*sizeof(struct Ref);
  luaM_free(L, L->refArray);
  L->nblocks -= (L->Mbuffsize)*sizeof(char);
  luaM_free(L, L->Mbuffer);
  luaM_free(L, L);
}
