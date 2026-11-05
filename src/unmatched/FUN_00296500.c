/* 0x00296500 — FUN_00296500 (24 bytes). Forwards its two arguments to FUN_00296530 with mode 3. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern void FUN_00296530(int a, int b, int mode);

void FUN_00296500(int a, int b) {
    FUN_00296530(a, b, 3);
}
