/* 0x00297f60 — FUN_00297f60 (24 bytes). Forwards its three arguments to FUN_00298028 with a zero fourth argument. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern void FUN_00298028(int a, int b, int c, int d);

void FUN_00297f60(int a, int b, int c) {
    FUN_00298028(a, b, c, 0);
}
