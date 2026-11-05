struct G18fd50 { char pad[8]; int n; char pad2[4]; int *data; };
extern struct G18fd50 *DAT_00561138[4];
struct A18fd50 { char pad[8]; int idx; };
void FUN_0018fd50(struct A18fd50 *arg0, int arg1) {
    struct G18fd50 *g = DAT_00561138[0];
    int n = g->n;
    int i = arg0->idx;
    if ((n != 0) && (i >= 0) && (i < n)) {
        g->data[i] = arg1;
    }
}
