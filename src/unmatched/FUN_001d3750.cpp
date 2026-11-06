extern "C" {
void **FUN_00131390(...);
void **FUN_00133610(...);
void **FUN_00135e20(...);
void *FUN_00137070(...);
void **FUN_00138690(...);
void **FUN_00139600(...);
void **FUN_00139ed0(...);
void **FUN_0013b270(...);
int FUN_001d33a0(...);
int Memory_GetAllocatorBySelector(...);
int igMetaObject_CountInstances(...);
extern void ** DAT_00562798[4];
extern void ** DAT_005627a0[4];
extern void ** DAT_005627a8[4];
extern void ** DAT_005627b0[4];
extern void ** DAT_005627b8[4];
extern void * DAT_005627c0[4];
extern void ** DAT_005627c8[4];
extern void ** DAT_005627d0[4];
extern void ** DAT_005627d8[4];
extern int DAT_00587038[4];
void FUN_001d3750(void **arg0);
}
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
class DW4VC_128_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int vX(int); };
class DW4VC_132_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int vX(int); };
class DW4VC_136_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual int vX(int); };
class DW4VC_140_3 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual int vX(int, int, int); };
void FUN_001d3750(void **arg0) {
    FUN_001d33a0();
    if (igMetaObject_CountInstances(((DW4VC_88_0 *)(arg0))->vX(), 1) == 0) {
        DAT_00562798[0] = (void **)(FUN_00139ed0(Memory_GetAllocatorBySelector(DAT_00587038[0])));
        DAT_005627a0[0] = (void **)(FUN_00139ed0(Memory_GetAllocatorBySelector(DAT_00587038[0])));
        ((DW4VC_128_1 *)(DAT_005627a0[0]))->vX((int)(0));
        ((DW4VC_132_1 *)(DAT_005627a0[0]))->vX((int)(0));
        DAT_005627a8[0] = (void **)(FUN_00139600(Memory_GetAllocatorBySelector(DAT_00587038[0])));
        ((DW4VC_128_1 *)(DAT_005627a8[0]))->vX((int)(1));
        DAT_005627b0[0] = (void **)(FUN_00135e20(Memory_GetAllocatorBySelector(DAT_00587038[0])));
        ((DW4VC_128_1 *)(DAT_005627b0[0]))->vX((int)(0));
        DAT_005627b8[0] = (void **)(FUN_00131390(Memory_GetAllocatorBySelector(DAT_00587038[0])));
        ((DW4VC_128_1 *)(DAT_005627b8[0]))->vX((int)(0));
        DAT_005627c8[0] = (void **)(FUN_0013b270(Memory_GetAllocatorBySelector(DAT_00587038[0])));
        ((DW4VC_128_1 *)(DAT_005627c8[0]))->vX((int)(0));
        DAT_005627c0[0] = (void *)(FUN_00137070(Memory_GetAllocatorBySelector(DAT_00587038[0])));
        *(int *)((char *)(DAT_005627c0[0]) + 12) = 1;
        DAT_005627d0[0] = (void **)(FUN_00133610(Memory_GetAllocatorBySelector(DAT_00587038[0])));
        ((DW4VC_128_1 *)(DAT_005627d0[0]))->vX((int)(1));
        ((DW4VC_136_1 *)(DAT_005627d0[0]))->vX((int)(2));
        ((DW4VC_140_3 *)(DAT_005627d0[0]))->vX((int)(0), (int)(3), (int)(3));
        DAT_005627d8[0] = (void **)(FUN_00138690(Memory_GetAllocatorBySelector(DAT_00587038[0])));
        ((DW4VC_132_1 *)(DAT_005627d8[0]))->vX((int)(0));
    }
}
