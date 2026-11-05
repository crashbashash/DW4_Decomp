/* 0x0029de58 — FUN_0029de58 (24 bytes). Calls FUN_0029de88 with the same three arguments and a fourth argument of 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int FUN_0029de88(void *handle, int a, int b, int mode);

void FUN_0029de58(void *handle, int a, int b) {
    FUN_0029de88(handle, a, b, 0);
}
