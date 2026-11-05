/* 0x002add28 — FUN_002add28 (152 bytes). Copies the handle's 160-byte status block (+0x950) to *out; reports error 0xFF000119 when FUN_002a0dd8 refuses. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002a0dd8(void *handle);
int FUN_002a0bb8(void *obj, int code);

struct Status160 {
    long words[20]; /* 8-byte aligned: copied with ld/sd */
};

struct Handle {
    char pad0[0x950];
    struct Status160 status; /* +0x950 */
};

int FUN_002add28(struct Handle *handle, struct Status160 *out) {
    if (FUN_002a0dd8(handle) != 0) {
        return FUN_002a0bb8(0, 0xFF000119);
    }
    *out = handle->status;
    return 0;
}
