struct TexCoordPairXY { float x, y; };
struct PackedVertexWriter { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19(); virtual void a20(); virtual void a21(); virtual void a22(); virtual void a23(); virtual void a24(); virtual void a25(); virtual void a26();  virtual void v116(unsigned, int *); virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10();  virtual void v164(unsigned, int); virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4(); virtual void c5(); virtual void c6(); virtual void c7(); virtual void c8(); virtual void c9(); virtual void c10(); virtual void c11(); virtual void c12();  virtual void v220(unsigned, TexCoordPairXY *); int refs; };
struct VertexArrayWriter { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33();  virtual void v144(unsigned, int *); virtual void d35(); virtual void v152(unsigned, int); int pad[5]; PackedVertexWriter *f24; };
extern "C" {
int FUN_0015db00(VertexArrayWriter *, unsigned, TexCoordPairXY *);
int FUN_00181840(int);
int FUN_00181850(int);
int FUN_001818a0(int);
int FUN_001818b0(int);
int FUN_00181b50(int);
int FUN_00181df0(TexCoordPairXY *, int, int, int, float, float);
int FUN_001820f0(int);
int FUN_00182100(int);
int FUN_00182440(void *, int, int, int, float, float);
int FUN_001824c0(int);
int FUN_00183f60(void *, int, int, int, float, float);
int FUN_00183fc0(int);
int FUN_001931b0(void *, int);
int igObject_Destroy(void *);
void FUN_00186660(int arg0, unsigned int arg1, int arg2, int arg3, PackedVertexWriter *arg4, VertexArrayWriter *arg5, float fparg0);
}
void FUN_00186660(int arg0, unsigned int arg1, int arg2, int arg3, PackedVertexWriter *arg4, VertexArrayWriter *arg5, float fparg0) {
    int spD0[3];
    int spA0[4];
    TexCoordPairXY spC8;
    TexCoordPairXY spC0;
    TexCoordPairXY spB8;
    float f20;
    unsigned s5;
    unsigned s7;
    int s1;
    PackedVertexWriter *o;
    s5 = arg1;
    f20 = fparg0 * fparg0;
    if (arg5 != 0) {
        if (arg4 != 0) arg4->refs = arg4->refs + 1;
        o = arg5->f24;
        if (o != 0) {
            o->refs = o->refs - 1;
            if (((unsigned long long)((long long)o->refs << 0x29) >> 0x29) == 0) igObject_Destroy(o);
        }
        arg5->f24 = arg4;
        s7 = s5 + arg0;
        while (s5 < s7) {
            s1 = arg2 + s5 * arg3;
            FUN_00183f60(spD0, FUN_001818b0(s1), FUN_001818a0(s1), FUN_00183fc0(s1), fparg0, f20);
            FUN_00182440(spA0, FUN_00182100(s1), FUN_001820f0(s1), FUN_001824c0(s1), fparg0, f20);
            FUN_00181df0(&spC8, FUN_00181850(s1), FUN_00181840(s1), FUN_00181b50(s1), fparg0, f20);
            arg5->v144(s5, spD0);
            arg5->v152(s5, FUN_001931b0(spA0, 1));
            spC0.x = spC8.x;
            spC0.y = spC8.y;
            FUN_0015db00(arg5, s5, &spC0);
            s5 += 1;
        }
        o = arg5->f24;
        if (o != 0) {
            o->refs = o->refs - 1;
            if (((unsigned long long)((long long)o->refs << 0x29) >> 0x29) == 0) igObject_Destroy(o);
        }
        arg5->f24 = 0;
        return;
    }
    s7 = s5 + arg0;
    while (s5 < s7) {
        s1 = arg2 + s5 * arg3;
        FUN_00183f60(spD0, FUN_001818b0(s1), FUN_001818a0(s1), FUN_00183fc0(s1), fparg0, f20);
        FUN_00182440(spA0, FUN_00182100(s1), FUN_001820f0(s1), FUN_001824c0(s1), fparg0, f20);
        FUN_00181df0(&spC8, FUN_00181850(s1), FUN_00181840(s1), FUN_00181b50(s1), fparg0, f20);
        arg4->v116(s5, spD0);
        arg4->v164(s5, FUN_001931b0(spA0, 1));
        spB8.x = spC8.x;
        spB8.y = spC8.y;
        arg4->v220(s5, &spB8);
        s5 += 1;
    }
}
