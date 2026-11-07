int Memory_GetBufferSize();
struct M { char pad[8]; int f8; };
int igMemoryRefMetaField_IsAlikeShallow(struct M *arg0, int arg1, int arg2) {
    int off;
    int n;
    char *a;
    char *b;
    int i;

    off = arg0->f8;
    a = *(char **)(arg1 + off);
    b = *(char **)(arg2 + off);
    if (a == b) {
        return 1;
    }
    if (a == 0 || b == 0) {
        return 0;
    }
    n = Memory_GetBufferSize(a);
    if (n != Memory_GetBufferSize(b)) {
        return 0;
    }
    for (i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}
