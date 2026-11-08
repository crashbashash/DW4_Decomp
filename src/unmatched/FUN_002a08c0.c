int FUN_002a08c0(int handle, unsigned char key, int (*lookup)(int, int, int *)) {
    int value;

    if (lookup(handle, key, &value) == 0) {
        return -1;
    }
    return value;
}
