/* When option 28 is set, posts state 5 through FUN_002a3200: mode 1 for a zero FUN_002a0960 value,
 * 0 otherwise, nothing for -1. */
extern int FUN_002adc40(void *handle, int option);
extern int FUN_002a0960(void *handle);
extern void FUN_002a3200(void *handle, int state, int mode);

void FUN_002a37e0(void *handle) {
    int value;
    int mode;

    if (FUN_002adc40(handle, 28) == 0) {
        return;
    }
    value = FUN_002a0960(handle);
    if (value == 0) {
        mode = 1;
    } else if (value > 0) {
        mode = 0;
    } else if (value == -1) {
        return;
    } else {
        mode = 0;
    }
    FUN_002a3200(handle, 5, mode);
}
