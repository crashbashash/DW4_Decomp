/* 0x00285558 — FUN_00285558 (124 bytes). Copies the handle's 20-byte block at +4 to *out once FUN_0028b098 accepts the handle; otherwise reports error 0xFF030204 through FUN_002855d8. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_0028b098(void *handle); /* 0 when handle is non-null and in state 2, else -1 */
void FUN_002855d8(void *handle, int error);

struct Block00285558 {
    int word[5];
};

struct Handle00285558 {
    int state;                  /* +0 */
    struct Block00285558 block; /* +4 */
};

void FUN_00285558(struct Handle00285558 *handle, struct Block00285558 *out) {
    if (FUN_0028b098(handle) != 0) {
        FUN_002855d8(0, 0xFF030204);
        return;
    }
    *out = handle->block;
}
