int FUN_00457c40();
struct B { char p[8]; int n; char q[4]; int *arr; };
struct A { char p[12]; int sel; };
struct S { char p[8]; struct A *a; char p2[4]; struct B *b; int f20; int cur; };
void FUN_00457a10(struct S *s) {
    int idx = s->a->sel;
    if (s->cur != idx) {
        struct B *b = s->b;
        if (idx < b->n) {
            int c;
            if (idx >= 0) {
                FUN_00457c40(b->arr[idx], 1);
            }
            c = s->cur;
            if (c >= 0) {
                FUN_00457c40(s->b->arr[c], 0);
            }
            s->cur = s->a->sel;
        }
    }
}
