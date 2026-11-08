extern "C" int FUN_00305000(...);
extern "C" int igObject_Destroy(...);
struct PairCallStatus { int w; };
struct PairCountedObject { int vt; int f4; };
struct PairCountedRef { int vt; int f4; };
class PairSourceView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual PairCallStatus m104(int, int); };
class PairQueryTarget { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual PairCallStatus m96(PairCountedObject *); };
class PairQueryHost { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual PairQueryTarget *m92(); };
class PairOwnerView { public: char pad[28]; unsigned char f28; char p29[3]; PairSourceView *f32; PairCountedObject *f36; };
extern PairQueryHost *DAT_005871d0[4];
extern "C" void FUN_00308e00(PairOwnerView *arg0) {
    PairCallStatus sp3C, sp38;
    PairCountedObject *q;
    PairSourceView *x;
    if (arg0->f28 != 0) {
        arg0->f28 = 0;
        sp3C = arg0->f32->m104(0, 1);
        PairQueryTarget *z;
        q = arg0->f36;
        z = DAT_005871d0[0]->m92();
        sp38 = z->m96(q);
        FUN_00305000(arg0->f32);
        x = arg0->f32;
        if (x != 0) {
            ((PairCountedRef *)x)->f4 = ((PairCountedRef *)x)->f4 - 1;
            if (((unsigned long long) ((long long) ((PairCountedRef *)x)->f4 << 0x29) >> 0x29) == 0) igObject_Destroy(x);
        }
        arg0->f32 = 0;
        q = arg0->f36;
        if (q != 0) {
            q->f4 = q->f4 - 1;
            if (((unsigned long long) ((long long) q->f4 << 0x29) >> 0x29) == 0) igObject_Destroy(q);
        }
        arg0->f36 = 0;
    }
}
