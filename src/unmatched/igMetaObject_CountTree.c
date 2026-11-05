/* 0x002fe3d0 - igMetaObject_CountTree. Recursive tree count; sum declared before the bound; alternate compiler. Verified byte-identical by tools/verify.py. */
struct M;
struct L { char p[8]; struct M **arr; int n; };
struct M { char p[44]; int f44; char q[4]; struct L *f52; };
int igMetaObject_CountTree(struct M *arg0) {
    struct L *l = arg0->f52;
    int s2;
    int s1;
    int s0;
    if (l == 0) return 1;
    s1 = l->n;
    s2 = 1;
    for (s0 = 0; s0 < s1; s0++) {
        s2 += igMetaObject_CountTree(arg0->f52->arr[s0]);
    }
    return s2;
}
