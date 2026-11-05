/* 0x002910a0 — FUN_002910a0 (80 bytes). Returns the first 1024-byte handle of the global pool whose word at +392 is 1 (free; see FUN_00290e40), or 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */

struct Handle002910a0 {
    char pad0[392];
    int free;              /* +392: 1 = available */
    char pad396[1024 - 396];
};

/* Global block at DAT_00573f18 (only the members used here). */
struct Pool002910a0 {
    char pad0[84];
    int count;                      /* +84 */
    struct Handle002910a0 *handles; /* +88 */
};

extern struct Pool002910a0 DAT_00573f18;

struct Handle002910a0 *FUN_002910a0(void) {
    struct Handle002910a0 *handle = DAT_00573f18.handles;
    int count = DAT_00573f18.count;
    int i;

    for (i = 0; i < count; i++, handle++) {
        if (handle->free == 1) {
            return handle;
        }
    }
    return 0;
}
