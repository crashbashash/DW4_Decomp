struct Rc { int w0; int refs; };
extern "C" {
void *FUN_0014bff0(...);
int igObject_Destroy(...);
int igObject_GetAllocator(void *);
int FUN_0013d030(void *, int);
void Gap__Core__igGeometryAttr1_5__vfunc_40(void *, int, int);
extern int DAT_0055f170[4];
}
class X { public:
virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void grow(unsigned, int, int);
virtual void e0(); virtual void e1(); virtual void setAt(int, int);
};
struct Y { char pad[12]; unsigned f12; };
struct Cnt { char pad[8]; int n; };
class S { public:
    char pad[32];
    Cnt *f32;
    char pad2[12];
    Rc *f48;
};
#define REL(pp) if (*(pp) != 0) { (*(pp))->refs = (*(pp))->refs - 1; if (((unsigned long long)(long long)(*(pp))->refs & 0x7fffffULL) == 0) igObject_Destroy(*(pp)); }
extern "C" void FUN_0013d180(S *arg0, int arg1) {
    Rc *sp3C;
    Rc *s0;
    Rc *old;
    int i;
    if (DAT_0055f170[0] == arg1 && arg0->f32 != 0) {
        old = arg0->f48;
        if (old != 0) {
            old->refs = old->refs - 1;
            if (((unsigned long long)(long long)old->refs & 0x7fffffULL) == 0) igObject_Destroy(old);
        }
        *(Rc *volatile *)&sp3C = (Rc *)FUN_0014bff0(igObject_GetAllocator(arg0));
        s0 = *(Rc *volatile *)&sp3C;
        if (s0 != 0) s0->refs = s0->refs + 1;
        old = arg0->f48;
        if (old != 0) {
            old->refs = old->refs - 1;
            if (((unsigned long long)(long long)old->refs & 0x7fffffULL) == 0) igObject_Destroy(old);
        }
        arg0->f48 = s0;
        REL(&sp3C)
        X *x = (X *)arg0->f48;
        x->grow(arg0->f32->n, 32, 0);
        for (i = 0; i < arg0->f32->n; i++) {
            Gap__Core__igGeometryAttr1_5__vfunc_40(arg0, i, FUN_0013d030(arg0, i));
        }
    }
}
