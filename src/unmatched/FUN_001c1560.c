typedef struct L { char p0[8]; int n; int p1; int *d; } L;
typedef struct O { char p0[8]; int c; int p1; int *d; } O;
typedef struct T { char p0[8]; L *f8; L *f12; L *f16; } T;
int FUN_001c17e0(T *, int);
int FUN_001c1a80(T *, int, int);
int FUN_001c1560(T *arg0, int arg1) {
    int i;
    int r;
    L *l;
    int n;
    int s1, nv;
    L *q;
    int v;
    l = arg0->f12;
    n = l->n;
    for (i = 0; i < n; i++) { if (arg1 == l->d[i]) { r = i; goto found; } }
    r = -1;
found:
    if (r == -1) {
        FUN_001c17e0(arg0, arg1);
        r = arg0->f8->n - 1;
    }
    s1 = arg0->f16->d[r];
    if (s1 >= ((O *)arg0->f8->d[r])->c) {
        FUN_001c1a80(arg0, arg1, ((O *)arg0->f8->d[r])->c + 1);
    }
    v = ((int *)((L *)arg0->f8->d[r])->d)[s1];
    nv = s1 + 1;
    q = arg0->f16;
    if (q->n != 0 && r >= 0 && r < q->n) q->d[r] = nv;
    return v;
}
