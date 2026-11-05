extern "C" {
int igObject_Destroy(void *);
int FUN_001818b0(int);
int FUN_001818a0(int);
int FUN_00182100(int);
int FUN_001820f0(int);
void FUN_00181860(void *, int, int, float);
void FUN_00182090(void *, int, int, float);
int FUN_001931b0(void *, int);
}
struct Obj { int vt; int ref; };
class A { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int s0(unsigned, char *); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual int s1(unsigned, void *); };
class Hold { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual int s0(unsigned, char *); virtual void d35(); virtual int s1(unsigned, void *); int pad[5]; Obj *obj; };

extern "C" void FUN_00181e30(int cnt, unsigned idx, int base, int stride, A *arg4, Hold *arg5, float f) {
    char bufB[16];
    char bufA[16];
    unsigned end;
    int p, a, b;
    if (arg5 != 0) {
        Obj *old;
        if (arg4 != 0) {
            ((Obj*)arg4)->ref = ((Obj*)arg4)->ref + 1;
        }
        old = arg5->obj;
        if (old != 0) {
            old->ref = old->ref - 1;
            if (((unsigned long long)((long long)old->ref << 0x29) >> 0x29) == 0) {
                igObject_Destroy(old);
            }
        }
        arg5->obj = (Obj*)arg4;
        end = idx + cnt;
        while (idx < end) {
            p = base + idx * stride;
            FUN_00181860(bufA, FUN_001818b0(p), FUN_001818a0(p), f);
            FUN_00182090(bufB, FUN_00182100(p), FUN_001820f0(p), f);
            arg5->s0(idx, bufA);
            arg5->s1(idx, (void*)FUN_001931b0(bufB, 1));
            idx++;
        }
        old = arg5->obj;
        if (old != 0) {
            old->ref = old->ref - 1;
            if (((unsigned long long)((long long)old->ref << 0x29) >> 0x29) == 0) {
                igObject_Destroy(old);
            }
        }
        arg5->obj = 0;
        return;
    }
    end = idx + cnt;
    while (idx < end) {
        p = base + idx * stride;
        FUN_00181860(bufA, FUN_001818b0(p), FUN_001818a0(p), f);
        FUN_00182090(bufB, FUN_00182100(p), FUN_001820f0(p), f);
        arg4->s0(idx, bufA);
        arg4->s1(idx, (void*)FUN_001931b0(bufB, 1));
        idx++;
    }
}
