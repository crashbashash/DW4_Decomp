/* When a source is given, reads four values through getter callbacks via FUN_002a08c0. */
extern int FUN_002b2600(void *handle, void *source, int *value);
extern int FUN_002b2670(void *handle, void *source, int *value);
extern int FUN_002b26f0(void *handle, void *source, int *value);
extern int FUN_002b2760(void *handle, void *source, int *value);
extern int FUN_002a08c0(void *handle, void *source, int (*getter)(void *handle, void *source, int *value));

void FUN_002a0658(void *handle, void *source, int *out) {
    if (source != 0) {
        out[0] = FUN_002a08c0(handle, source, FUN_002b2600);
        out[1] = FUN_002a08c0(handle, source, FUN_002b2670);
        out[2] = FUN_002a08c0(handle, source, FUN_002b26f0);
        out[3] = FUN_002a08c0(handle, source, FUN_002b2760);
    }
}
