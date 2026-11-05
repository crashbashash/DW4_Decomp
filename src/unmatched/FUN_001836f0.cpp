#include "dw4/reflected.h"
struct V3 { float x, y, z; };
struct V4 { float x, y, z, w; };
struct A { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void v144(unsigned, void *); virtual void d35(); virtual void v152(unsigned, int); char pad[20]; igObject *f24; };
struct B { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19(); virtual void a20(); virtual void a21(); virtual void a22(); virtual void a23(); virtual void a24(); virtual void a25(); virtual void a26(); virtual void v116(unsigned, void *); virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10(); virtual void v164(unsigned, int); virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4(); virtual void c5(); virtual void c6(); virtual void c7(); virtual void c8(); virtual void c9(); virtual void c10(); virtual void v212(unsigned, float); };
extern "C" {
int FUN_0015dae0(void *, unsigned, float);
int FUN_00181840(int);
int FUN_00181850(int);
int FUN_00181860(void *, int, int, float);
int FUN_001818a0(int);
int FUN_001818b0(int);
int FUN_001820f0(int);
int FUN_00182100(int);
int FUN_00181b30(void *, int, int, int, float, float);
int FUN_00181b50(int);
int FUN_00182440(void *, int, int, int, float, float);
int FUN_001824c0(int);
int FUN_001931b0(void *, int);
int igObject_Destroy(...);
void FUN_001836f0(int arg0, unsigned arg1, int arg2, int arg3, igObject *arg4, A *arg5, float fparg0);
}
void FUN_001836f0(int arg0, unsigned arg1, int arg2, int arg3, igObject *arg4, A *arg5, float fparg0) {
    float spBC;
    V3 spB0;
    V4 spA0;
    float f20 = fparg0 * fparg0;
    unsigned i = arg1;
    unsigned end;
    if (arg5 != 0) {
        igObject *t;
        if (arg4 != 0) ++arg4->_refCount;
        t = arg5->f24;
        if (t != 0) { --t->_refCount; if ((t->_refCount & 0x7fffff) == 0) igObject_Destroy(t); }
        arg5->f24 = arg4;
        end = i + arg0;
        while (i < end) {
            int e;
            int s7;
            int s6;
            int s8;
            int s0;
            e = arg2 + i * arg3;
            s0 = FUN_001818b0(e);
            FUN_00181860(&spB0, s0, FUN_001818a0(e), fparg0);
            s7 = FUN_00182100(e);
            s6 = FUN_001820f0(e);
            FUN_00182440(&spA0, s7, s6, FUN_001824c0(e), fparg0, f20);
            s8 = FUN_00181850(e);
            FUN_00181b30(&spBC, s8, FUN_00181840(e), FUN_00181b50(e), fparg0, f20);
            arg5->v144(i, &spB0);
            arg5->v152(i, FUN_001931b0(&spA0, 1));
            FUN_0015dae0(arg5, i, spBC);
            i++;
        }
        t = arg5->f24;
        if (t != 0) { --t->_refCount; if ((t->_refCount & 0x7fffff) == 0) igObject_Destroy(t); }
        arg5->f24 = 0;
        return;
    }
    end = i + arg0;
    {
        B *b = (B *)arg4;
        while (i < end) {
            int s0;
            int e;
            int s7;
            int s8;
            int s6;
            e = arg2 + i * arg3;
            s0 = FUN_001818b0(e);
            FUN_00181860(&spB0, s0, FUN_001818a0(e), fparg0);
            s7 = FUN_00182100(e);
            s6 = FUN_001820f0(e);
            FUN_00182440(&spA0, s7, s6, FUN_001824c0(e), fparg0, f20);
            s8 = FUN_00181850(e);
            FUN_00181b30(&spBC, s8, FUN_00181840(e), FUN_00181b50(e), fparg0, f20);
            b->v116(i, &spB0);
            b->v164(i, FUN_001931b0(&spA0, 1));
            b->v212(i, spBC);
            i++;
        }
    }
}
