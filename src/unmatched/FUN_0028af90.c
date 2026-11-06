/* Installs callback `index` either globally (null handle, also forwarded to FUN_0028b040) or in a
 * validated handle's table at +24; slot 8 defaults to FUN_00285278. */
typedef void (*Callback0028af90)();

int FUN_0028b098(void *handle); /* 0 when handle is non-null and in state 2, else -1 */
void FUN_002855d8(void *handle, int error);
void FUN_0028b040(int index, Callback0028af90 fn);
void FUN_00285278();

struct Handle0028af90 {
    char pad0[24];
    Callback0028af90 callbacks[1]; /* +24 */
};

/* Global block at DAT_00573eb8 (only the member used here). */
struct Pool0028af90 {
    Callback0028af90 callbacks[1]; /* +0: defaults for new handles */
};

extern struct Pool0028af90 DAT_00573eb8;

void FUN_0028af90(struct Handle0028af90 *handle, int index, Callback0028af90 fn) {
    Callback0028af90 *table;

    if (index == 8 && fn == 0) {
        fn = FUN_00285278;
    }
    if (handle == 0) {
        FUN_0028b040(index, fn);
        table = DAT_00573eb8.callbacks;
    } else {
        if (FUN_0028b098(handle) != 0) {
            FUN_002855d8(0, 0xFF030202);
            return;
        }
        table = handle->callbacks;
    }
    table[index] = fn;
}
