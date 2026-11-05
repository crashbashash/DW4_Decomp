int igObject_Destroy();
struct R { int w0; int rc; };
struct R *igMetaObject_CreateInstance();
int FUN_002fd6e0(struct R **arg0, int arg1, int arg2) {
    struct R * volatile sp2C;
    struct R *q;
    struct R *t;
    sp2C = igMetaObject_CreateInstance(arg1, arg2);
    t = sp2C;
    if (t != 0) {
        t->rc = t->rc + 1;
    }
    t = sp2C;
    if (t != 0) {
        t->rc = t->rc - 1;
        if ((t->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(t);
        }
    }
    *arg0 = sp2C;
    q = *arg0;
    if (q != 0) {
        q->rc = q->rc + 1;
    }
    t = sp2C;
    if (t != 0) {
        t->rc = t->rc - 1;
        if ((t->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(t);
        }
    }
    return 0;
}
