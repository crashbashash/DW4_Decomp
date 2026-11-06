struct Rc { int w0; int refs; };
extern "C" {
void *FUN_0014bff0(...);
int igObject_Destroy(...);
int igObject_GetAllocator();
}
class X { public:
virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void grow(unsigned, int, int);
virtual void e0(); virtual void e1(); virtual void setAt(int, int);
};
struct Y { char pad[12]; unsigned f12; };
class S { public:
    char pad[48];
    Rc *f48;
};
#define REL(pp) if (*(pp) != 0) { (*(pp))->refs = (*(pp))->refs - 1; if (((unsigned long long)(long long)(*(pp))->refs & 0x7fffffULL) == 0) igObject_Destroy(*(pp)); }
extern "C" void Gap__Attrs__igGeometryAttr1_5__vfunc_40(S *arg0, int arg1, int arg2) {
    Rc *sp5C;
    Rc *s0;
    Rc *old;
    if (arg0->f48 == 0) {
        *(Rc *volatile *)&sp5C = (Rc *)FUN_0014bff0(igObject_GetAllocator());
        s0 = *(Rc *volatile *)&sp5C;
        if (s0 != 0) s0->refs = s0->refs + 1;
        old = arg0->f48;
        if (old != 0) {
            old->refs = old->refs - 1;
            if (((unsigned long long)(long long)old->refs & 0x7fffffULL) == 0) igObject_Destroy(old);
        }
        arg0->f48 = s0;
        REL(&sp5C)
    }
    X *x = (X *)arg0->f48;
    unsigned n = arg1 + 1;
    if (((Y *)x)->f12 < n) x->grow(n, 32, 0);
    x = (X *)arg0->f48;
    x->setAt(arg1, arg2);
}
