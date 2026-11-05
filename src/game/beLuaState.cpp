/* src/game/beLuaState.cpp — the beLuaState methods
 *
 * One translation unit: 2 functions, in retail address order.  Folded
 * from the per-function units by tools/merge_units.py; the matching build
 * splits a function back out with tools/units.py, so `make check` still
 * verifies one function at a time. */
extern "C" {
void igLuaState_RunString(void);
void Gap__Bec__beLuaState__vfunc_21(void);
}
extern "C" {
void igLuaState_RunBuffer(void);
void Gap__Bec__beLuaState__vfunc_23(void);
}

/* 0x0038a6c0 */
void Gap__Bec__beLuaState__vfunc_21(void)
{
    igLuaState_RunString();
}

/* 0x0038ac70 */
void Gap__Bec__beLuaState__vfunc_23(void)
{
    igLuaState_RunBuffer();
}
