int Memory_FreeBuffer();
int igObject_Destroy();
struct R { int w0; int rc; };
struct Lst { int w0; int w4; int n; int w12; int *items; };
struct O { char pad[48]; struct Lst *f48; struct Lst *f52; struct R *f56; };
void FUN_0017d2b0(struct O *arg0) {
    int var_s0;
    struct R *t;

    t = arg0->f56;
    if (t != 0) {
        t->rc = t->rc - 1;
        if ((t->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(t);
        }
    }
    arg0->f56 = 0;
    var_s0 = 0;
    if (arg0->f48 != 0) {
        while (var_s0 < arg0->f48->n) {
            Memory_FreeBuffer(arg0->f48->items[var_s0]);
            var_s0 += 1;
        }
    }
    var_s0 = 0;
    if (arg0->f52 != 0) {
        while (var_s0 < arg0->f52->n) {
            Memory_FreeBuffer(arg0->f52->items[var_s0]);
            var_s0 += 1;
        }
    }
    t = (struct R *)arg0->f48;
    if (t != 0) {
        t->rc = t->rc - 1;
        if ((t->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(t);
        }
    }
    arg0->f48 = 0;
    t = (struct R *)arg0->f52;
    if (t != 0) {
        t->rc = t->rc - 1;
        if ((t->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(t);
        }
    }
    arg0->f52 = 0;
}
