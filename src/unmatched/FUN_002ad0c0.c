/* 0x002ad0c0 — FUN_002ad0c0 (128 bytes). If FUN_002b03e8(handle, 2) and FUN_002adc40(handle, 5) both succeed, reports 1 through *status and returns whether *flag is clear; otherwise reports 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002adc40();
int FUN_002b03e8();

int FUN_002ad0c0(int handle, int *flag, int *status) {
    int result;

    if (FUN_002b03e8(handle, 2) != 0) {
        result = FUN_002adc40(handle, 5);
        if (result == 1) {
            *status = result;
            return *flag == 0;
        }
    }
    *status = 0;
    return 0;
}
