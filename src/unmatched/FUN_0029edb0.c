/* True when option 49 or option 57 is set. */
extern int FUN_002adc40(void *handle, int option);

int FUN_0029edb0(void *handle) {
    if (FUN_002adc40(handle, 49) != 0 || FUN_002adc40(handle, 57) != 0) {
        return 1;
    }
    return 0;
}
