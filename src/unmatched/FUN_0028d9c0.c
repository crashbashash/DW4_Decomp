/* 0x0028d9c0 — FUN_0028d9c0 (160 bytes). Copies a 12-byte block to *out: the global defaults for a null handle, else the validated handle's block at +4 (error 0xFF020102 through FUN_0028d890). Returns 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_0028da60(void *handle);
int FUN_0028d890(void *handle, int error);

struct Block0028d9c0 {
    int word[3];
};

struct Handle0028d9c0 {
    int state;                  /* +0 */
    struct Block0028d9c0 block; /* +4 */
};

extern struct Block0028d9c0 *DAT_004bcc68; /* global defaults (first member of the shared state) */

int FUN_0028d9c0(struct Handle0028d9c0 *handle, struct Block0028d9c0 *out) {
    if (handle == 0) {
        *out = *DAT_004bcc68;
    } else {
        if (FUN_0028da60(handle) != 0) {
            return FUN_0028d890(0, 0xFF020102);
        }
        *out = handle->block;
    }
    return 0;
}
