/* 0x00125ec0 — FUN_00125ec0 (28 bytes). Calls FUN_00125d78 with both arguments and a 16-byte scratch area on the
 * stack, returning its result. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_00125d78(void *state, void *arg, void *scratch);

int FUN_00125ec0(void *state, void *arg) {
    int scratch[4];

    return FUN_00125d78(state, arg, scratch);
}
