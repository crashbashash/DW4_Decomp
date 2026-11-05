/* 0x002abf78 — FUN_002abf78 (92 bytes). In state 4 tries FUN_002b0338(handle, 7, 7, 0, 0) and returns its result when non-zero; otherwise moves the handle to state 1 and returns 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002b0338(void *handle, int a, int b, int c, int d);

struct Handle {
    char pad0[72];
    int state;    /* +72 */
    int substate; /* +76 */
};

int FUN_002abf78(struct Handle *handle) {
    int result;

    if (handle->state == 4) {
        result = FUN_002b0338(handle, 7, 7, 0, 0);
        if (result != 0) {
            return result;
        }
    }
    handle->state = 1;
    handle->substate = 1;
    return 0;
}
