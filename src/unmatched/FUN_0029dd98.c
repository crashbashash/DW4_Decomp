/* 0x0029dd98 — FUN_0029dd98 (24 bytes). Calls FUN_0029ddb0 with the same three arguments and a fourth argument of 1. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int FUN_0029ddb0(void *handle, int a, int b, int mode);

void FUN_0029dd98(void *handle, int a, int b) {
    FUN_0029ddb0(handle, a, b, 1);
}
