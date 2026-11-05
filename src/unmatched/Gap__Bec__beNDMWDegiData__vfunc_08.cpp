class V88 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); char pad[24]; int f28; };
extern "C" {
int Gap__Core__igObject__vfunc_08__002ff0f0(...);
int Memory_FreeBufferWithAllocator(...);
int Memory_GetAllocatorBySelector(...);
int igMetaObject_CountInstances(...);
int igObject_GetAllocator(...);
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
void Gap__Bec__beNDMWDegiData__vfunc_08(V88 *arg0);
}
void Gap__Bec__beNDMWDegiData__vfunc_08(V88 *arg0) {
    int a;

    if (arg0->f28 != 0) {
        a = igObject_GetAllocator(arg0);
        a = GPR_00554c14 != 0 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        Memory_FreeBufferWithAllocator(arg0->f28, a);
    }
    arg0->f28 = 0;
    igMetaObject_CountInstances(arg0->vX(), 1);
    Gap__Core__igObject__vfunc_08__002ff0f0(arg0);
}
