extern "C" {
int FUN_0016b1d0(void *, int);
int Memory_FreeBuffer(int);
void igObject_Destroy(void *);
}
struct RC { int p0; unsigned refs; };
class VO { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55();  virtual void *v58(void *, int); };
extern "C" VO *Memory_FindBufferOwner(void *);
struct E { int p0; RC *f4; int f8; int p12; int f16; int p20; };
struct T { unsigned short f0; unsigned short f2; unsigned short f4; short pad2; int f8; unsigned short *f12; E *f16;
    bool Chk(int s0) {
        int a2, a1;
        if (s0 < f0 && s0 >= 0) {
            a1 = f4;
            for (a2 = 0; a2 < a1; a2++) {
                if (s0 == f12[a2]) return false;
            }
            return true;
        }
        return false;
    }
};
struct O { int w[82]; T *f328; };
extern "C" void FUN_0016ab80(O *arg0, int arg1);
void FUN_0016ab80(O *arg0, int arg1) {
    T *t;
    E *e;
    RC *r;
    t = arg0->f328;
    if (t->Chk(arg1)) {
        e = (E *)((char *)t->f16 + arg1 * 24);
        if (e->f8 != 0) {
            FUN_0016b1d0(arg0, arg1);
        }
        r = e->f4;
        if (r != 0) {
            --r->refs;
            if (!(r->refs & 0x7fffff)) igObject_Destroy(r);
        }
        e->f4 = 0;
        if (e->f16 != 0) {
            Memory_FreeBuffer(e->f16);
        }
        t = arg0->f328;
        if (arg1 < t->f0 && arg1 >= 0) {
            if (t->f4 >= t->f2) {
                VO *ow = Memory_FindBufferOwner(t);
                t->f2 = t->f2 + 8;
                t->f12 = (unsigned short *)ow->v58(t->f12, t->f2 * 2);
            }
            t->f12[t->f4] = arg1;
            t->f4 = t->f4 + 1;
        }
    }
}
