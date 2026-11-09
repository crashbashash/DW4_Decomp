struct Vec2 { float x; float y; Vec2() {} Vec2(const Vec2 &o) { x = o.x; y = o.y; } };
class B { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int v116(unsigned, int *); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual int v144(unsigned, int *); virtual void d35(); virtual int v152(unsigned, int); virtual void d37(); virtual void d38(); virtual int v164(unsigned, int); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual int v220(unsigned, Vec2);
 int f4; char pad8[16]; B *f24; };
extern "C" {
int FUN_00181840(int);
int FUN_00181850(int);
int FUN_001818a0(int);
int FUN_001818b0(int);
int FUN_00181810(Vec2 *, int, int, float);
int FUN_00181860(int *, int, int, float);
int FUN_001820f0(int);
int FUN_00182100(int);
int FUN_00182440(int *, int, int, int, float, float);
int FUN_001824c0(int);
int FUN_001931b0(int *, int);
int FUN_0015db00(B *, unsigned, Vec2);
int igObject_Destroy(...);
/* matching construct: a small sweep of spellings */
void FUN_001824d0(int arg0, unsigned arg1, int arg2, int arg3, B *arg4, B *arg5, float fparg0);
}
extern "C" void FUN_001824d0(int arg0, unsigned arg1, int arg2, int arg3, B *arg4, B *arg5, float fparg0) {
    int spD0[3];
    Vec2 spC8;
    int spA0[4];
    float sq;
    B *t;
    B *t2;
    unsigned end;
    int p;
    int a;
    int b;
    int p2;
    unsigned end2;
    int a2;
    int b2;

    sq = fparg0 * fparg0;
    if (arg5 != 0) {
        if (arg4 != 0) {
            arg4->f4 = arg4->f4 + 1;
        }
        t = arg5->f24;
        if (t != 0) {
            t->f4 = t->f4 - 1;
            if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
        arg5->f24 = arg4;
        end = arg1 + arg0;
        for (; arg1 < end; arg1++) {
            p = arg2 + arg1 * arg3;
            a = FUN_001818b0(p);
            b = FUN_001818a0(p);
            FUN_00181860(spD0, a, b, fparg0);
            a = FUN_00182100(p);
            b = FUN_001820f0(p);
            FUN_00182440(spA0, a, b, FUN_001824c0(p), fparg0, sq);
            a = FUN_00181850(p);
            b = FUN_00181840(p);
            FUN_00181810(&spC8, a, b, fparg0);
            arg5->v144(arg1, spD0);
            arg5->v152(arg1, FUN_001931b0(spA0, 1));
            FUN_0015db00(arg5, arg1, spC8);
        }
        t2 = arg5->f24;
        if (t2 != 0) {
            t2->f4 = t2->f4 - 1;
            if (((unsigned long long)((long long)t2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t2);
            }
        }
        arg5->f24 = 0;
    } else {
        end2 = arg1 + arg0;
        for (; arg1 < end2; arg1++) {
            p2 = arg2 + arg1 * arg3;
            a2 = FUN_001818b0(p2);
            b2 = FUN_001818a0(p2);
            FUN_00181860(spD0, a2, b2, fparg0);
            a2 = FUN_00182100(p2);
            b2 = FUN_001820f0(p2);
            FUN_00182440(spA0, a2, b2, FUN_001824c0(p2), fparg0, sq);
            a2 = FUN_00181850(p2);
            b2 = FUN_00181840(p2);
            FUN_00181810(&spC8, a2, b2, fparg0);
            arg4->v116(arg1, spD0);
            arg4->v164(arg1, FUN_001931b0(spA0, 1));
            arg4->v220(arg1, spC8);
        }
    }
}
