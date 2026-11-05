/* 0x0029dd80 — FUN_0029dd80 (24 bytes). Calls FUN_0029ddb0 with the same three arguments and a fourth argument of 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int FUN_0029ddb0(void *handle, int a, int b, int mode);

void FUN_0029dd80(void *handle, int a, int b) {
    FUN_0029ddb0(handle, a, b, 0);
}
