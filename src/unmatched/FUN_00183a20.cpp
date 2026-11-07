struct MeshVec2 { float x, y; };
struct MeshVec3 { float x, y, z; };
class MeshTarget { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int v116(unsigned, MeshVec3 *); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual int v144(unsigned, MeshVec3 *); virtual void d35(); virtual int v152(unsigned, int); virtual void d37(); virtual void d38(); virtual int v164(unsigned, int); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual int v220(unsigned, MeshVec2 *);
 int f4; char pad8[16]; MeshTarget *f24; };
extern "C" {
int FUN_0015db00(void *, unsigned, MeshVec2 *);
int FUN_00181840(int);
int FUN_00181850(int);
int FUN_00181860(void *, int, int, float);
int FUN_001818a0(int);
int FUN_001818b0(int);
int FUN_00181b50(int);
int FUN_00181df0(void *, int, int, int, float, float);
int FUN_00182100(int);
int FUN_001820f0(int);
int FUN_00182440(void *, int, int, int, float, float);
int FUN_001824c0(int);
int FUN_001931b0(void *, int);
int igObject_Destroy(...);
void FUN_00183a20(int arg0, unsigned arg1, int arg2, int arg3, MeshTarget *arg4, MeshTarget *arg5, float fparg0);
}
struct MeshVec4 { float x, y, z, w; };
extern "C" void FUN_00183a20(int arg0, unsigned arg1, int arg2, int arg3, MeshTarget *arg4, MeshTarget *arg5, float fparg0) {
    MeshVec3 spD0;
    MeshVec2 spC8;
    MeshVec2 spC0;
    MeshVec2 spB8;
    MeshVec4 spA0;
    float temp_f20;
    unsigned end;
    MeshTarget *t;
    int e;
    int p, r;
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
            e = arg2 + arg1 * arg3;
            FUN_00181860(&spD0, FUN_001818b0(e), FUN_001818a0(e), fparg0);
            FUN_00182440(&spA0, FUN_00182100(e), FUN_001820f0(e), FUN_001824c0(e), fparg0, temp_f20);
            FUN_00181df0(&spC8, FUN_00181850(e), FUN_00181840(e), FUN_00181b50(e), fparg0, temp_f20);
            arg5->v144(arg1, &spD0);
            arg5->v152(arg1, FUN_001931b0(&spA0, 1));
            spC0 = spC8;
            FUN_0015db00(arg5, arg1, &spC0);
        }
        t = arg5->f24;
        if (t != 0) {
            t->f4 = t->f4 - 1;
            if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
        arg5->f24 = 0;
    } else {
        end = arg1 + arg0;
        for (; arg1 < end; arg1++) {
            e = arg2 + arg1 * arg3;
            FUN_00181860(&spD0, FUN_001818b0(e), FUN_001818a0(e), fparg0);
            FUN_00182440(&spA0, FUN_00182100(e), FUN_001820f0(e), FUN_001824c0(e), fparg0, temp_f20);
            FUN_00181df0(&spC8, FUN_00181850(e), FUN_00181840(e), FUN_00181b50(e), fparg0, temp_f20);
            arg4->v116(arg1, &spD0);
            arg4->v164(arg1, FUN_001931b0(&spA0, 1));
            spB8 = spC8;
            arg4->v220(arg1, &spB8);
        }
    }
}
