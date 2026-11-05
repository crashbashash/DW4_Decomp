/* 0x00260f50 — FUN_00260f50 (56 bytes). Forwards to FUN_00260f88 with its fourth and fifth arguments zero and its last argument 1. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_00260f88(void *handle, int a, int b, int c, int d, int e, int f, int g, int h);

void FUN_00260f50(void *handle, int a, int b, int e, int f, int g) {
    FUN_00260f88(handle, a, b, 0, 0, e, f, g, 1);
}
