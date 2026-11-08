typedef int (*Fn)(void *h, int, int, int);
typedef struct { char pad[12]; Fn *fns; char pad2[52]; } Slot;
int FUN_002b02a0(char *h, int k) {
    int i;
    int r = 0;
    Slot *s = (Slot *)(h + 7976);
    for (i = 0; i < 9; i++) {
        Fn *t = (s++)->fns;
        if (t == 0) continue;
        r = t[k](h, 0, 0, 0);
        if (r != 0) break;
    }
    return r;
}
