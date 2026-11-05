int List_RemoveWordAt();
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
typedef struct { char pad[8]; int n; char pad2[4]; int *d; } L;
typedef struct { char pad[16]; L *volatile f10; } T;
int Gap__Core__igObject__vfunc_32(T *arg0, int arg1) {
    volatile int spC;
    L *l;
    int key;
    int n;
    int i;
    int r;
    int var_v1;
    int var_v0;

    if (arg0->f10 != 0) {
        spC = arg1;
        l = arg0->f10;
        key = spC;
        n = l->n;
        for (i = 0; i < n; i++) { if (key == l->d[i]) { r = i; goto found; } }
        r = -1;
found:
        if (r >= 0) {
            List_RemoveWordAt(l, r, key, n);
            var_v1 = DAT_004fb410[0];
        } else {
            var_v1 = DAT_004fb418[0];
        }
        return var_v1 == DAT_004fb410[0];
    }
    return 0;
}
