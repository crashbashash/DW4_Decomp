/* Returns the value FUN_002b2250 reports for the handle, or -1 when it fails. */
extern int FUN_002b2250(int handle, int *out);

int FUN_00294598(int handle) {
    int value;

    if (FUN_002b2250(handle, &value) != 0) {
        return value;
    }
    return -1;
}
