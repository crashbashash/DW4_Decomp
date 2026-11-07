int FUN_00457c40();
struct RadioButtonListView { char p[8]; int n; char q[4]; int *arr; };
struct RadioSelectionView { char p[12]; int sel; };
struct RadioGroupView { char p[8]; struct RadioSelectionView *a; char p2[4]; struct RadioButtonListView *b; int f20; int cur; };
void FUN_00457a10(struct RadioGroupView *s) {
    struct RadioButtonListView *b;
    int idx;
    int c;
    idx = s->a->sel;
    if (s->cur != idx) {
        b = s->b;
        if (idx < b->n) {
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
