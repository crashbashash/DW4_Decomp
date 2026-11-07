extern "C" {
int memset(...);
int FUN_00170210(...);
int thunk_FUN_002ed3b0(...);
}
class O { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55();  virtual int vX(int, int); };
struct Pool { unsigned short f0; unsigned short f2; unsigned short f4; short pad6; int pad8; short *f12; char *f16; };
struct It { char pad[124]; int f124; char pad2[24]; int f152; };
struct Obj { char pad[1336]; Pool *f1336; };
extern "C" O *Memory_FindBufferOwner(Pool *);
extern "C" unsigned short Gap__Gfx__igPsx2VisualContext__vfunc_77(Obj *arg0, int arg1) {
    Pool *p;
    int i;
    unsigned short idx;
    It *it;
    int v;
    p = arg0->f1336;
    if (p->f4 <= 0) {
        p->f16 = (char *)thunk_FUN_002ed3b0(p->f16, (p->f0 + 4) * 0xA0, 0x10);
        memset(p->f16 + p->f0 * 0xA0, 0, 0x280);
        if (p->f2 < 4) {
            O *o = Memory_FindBufferOwner(p);
            p->f12 = (short *)o->vX((int)p->f12, 8);
            p->f2 = 4;
        }
        i = 0;
        do {
            p->f12[i] = p->f0 + i;
            i++;
        } while (i < 4);
        p->f4 = 4;
        p->f0 = p->f0 + 4;
    }
    idx = p->f12[p->f4 - 1];
    p->f4 = p->f4 - 1;
    it = (It *)(arg0->f1336->f16 + idx * 0xA0);
    FUN_00170210(it);
    it->f152 = arg1;
    switch (arg1) {
    case 0:
        it->f124 = 0;
        break;
    case 1:
        it->f124 = 1;
        break;
    case 2:
        it->f124 = 2;
        break;
    }
    return idx;
}
