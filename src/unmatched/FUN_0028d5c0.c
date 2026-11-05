/* 0x0028d5c0 — FUN_0028d5c0 (148 bytes). Copies the handle's 32-byte block at +40 to *out once FUN_0028da60 accepts the handle (returning its 0 status); otherwise returns FUN_0028d890's report of 0xFF020202. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_0028da60(void *handle);
int FUN_0028d890(void *handle, int error);

struct Block0028d5c0 {
    int word[8];
};

struct Handle0028d5c0 {
    char pad0[40];
    struct Block0028d5c0 block; /* +40 */
};

int FUN_0028d5c0(struct Handle0028d5c0 *handle, struct Block0028d5c0 *out) {
    int status = FUN_0028da60(handle);

    if (status != 0) {
        return FUN_0028d890(0, 0xFF020202);
    }
    *out = handle->block;
    return status;
}
