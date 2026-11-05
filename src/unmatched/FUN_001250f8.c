/* 0x001250f8 — FUN_001250f8 (28 bytes). Runs FUN_00124e10 over every stream of the state block through the walker
 * FUN_00125c90; installed as the block's cleanup hook by FUN_00125138. The shape of newlib's _cleanup_r
 * (hypothesis). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_00125c90(void *state, int (*fn)());
int FUN_00124e10();

void FUN_001250f8(void *state) {
    FUN_00125c90(state, FUN_00124e10);
}
