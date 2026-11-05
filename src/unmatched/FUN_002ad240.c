/* 0x002ad240 — FUN_002ad240 (160 bytes). Clears *out and, once the handle's timing record (+13864) is ready (FUN_002ad1d0), converts through FUN_002ad2e0(record, scale, divisor, out); reports error 0xFF000156 when FUN_002a0dd8 refuses. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002a0dd8(void *handle);
int FUN_002a0bb8(void *obj, int code);
void FUN_002ad1d0(void *record, int *ready);
void FUN_002ad2e0(void *record, int scale, int divisor, int *out);

struct Handle {
    char pad0[13864];
    void *timing; /* +13864 */
};

int FUN_002ad240(struct Handle *handle, int scale, int divisor, int *out) {
    void **timing;
    int ready;

    *out = 0;
    if (FUN_002a0dd8(handle) != 0) {
        return FUN_002a0bb8(0, 0xFF000156);
    }
    /* matching construct: the record address is taken after the guard */
    timing = &handle->timing;
    FUN_002ad1d0(*timing, &ready);
    if (ready == 0) {
        return 0;
    }
    FUN_002ad2e0(*timing, scale, divisor, out);
    return 0;
}
