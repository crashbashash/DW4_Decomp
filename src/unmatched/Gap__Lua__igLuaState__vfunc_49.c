/* 0x00280b70 — 12 bytes. Drops its own first argument and tail-calls FUN_00129068 with the remaining
 * two (retail: `move a0,a1; j FUN_00129068; move a1,a2` — C mode, not C++, gives the direct jump). */
int FUN_00129068();
void Gap__Lua__igLuaState__vfunc_49(int unused, int a, int b) {
    FUN_00129068(a, b);
}
