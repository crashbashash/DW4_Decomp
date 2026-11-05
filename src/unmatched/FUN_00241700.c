int FUN_002413f0();
struct N { char pad[28]; int v; char pad2[24]; struct N *next; };
int FUN_00241700(struct N *arg0) {
    struct N *p;
    int r;
    for (p = arg0; p != 0; p = p->next) {
        r = FUN_002413f0(p->v);
        if (r != 0) return r;
    }
    return 0;
}
