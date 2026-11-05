/* 0x00260f08 — FUN_00260f08 (72 bytes). Forwards to FUN_00260f88 with its second and third arguments zero and its last argument 1. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_00260f88(void *handle, int a, int b, int c, int d, int e, int f, int g, int h);

void FUN_00260f08(void *handle, int c, int d, int e, int f, int g) {
    FUN_00260f88(handle, 0, 0, c, d, e, f, g, 1);
}
