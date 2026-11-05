/* 0x0028eab8 — FUN_0028eab8 (124 bytes). Copies the handle's 20-byte block at +592 to *out once FUN_002913f8 accepts the handle (returning its 0 status); otherwise returns the report of error 0xFF030204 through FUN_0028eb38. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002913f8(void *handle); /* handle check; non-zero rejects */
int FUN_0028eb38(void *handle, int error);

struct Block0028eab8 {
    int word[5];
};

struct Handle0028eab8 {
    char pad0[592];
    struct Block0028eab8 block; /* +592 */
};

int FUN_0028eab8(struct Handle0028eab8 *handle, struct Block0028eab8 *out) {
    int status = FUN_002913f8(handle);

    if (status != 0) {
        return FUN_0028eb38(0, 0xFF030204);
    }
    *out = handle->block;
    return status;
}
