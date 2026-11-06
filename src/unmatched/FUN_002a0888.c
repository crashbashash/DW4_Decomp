/* Runs a getter callback and returns the value it produced, or -1 when it fails. */
typedef int (*SfdGetter)(void *handle, int *value);

int FUN_002a0888(void *handle, SfdGetter getter) {
    int value[4];

    if (getter(handle, value) != 0) {
        return value[0];
    }
    return -1;
}
