struct TexCoordPair { float a, b; };
class VertexSink { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int v116(unsigned, float *); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual int v144(unsigned, float *); virtual void d35(); virtual int v152(unsigned, int); virtual void d37(); virtual void d38(); virtual int v164(unsigned, int); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual int v212(unsigned, float); virtual void d52(); virtual int v220(unsigned, TexCoordPair *);
 int f4; char pad8[16]; VertexSink *f24; };
extern "C" {
int FUN_0015db00(VertexSink *, unsigned, TexCoordPair *);
int FUN_00181840(int);
int FUN_00181850(int);
void FUN_00181810(TexCoordPair *, int, int, float);
int FUN_001818a0(int);
int FUN_001818b0(int);
int FUN_001820f0(int);
int FUN_00182100(int);
int FUN_001824c0(int);
int FUN_00183fc0(int);
void FUN_00183f60(float *, int, int, int, float, float);
void FUN_00182440(float *, int, int, int, float, float);
int FUN_001931b0(float *, int);
int igObject_Destroy(...);
void FUN_00185fb0(int arg0, unsigned arg1, int arg2, int arg3, VertexSink *arg4, VertexSink *arg5, float fparg0);
}
extern "C" void FUN_00185fb0(int arg0, unsigned arg1, int arg2, int arg3, VertexSink *arg4, VertexSink *arg5, float fparg0) {
    VertexSink *t;
    VertexSink *t2;
    float temp_f20;
    float spD0[3];
    int i2;
    TexCoordPair spC8;
    float spA0[4];
    TexCoordPair spC0;
    unsigned end;
    int i1;
    int b2;
    int b1;
    int f1;
    int c1;
    int c2;
    int f2;
    int d1;
    int e1;
    TexCoordPair spB8;
    int d2;
    int e2;
    unsigned end2;

    temp_f20 = fparg0 * fparg0;
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
            i1 = arg2 + arg1 * arg3;
            b1 = FUN_001818b0(i1);
            c1 = FUN_001818a0(i1);
            FUN_00183f60(spD0, b1, c1, FUN_00183fc0(i1), fparg0, temp_f20);
            d1 = FUN_00182100(i1);
            e1 = FUN_001820f0(i1);
            FUN_00182440(spA0, d1, e1, FUN_001824c0(i1), fparg0, temp_f20);
            f1 = FUN_00181850(i1);
            FUN_00181810(&spC8, f1, FUN_00181840(i1), fparg0);
            arg5->v144(arg1, spD0);
            arg5->v152(arg1, FUN_001931b0(spA0, 1));
            spC0 = spC8;
            FUN_0015db00(arg5, arg1, &spC0);
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
            i2 = arg2 + arg1 * arg3;
            b2 = FUN_001818b0(i2);
            c2 = FUN_001818a0(i2);
            FUN_00183f60(spD0, b2, c2, FUN_00183fc0(i2), fparg0, temp_f20);
            d2 = FUN_00182100(i2);
            e2 = FUN_001820f0(i2);
            FUN_00182440(spA0, d2, e2, FUN_001824c0(i2), fparg0, temp_f20);
            f2 = FUN_00181850(i2);
            FUN_00181810(&spC8, f2, FUN_00181840(i2), fparg0);
            arg4->v116(arg1, spD0);
            arg4->v164(arg1, FUN_001931b0(spA0, 1));
            spB8 = spC8;
            arg4->v220(arg1, &spB8);
        }
    }
}
