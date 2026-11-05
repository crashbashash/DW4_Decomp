/* 0x002abef0 — FUN_002abef0 (100 bytes). Unless the handle is already in state 1, runs FUN_002abf78 and, when that does not take over, resets the state words and runs FUN_002abfd8 inside a FUN_002abf58(1)/FUN_002abf58(0) bracket. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002abf78(void *handle);
void FUN_002abf58(int on);
int FUN_002abfd8(void *handle);

struct Handle {
    char pad0[72];
    int state;    /* +72 */
    int substate; /* +76 */
};

int FUN_002abef0(struct Handle *handle) {
    int result;

    if (handle->state == 1) {
        return 0;
    }
    result = FUN_002abf78(handle);
    if (result != 0) {
        return result;
    }
    handle->substate = 0;
    handle->state = 0;
    FUN_002abf58(1);
    result = FUN_002abfd8(handle);
    FUN_002abf58(0);
    return result;
}
