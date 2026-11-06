/* Installs callback `index` either globally (null handle, also pushed to live handles by
 * FUN_00291318) or in a validated handle's table at +400, then notifies FUN_002914b0; slot 8
 * defaults to FUN_00291248. */
typedef void (*Callback00291250)();

int FUN_002913f8(void *handle); /* handle check; non-zero rejects */
int FUN_0028eb38(void *handle, int error);
void FUN_00291318(int index, Callback00291250 fn);
void FUN_002914b0(void *handle, int index, Callback00291250 fn);
void FUN_00291248();

struct Handle00291250 {
    char pad0[400];
    Callback00291250 callbacks[1]; /* +400 */
};

struct Pool00291250 {
    Callback00291250 callbacks[1]; /* +0: defaults for new handles */
};

extern struct Pool00291250 DAT_00573f18;

int FUN_00291250(struct Handle00291250 *handle, int index, Callback00291250 fn) {
    Callback00291250 *table;

    if (index == 8 && fn == 0) {
        fn = FUN_00291248;
    }
    if (handle == 0) {
        FUN_00291318(index, fn);
        table = DAT_00573f18.callbacks;
    } else {
        if (FUN_002913f8(handle) != 0) {
            return FUN_0028eb38(0, 0xFF030202);
        }
        table = handle->callbacks;
    }
    table[index] = fn;
    FUN_002914b0(handle, index, fn);
    return 0;
}
