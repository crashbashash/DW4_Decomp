/* Returns 1 after reporting error 0xFF000222 for the handle when FUN_002ae648(handle) fails, else
 * 0. */
int FUN_002a0bb8();
int FUN_002ae648();

int FUN_002ae608(int handle) {
    if (FUN_002ae648(handle) != 0) {
        FUN_002a0bb8(handle, 0xFF000222);
        return 1;
    }
    return 0;
}
