/* 0x0026aab8 — FUN_0026aab8 (44 bytes). Stores FUN_002702e8(object) in *out and returns 1. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002702e8(void *object);

int FUN_0026aab8(void *object, int *out) {
    *out = FUN_002702e8(object);
    return 1;
}
