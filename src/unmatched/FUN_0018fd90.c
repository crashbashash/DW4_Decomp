struct G { char pad[8]; int count; char pad2[4]; int *data; };
struct A { char pad[8]; int idx; };
extern struct G *DAT_00561140[4];
void FUN_0018fd90(struct A *arg0, int arg1) {
    struct G *g = DAT_00561140[0];
    int n = g->count;
    int idx = arg0->idx;
    if (n != 0 && idx >= 0 && idx < n) {
        g->data[idx] = arg1;
    }
}
