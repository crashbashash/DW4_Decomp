struct Vec2 { float x; float y; Vec2() {} Vec2(const Vec2 &o) { x = o.x; y = o.y; } };
class B { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int v116(unsigned, int *); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual int v144(unsigned, int *); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual int v220(unsigned, Vec2);
 int f4; char pad8[16]; B *f24; };
extern "C" {
int FUN_00181840(int);
int FUN_00181850(int);
int FUN_001818a0(int);
int FUN_001818b0(int);
int FUN_00181b50(int);
int FUN_00181df0(Vec2 *, int, int, int, float, float);
int FUN_00183f60(int *, int, int, int, float, float);
int FUN_00183fc0(int);
int FUN_0015db00(B *, unsigned, Vec2);
int igObject_Destroy(...);
/* matching construct: a small sweep of spellings */
void FUN_00184770(int arg0, unsigned arg1, int arg2, int arg3, B *arg4, B *arg5, float fparg0);
}
extern "C" void FUN_00184770(int arg0, unsigned arg1, int arg2, int arg3, B *arg4, B *arg5, float fparg0) {
    int spC0[3];
    Vec2 spB8;
    float sq;
    B *t;
    B *t2;
    unsigned end;
    int p;
    int a;
    int b;
    int p2;
    unsigned end2;

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
            FUN_00183f60(spC0, a, b, FUN_00183fc0(p), fparg0, sq);
            a = FUN_00181850(p);
            b = FUN_00181840(p);
            FUN_00181df0(&spB8, a, b, FUN_00181b50(p), fparg0, sq);
            arg5->v144(arg1, spC0);
            FUN_0015db00(arg5, arg1, spB8);
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
            a = FUN_001818b0(p2);
            b = FUN_001818a0(p2);
            FUN_00183f60(spC0, a, b, FUN_00183fc0(p2), fparg0, sq);
            a = FUN_00181850(p2);
            b = FUN_00181840(p2);
            FUN_00181df0(&spB8, a, b, FUN_00181b50(p2), fparg0, sq);
            arg4->v116(arg1, spC0);
            arg4->v220(arg1, spB8);
        }
    }
}
