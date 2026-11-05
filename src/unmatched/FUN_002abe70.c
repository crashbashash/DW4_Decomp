/* 0x002abe70 — FUN_002abe70 (40 bytes). Posts event (7, 6) through FUN_002b0338. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int FUN_002b0338(void *handle, int group, int event, int a, int b);

/* matching construct: hand — the long return type (callee returns int) is what keeps
   retail's plain jal instead of a sibling tail call */
long FUN_002abe70(void *handle) {
    return FUN_002b0338(handle, 7, 6, 0, 0);
}
