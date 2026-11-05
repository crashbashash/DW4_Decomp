/* 0x002ad478 — FUN_002ad478 (248 bytes). Starts playback on a handle: unless FUN_002a0dd8 refuses (error 0xFF000158) or there is no timing record, stops it (FUN_002abef0), issues the FUN_002ada78 requests 47 and, where the ids at +3512/+3516 are unset, 5 and 6, copies the 12-byte settings to +13868 and sends command 13 (FUN_002b02a0). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002a0dd8(void *handle);
void FUN_002a0bb8(void *obj, int code);
int FUN_002abef0(void *handle);
void FUN_002ada78(void *handle, int code, int arg);
void FUN_002b02a0(void *handle, int command);

struct Timing {
    char pad0[3512];
    int id3512; /* +3512 */
    int id3516; /* +3516 */
};

struct Settings12 {
    int f0, f4, f8;
};

struct Handle {
    char pad0[13864];
    struct Timing *timing;     /* +13864 */
    struct Settings12 settings; /* +13868 */
};

void FUN_002ad478(struct Handle *handle, struct Settings12 *settings) {
    struct Timing *timing;

    if (FUN_002a0dd8(handle) != 0) {
        FUN_002a0bb8(0, 0xFF000158);
        return;
    }
    timing = handle->timing;
    if (timing == 0) {
        return;
    }
    if (FUN_002abef0(handle) != 0) {
        return;
    }
    FUN_002ada78(handle, 47, 0);
    if (timing->id3512 == 0) {
        FUN_002ada78(handle, 5, 0);
    }
    if (timing->id3516 == 0) {
        FUN_002ada78(handle, 6, 0);
    }
    handle->settings = *settings;
    FUN_002b02a0(handle, 13);
}
