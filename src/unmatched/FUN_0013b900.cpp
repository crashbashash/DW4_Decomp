/* 0x0013b900 - FUN_0013b900. Smart-pointer result returned through a hidden pointer: the holder struct has constructors so the vcall initialises the slot directly (declared first = highest slot); volatile slot plus plain copies for the tests. Alternate -O3. */
extern "C" {
int FUN_0013ba30(...);
int FUN_0013c060();
void igObject_Destroy(void *);
int FUN_0013b900(void **arg0, void **arg1);
}
struct RO { int vt; union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } u; };
struct SR { RO *p; SR() {} SR(RO *x) { p = x; } };
class VA { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual SR vX(); };
extern "C" {
int FUN_0013b900(void **arg0, void **arg1) {
    SR sp2C = ((VA *)arg1)->vX();
    RO *sp28;
    RO *volatile sp24;
    RO *q;
    sp24 = sp2C.p;
    q = sp24;
    if (q != 0) {
        q->u.w = q->u.w + 1;
    }
    FUN_0013ba30(&sp28, FUN_0013c060(), &sp24);
    q = sp24;
    if (q != 0) {
        q->u.w = q->u.w - 1;
        q = sp24;
        if (q->u.b.cnt == 0) igObject_Destroy(q);
    }
    *arg0 = sp28;
    q = (RO *)*arg0;
    if (q != 0) {
        q->u.w = q->u.w + 1;
    }
    q = sp28;
    if (q != 0) {
        q->u.w = q->u.w - 1;
        if (q->u.b.cnt == 0) igObject_Destroy(q);
    }
    q = sp2C.p;
    if (q != 0) {
        q->u.w = q->u.w - 1;
        if (q->u.b.cnt == 0) igObject_Destroy(q);
    }
    return 0;
}
}
