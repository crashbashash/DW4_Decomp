/* 0x00291318 — FUN_00291318 (76 bytes). Stores callback `index` in every in-use handle (state 2 at +392) of the global pool. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef void (*Callback00291250)();

struct Handle00291318 {
    char pad0[392];
    int state;                     /* +392: 2 = in use */
    char pad396[400 - 396];
    Callback00291250 callbacks[1]; /* +400 */
    char pad404[1024 - 404];
};

/* Global block at DAT_00573f18 (only the members used here). */
struct Pool00291318 {
    char pad0[84];
    int count;                      /* +84 */
    struct Handle00291318 *handles; /* +88 */
};

extern struct Pool00291318 DAT_00573f18;

void FUN_00291318(int index, Callback00291250 fn) {
    struct Handle00291318 *handle = DAT_00573f18.handles;
    int count = DAT_00573f18.count;
    int i;

    for (i = 0; i < count; i++, handle++) {
        if (handle->state == 2) {
            handle->callbacks[index] = fn;
        }
    }
}
