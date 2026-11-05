/* 0x002939a8 — FUN_002939a8 (116 bytes). Passes FUN_00297f30 a flag: whether FUN_00294838 is 1, or, when FUN_00293f50 returns 1, whether FUN_00298ae8 also returns 1. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_00294838(void *handle);
int FUN_00293f50(void *handle);
int FUN_00298ae8(void *handle);
void FUN_00297f30(void *handle, int flag);

void FUN_002939a8(void *handle) {
    int on = 1; /* matching construct: manual — retail keeps this 1 in a saved register */
    int flag;
    int mode;

    flag = FUN_00294838(handle) == on;
    mode = FUN_00293f50(handle);
    if (mode == on) {
        flag = FUN_00298ae8(handle) == mode;
    }
    FUN_00297f30(handle, flag);
}
