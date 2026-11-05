/* 0x002a0528 — FUN_002a0528 (180 bytes). Reads seven settings through getter callbacks into the first seven words of a record. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int FUN_002b21b0(void *handle, int *value);
extern int FUN_002b2200(void *handle, int *value);
extern int FUN_002b2250(void *handle, int *value);
extern int FUN_002b22a0(void *handle, int *value);
extern int FUN_002b2358(void *handle, int *value);
extern int FUN_002b23a8(void *handle, int *value);
extern int FUN_002b23f8(void *handle, int *value);
extern int FUN_002a0888(void *handle, int (*getter)(void *handle, int *value));

void FUN_002a0528(void *handle, int *out) {
    out[0] = FUN_002a0888(handle, FUN_002b21b0);
    out[1] = FUN_002a0888(handle, FUN_002b2200);
    out[2] = FUN_002a0888(handle, FUN_002b2250);
    out[3] = FUN_002a0888(handle, FUN_002b22a0);
    out[4] = FUN_002a0888(handle, FUN_002b2358);
    out[5] = FUN_002a0888(handle, FUN_002b23a8);
    out[6] = FUN_002a0888(handle, FUN_002b23f8);
}
