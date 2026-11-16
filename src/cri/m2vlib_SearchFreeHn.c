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

extern struct Pool0028ae28 m2vlib_libwork;

struct Handle0028ae28 *m2vlib_SearchFreeHn(void) {
    struct Handle0028ae28 *handle = m2vlib_libwork.handles;
    int i;

    for (i = 0; i < m2vlib_libwork.count; i++, handle++) {
        if (handle->state == 1) {
            return handle;
        }
    }
    return 0;
}
