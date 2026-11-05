/* 0x00291368 — FUN_00291368 (144 bytes). Reads callback `index` from the global table (null handle) or from a validated handle's table at +400 into *out; error 0xFF030210 goes through FUN_0028eb38. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef void (*Callback00291250)();

int FUN_002913f8(void *handle); /* handle check; non-zero rejects */
int FUN_0028eb38(void *handle, int error);

struct Handle00291368 {
    char pad0[400];
    Callback00291250 callbacks[1]; /* +400 */
};

/* Global block at DAT_00573f18 (only the member used here). */
struct Pool00291368 {
    Callback00291250 callbacks[1]; /* +0 */
};

extern struct Pool00291368 DAT_00573f18;

int FUN_00291368(struct Handle00291368 *handle, int index, Callback00291250 *out) {
    Callback00291250 *table;

    if (handle == 0) {
        table = DAT_00573f18.callbacks;
    } else {
        if (FUN_002913f8(handle) != 0) {
            return FUN_0028eb38(0, 0xFF030210);
        }
        table = handle->callbacks;
    }
    *out = table[index];
    return 0;
}
