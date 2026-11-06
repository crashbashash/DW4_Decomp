/* Returns the value FUN_002b23f8 reports for the handle, or -1 when it fails. */
extern int FUN_002b23f8(int handle, int *out);

int FUN_00294360(int handle) {
    int value;

    if (FUN_002b23f8(handle, &value) != 0) {
        return value;
    }
    return -1;
}
