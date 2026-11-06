/* The global count test is written `1 < n`. */
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int *v108(int); };
struct E { int pad[5]; int key; int val[30]; };
struct Ctx { E e[46]; };
extern "C" { extern int DAT_004f7910[4]; extern VC *DAT_00587000[4]; extern int DAT_00587010[4]; }
extern "C" int *FUN_002f29d0(Ctx *arg0, int arg1);
int *FUN_002f29d0(Ctx *arg0, int arg1) {
    int i, j;
    if (arg1 != 0) {
        for (i = 0; i < 46; i++) {
            { int k = arg0->e[i].key; if (k == arg1) return arg0->e[i].val; }
        }
    }
    if (1 < DAT_00587010[0]) {
        for (i = DAT_00587010[0] - 1; i >= 0; i--) {
            if (DAT_00587000[i] == (VC *)arg0) break;
        }
        j = i - 1;
        if (j >= 0) {
            VC *p = DAT_00587000[j];
            if (p != (VC *)arg0) return p->v108(arg1);
        }
    }
    return &DAT_004f7910[0];
}
