/* Installs callback `index` either globally (null handle, also forwarded to m2vlib_SetCondAll) or in a
 * validated handle's table at +24; slot 8 defaults to FUN_00285278. */
typedef void (*Callback0028af90)();

int M2VLIB_CheckHn(void *handle); /* 0 when handle is non-null and in state 2, else -1 */
void M2VERR_SetCode(void *handle, int error);
void m2vlib_SetCondAll(int index, Callback0028af90 fn);
void FUN_00285278();

struct Handle0028af90 {
    char pad0[24];
    Callback0028af90 callbacks[1]; /* +24 */
};

struct Pool0028af90 {
    Callback0028af90 callbacks[1]; /* +0: defaults for new handles */
};

extern struct Pool0028af90 m2vlib_libwork;

void M2V_SetCond(struct Handle0028af90 *handle, int index, Callback0028af90 fn) {
    Callback0028af90 *table;

    if (index == 8 && fn == 0) {
        fn = FUN_00285278;
    }
    if (handle == 0) {
        m2vlib_SetCondAll(index, fn);
        table = m2vlib_libwork.callbacks;
    } else {
        if (M2VLIB_CheckHn(handle) != 0) {
            M2VERR_SetCode(0, 0xFF030202);
            return;
        }
        table = handle->callbacks;
    }
    table[index] = fn;
}
