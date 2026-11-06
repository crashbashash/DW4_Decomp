/* Returns 0 when a kind-6 or kind-5 request in mode 1 is refused by FUN_002b03e8 (checks 3 and 2);
 * otherwise 1. */
int FUN_002b03e8(int handle, int check);

int FUN_002adb18(int handle, int kind, int mode) {
    if (kind == 6 && mode == 1 && FUN_002b03e8(handle, 3) == 0) {
        return 0;
    }
    if (kind == 5 && mode == 1 && FUN_002b03e8(handle, 2) == 0) {
        return 0;
    }
    return 1;
}
