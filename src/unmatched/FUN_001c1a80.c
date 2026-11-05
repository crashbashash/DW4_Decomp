/* 0x001c1a80 - FUN_001c1a80. Finds (or appends through FUN_001c17e0, whose arguments pass straight through) an item in the list at +12, then calls FUN_001c1950 with the entry of the list at +8; inline index search template (early goto found), declaration order i,r,l,n; alternate compiler -O3. */
typedef struct L { char p0[8]; int n; int p1; int *d; } L;
typedef struct T { char p0[8]; L *f8; L *f12; } T;
int FUN_001c17e0(T *, int);
int FUN_001c1950(T *, int, int, int);
void FUN_001c1a80(T *arg0, int arg1, int arg2) {
    int i;
    int r;
    L *l;
    int n;
    FUN_001c17e0(arg0, arg1);
    l = arg0->f12;
    n = l->n;
    for (i = 0; i < n; i++) { if (arg1 == l->d[i]) { r = i; goto found; } }
    r = -1;
found:
    if (r == -1) {
        FUN_001c17e0(arg0, arg1);
        r = arg0->f8->n - 1;
    }
    FUN_001c1950(arg0, arg0->f8->d[r], arg1, arg2);
}
