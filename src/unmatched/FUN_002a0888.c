/* 0x002a0888 — FUN_002a0888 (52 bytes). Runs a getter callback and returns the value it produced, or -1 when it fails. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef int (*SfdGetter)(void *handle, int *value);

int FUN_002a0888(void *handle, SfdGetter getter) {
    int value[4];

    if (getter(handle, value) != 0) {
        return value[0];
    }
    return -1;
}
