/* 0x0028ef50 — FUN_0028ef50 (196 bytes). Reports three values of a validated handle: +684 scaled by 2048, +700 as is, and +700 * +680 / 1800 (-1 when +680 is the 0x3FFFF "unknown" marker). Error 0xFF03020F goes through FUN_0028eb38. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002913f8(void *handle); /* handle check; non-zero rejects */
int FUN_0028eb38(void *handle, int error);

/* Members of the handle used here; roles not yet recovered. */
struct Handle0028ef50 {
    char pad0[680];
    int f680; /* +680 */
    int f684; /* +684 */
    char pad688[12];
    int f700; /* +700 */
};

int FUN_0028ef50(struct Handle0028ef50 *handle, int *out1, int *out2, int *out3) {
    if (FUN_002913f8(handle) != 0) {
        return FUN_0028eb38(0, 0xFF03020F);
    }
    *out1 = handle->f684 << 11;
    *out2 = handle->f700;
    if (handle->f680 == 0x3FFFF) {
        *out3 = -1;
    } else {
        *out3 = handle->f700 * handle->f680 / 1800;
    }
    return 0;
}
