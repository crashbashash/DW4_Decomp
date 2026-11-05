class VM { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void* v232(void*,int); };
struct Rc { int w0; unsigned refs; int count; int cap; int *data; };
struct Ent { Rc *list; };
extern "C" {
int FUN_001eeda0(int);
VM *Memory_FindBufferOwner(void *);
int FUN_002ed5c0(void *);
int igObject_Destroy(void *);
}
struct T { unsigned short f0; unsigned short f2; unsigned short f4; short pad; int pad8; unsigned short *f12; Ent **f16;
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
    void Add(int s0) {
        if (s0 < f0 && s0 >= 0) {
            if (f4 >= f2) {
                VM *o = Memory_FindBufferOwner(this);
                f2 = f2 + 8;
                f12 = (unsigned short *)o->v232(f12, f2 * 2);
            }
            f12[f4] = s0;
            f4 = f4 + 1;
        }
    }
};
struct O { int w[240]; T *f960; };
extern "C" void FUN_0016c8f0(O *arg0, int arg1);
void FUN_0016c8f0(O *arg0, int arg1) {
    T *a3;
    int s0;
    Rc *s2;
    int s1;
    bool ok;
    int a2, a1;
    a3 = arg0->f960;
    if (arg1 < a3->f0) {
        ok = false;
        if (arg1 >= 0) {
            a1 = a3->f4;
            for (a2 = 0; a2 < a1; a2++) {
                if (arg1 == a3->f12[a2]) {
                    ok = false;
                    goto done;
                }
            }
            ok = true;
        }
    } else {
        ok = false;
    }
done:
    if (ok & 0xFF) {
        s0 = arg1 * 4;
        s2 = a3->f16[arg1]->list;
        for (s1 = 0; s1 < s2->count; s1++) {
            FUN_001eeda0(s2->data[s1]);
        }
        --s2->refs;
        if ((s2->refs & 0x7fffff) == 0) {
            igObject_Destroy(s2);
        }
        FUN_002ed5c0(arg0->f960->f16[arg1]);
        arg0->f960->Add(arg1);
    }
}
