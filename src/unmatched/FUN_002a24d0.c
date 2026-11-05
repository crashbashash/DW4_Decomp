/* 0x002a24d0 — FUN_002a24d0 (84 bytes). Per-frame update: samples two values with FUN_002a27d8, then runs five update steps on the handle. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern void FUN_002a27d8(void *handle, int *a, int *b);
extern void FUN_002a2528(void *handle);
extern void FUN_002a2888(void *handle);
extern void FUN_002a26e0(void *handle);
extern void FUN_002a2920(void *handle);
extern void FUN_002a29d0(void *handle);

void FUN_002a24d0(void *handle) {
    int a;
    int b;

    FUN_002a27d8(handle, &a, &b);
    FUN_002a2528(handle);
    FUN_002a2888(handle);
    FUN_002a26e0(handle);
    FUN_002a2920(handle);
    FUN_002a29d0(handle);
}
