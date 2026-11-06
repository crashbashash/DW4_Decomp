/* Returns the first 1664-byte handle in the global pool whose state is 1, or 0. */

struct Handle0028ae28 {
    int state;            /* +0: 1 = selected by this search */
    char pad4[1664 - 4];
};

struct Pool0028ae28 {
    char pad0[64];
    int count;                       /* +64 */
    struct Handle0028ae28 *handles;  /* +68 */
};

extern struct Pool0028ae28 DAT_00573eb8;

struct Handle0028ae28 *FUN_0028ae28(void) {
    struct Handle0028ae28 *handle = DAT_00573eb8.handles;
    int i;

    for (i = 0; i < DAT_00573eb8.count; i++, handle++) {
        if (handle->state == 1) {
            return handle;
        }
    }
    return 0;
}
