/* Sets the handle's state at +76 to 6 when FUN_002abf78 fails. */
typedef struct SfdHandle {
    char pad0[76];
    int f76;                /* +76 */
} SfdHandle;

extern int FUN_002abf78(SfdHandle *handle);

int FUN_002ab680(SfdHandle *handle) {
    int ok = FUN_002abf78(handle);

    if (ok == 0) {
        handle->f76 = 6;
    }
    return ok;
}
