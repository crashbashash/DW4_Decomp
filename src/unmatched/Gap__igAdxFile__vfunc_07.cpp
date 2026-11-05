extern "C" {
int FUN_002ed2b0(...);
int Gap__Core__igObject__vfunc_07(...);
int igMetaObject_CountInstances(...);
int igObject_GetAllocator(...);
struct S;
void Gap__igAdxFile__vfunc_07(S *arg0);
}
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
struct S { char p0[48]; volatile int f48; char p1[12]; int f64; };
void Gap__igAdxFile__vfunc_07(S *arg0) {
    Gap__Core__igObject__vfunc_07();
    igMetaObject_CountInstances(((DW4VC_88_0 *)(((char *)(arg0) + 0)))->vX(), 1);
    arg0->f48 = FUN_002ed2b0(arg0->f64, 0x40, igObject_GetAllocator(arg0));
    arg0->f48;
}
