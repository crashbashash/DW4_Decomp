/* Recursive count over a child array; alternate compiler. */
struct M;
struct L { char p[8]; struct M **arr; int n; };
struct M { char p[44]; int f44; char q[4]; struct L *f52; };
int igMetaObject_CountInstances(struct M *arg0, int arg1) {
    int s2 = arg0->f44;
    struct L *l;
    int s1;
    int s0;
    if (arg1 != 0) {
        l = arg0->f52;
        if (l != 0) {
            s0 = l->n;
            for (s1 = 0; s1 < s0; s1++) {
                s2 += igMetaObject_CountInstances(arg0->f52->arr[s1], 1);
            }
        }
    }
    return s2;
}
