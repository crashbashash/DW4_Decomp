/* lua_game_state.h - what the game added to Lua 4.0.1's state.
 *
 * The game gave every lua_State a memory pool. The stock lstate.h stays untouched in
 * src/third_party/lua/, so the addition is a derived struct: the pool word follows the stock
 * fields at +0x70, making the state 0x74 bytes. */
#ifndef DW4_LUA_GAME_STATE_H
#define DW4_LUA_GAME_STATE_H

#include "lstate.h"
#include "dw4/igMemoryPoolView.h"

struct GameLuaState : lua_State {
    igMemoryPoolView *pool;  /* +0x70: where this state's blocks come from; may be NULL */
};

#endif
