/* Probes FUN_0029f918 at offsets 0, 2, 1 and 3 and reports whether any probe succeeds. */
extern int FUN_0029f918(unsigned char *data, int size, int arg);

int FUN_0029f880(unsigned char *data, int size, int arg) {
    if (FUN_0029f918(data, size, arg) != 0) {
        return 1;
    }
    if (FUN_0029f918(data + 2, size - 2, arg) != 0) {
        return 1;
    }
    if (FUN_0029f918(data + 1, size - 1, arg) != 0) {
        return 1;
    }
    return FUN_0029f918(data + 3, size - 3, arg) != 0;
}
