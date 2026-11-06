/* Calls FUN_0029d188 when option 6 is set. */
extern int FUN_002adc40(void *handle, int option);
extern void FUN_0029d188(void *handle);

void FUN_0029d148(void *handle) {
    if (FUN_002adc40(handle, 6) != 0) {
        FUN_0029d188(handle);
    }
}
