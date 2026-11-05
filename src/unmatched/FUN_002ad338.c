/* 0x002ad338 — FUN_002ad338 (168 bytes). Clears *value, sets *pending and, once the handle's timing record (+13864) is ready (FUN_002ad1d0), queries it through FUN_002ad3e0(record, arg, value, pending); reports error 0xFF000157 when FUN_002a0dd8 refuses. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002a0dd8(void *handle);
int FUN_002a0bb8(void *obj, int code);
void FUN_002ad1d0(void *record, int *ready);
void FUN_002ad3e0(void *record, int arg, int *value, int *pending);

struct Handle {
    char pad0[13864];
    void *timing; /* +13864 */
};

int FUN_002ad338(struct Handle *handle, int arg, int *value, int *pending) {
    void **timing;
    int ready;

    *value = 0;
    *pending = 1;
    if (FUN_002a0dd8(handle) != 0) {
        return FUN_002a0bb8(0, 0xFF000157);
    }
    /* matching construct: the record address is taken after the guard */
    timing = &handle->timing;
    FUN_002ad1d0(*timing, &ready);
    if (ready == 0) {
        return 0;
    }
    FUN_002ad3e0(*timing, arg, value, pending);
    return 0;
}
