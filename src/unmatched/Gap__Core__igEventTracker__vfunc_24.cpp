/* The busy flag is read through a volatile access into a boolean local; the spellings `0 <= cap`
 * and `!(0 < cnt)` give the slt at / slt v0 forms. */
extern "C" {
int FUN_002d3950(int);
int FUN_002dcaa0(void *, int);
int FUN_002eb150(int);
int FUN_0030cfa0(int);
int List_Reserve(...);
int List_Resize(...);
}
class VT { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vA(); };
struct L { int a0, a4, cnt, cap; };
struct E { int vt, a4, a8, flags; char p[36]; int f52, f56, f60, f64, f68, f72, f76; L *f80; int f84, f88; VT *f92; };
extern "C" {
void Gap__Core__igEventTracker__vfunc_24(E *arg0) {
    int busy = (*(volatile int *)&arg0->flags & 2) != 0;
    if (!busy) {
        arg0->flags = arg0->flags | 2;
        FUN_0030cfa0(arg0->f52);
        FUN_0030cfa0(arg0->f56);
        FUN_0030cfa0(arg0->f68);
        FUN_0030cfa0(arg0->f64);
        FUN_0030cfa0(arg0->f68);
        FUN_002d3950(arg0->f72);
        if (arg0->f92->vA() != 0) {
            FUN_002eb150(arg0->f76);
        }
        if (0 <= arg0->f80->cap) {
            arg0->f80->cnt = 0;
        } else {
            List_Resize(arg0->f80, 0, 1);
        }
        if (!(0 < arg0->f80->cnt)) {
            List_Reserve(arg0->f80, 0, 1);
        }
        FUN_002dcaa0(arg0, 0);
        arg0->flags = arg0->flags & ~2;
    }
}
}
