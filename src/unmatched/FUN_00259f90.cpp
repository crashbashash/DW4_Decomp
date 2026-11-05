extern "C" {
int igObject_Destroy(struct R *);
struct R { int w0; int rc; };
struct A { char pad[36]; struct R *f36; struct R *f40; };
void FUN_00259f90(struct A *arg0, struct R *arg1, struct R *arg2) {
    struct R *t;
    struct R *u;
    if (arg1 != 0) {
        arg1->rc = arg1->rc + 1;
    }
    t = arg0->f40;
    if (t != 0) {
        t->rc = t->rc - 1;
        if ((t->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(t);
        }
    }
    arg0->f40 = arg1;
    if (arg2 != 0) {
        arg2->rc = arg2->rc + 1;
    }
    u = arg0->f36;
    if (u != 0) {
        u->rc = u->rc - 1;
        if ((u->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(u);
        }
    }
    arg0->f36 = arg2;
}
}
