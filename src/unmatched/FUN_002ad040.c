/* If FUN_002b03e8(handle, 3) and FUN_002adc40(handle, 6) both succeed, reports 1 through *status
 * and returns whether *flag is clear; otherwise reports 0. */
int FUN_002adc40();
int FUN_002b03e8();

int FUN_002ad040(int handle, int *flag, int *status) {
    int result;

    if (FUN_002b03e8(handle, 3) != 0) {
        result = FUN_002adc40(handle, 6);
        if (result == 1) {
            *status = result;
            return *flag == 0;
        }
    }
    *status = 0;
    return 0;
}
