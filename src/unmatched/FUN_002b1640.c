extern int FUN_0029e960(void *owner, int index, int *value);
extern int FUN_002af688(void *h, int v);
int FUN_002b1640(char *h, int *out) {
    int r;
    if ((unsigned)(*(int *)(h + 72) - 3) >= 2) {
        *out = 0;
        return 0;
    }
    r = FUN_0029e960(h, *(int *)(h + 8400), out);
    if (r != 0) return r;
    r = FUN_002af688(h, *out);
    if (r == 0) {
        *out = 0;
        return r;
    }
    return 0;
}
