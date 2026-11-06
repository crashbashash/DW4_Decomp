/* Geometry attribute resize helper: volatile flag word read back from memory, buffer virtual calls
 * (slots 100, 140, 240), per-element loop on a copy of the counter; alternate compiler -O4. */
class VB { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int *v100(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void v140(int, int *); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void v240(int *, int, int, int); };
struct B : VB { int f4; int f8; int f12; int f16; int f20; };
struct A { int p[3]; B *buf; };
struct R { int p[2]; unsigned cnt; int pp; int *arr; };
extern "C" { extern int DAT_004fb410[4]; extern int DAT_004fb418[4]; }
extern "C" void Gap__Core__igGeometryAttr1_5__vfunc_38(int *arg0, A *arg1, R *arg2);
void Gap__Core__igGeometryAttr1_5__vfunc_38(int *arg0, A *arg1, R *arg2) {
    volatile int sp6C;
    unsigned int s0;
    unsigned int s1;
    B *b = arg1->buf;
    s1 = arg2->cnt;
    if (b->f12 < s1) {
        *arg0 = DAT_004fb418[0];
        return;
    }
    sp6C = *b->v100();
    s0 = 0;
    if (!(sp6C & 0x400000)) {
        sp6C = sp6C | 0x400000;
        b = arg1->buf;
        b->v240((int *)&sp6C, b->f12, b->f20, 0);
        ;
    }
    { int i = s0; for (; i < s1; i++) { b = arg1->buf; b->v140(i, arg2->arr + i * 3); } }
    *arg0 = DAT_004fb410[0];
}
