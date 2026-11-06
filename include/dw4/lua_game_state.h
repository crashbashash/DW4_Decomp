/* lua_game_state.h - what the game added to Lua 4.0.1's state.
 *
 * The game gave every lua_State a memory pool. The stock lstate.h stays untouched in
 * src/third_party/lua/, so the addition is a derived struct: the pool word follows the stock
 * fields at +0x70, making the state 0x74 bytes.
 *
 * igMemoryPoolView is a local view of the Alchemy pool (the reflected layout is igMemoryPool in
 * dw4/reflected.h) that adds the three virtuals Lua calls. The dummies place them at vtable bytes
 * 216, 232 and 264: MWCC keeps two header words ahead of the slots, so slot N sits at 8 + 4 * N. */
#ifndef DW4_LUA_GAME_STATE_H
#define DW4_LUA_GAME_STATE_H

#include "lstate.h"

class igMemoryPoolView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5();
    virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11();
    virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17();
    virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35();
    virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41();
    virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();
    virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51();
    virtual void *Allocate(size_t size);                    /* slot 52, byte 216 */
    virtual void d53(); virtual void d54(); virtual void d55();
    virtual void *Reallocate(void *block, size_t size);     /* slot 56, byte 232 */
    virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62();
    virtual void d63();
    virtual void Free(void *block);                         /* slot 64, byte 264 */
};

struct GameLuaState : lua_State {
    igMemoryPoolView *pool;  /* +0x70: where this state's blocks come from; may be NULL */
};

#endif
