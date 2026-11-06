/* Returns the value FUN_002b2200 reports for the handle, or -1 when it fails. */
extern int FUN_002b2200(int handle, int *out);

int FUN_00294568(int handle) {
    int value;

    if (FUN_002b2200(handle, &value) != 0) {
        return value;
    }
    return -1;
}
