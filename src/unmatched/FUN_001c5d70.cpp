extern "C" {
int FUN_001d32f0(...);
int List_InsertWords(...);
}
class O { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int vX(void *); int f4; char pad[12]; int f20; };
struct T { char pad[28]; int f28; };
struct R { O *p; };
extern "C" int FUN_001c5d70(T *self, int a1, O *a2) {
    if (a2 == 0) return 0;
    if (a2->vX(self) != 0) {
        R r;
        int f;
        r.p = a2;
        f = self->f28;
        if (r.p != 0) r.p->f4 = r.p->f4 + 1;
        List_InsertWords(f, a1, 1, &r);
        FUN_001d32f0(self, a2->f20);
        return 1;
    } else {
        return 0;
    }
}
