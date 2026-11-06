extern "C" {
struct T { int word0; int references; int f8; int f12; };
T *FUN_00131390(...);
T *FUN_001315d0(...);
T *FUN_00134b60(...);
T *FUN_001359a0(...);
T *FUN_00138cb0(...);
T *FUN_00139ed0(...);
int FUN_001c1e10(...);
int Memory_GetAllocatorBySelector(...);
void igObject_Destroy(T *);
extern T * DAT_00562a68[4];
extern T * DAT_00562a80[4];
extern T * DAT_00562a98[4];
extern T * DAT_00562ab0[4];
extern T * DAT_00562ac8[4];
extern T * DAT_00562ae0[4];
extern T * DAT_00562af8[4];
extern T * DAT_00562b10[4];
extern T * DAT_00562b28[4];
extern T * DAT_00562b40[4];
extern T * DAT_00562b58[4];
extern int DAT_00587038[4];
void Gap__Sg__igPsx2EnvironmentMapShader__vfunc_49(void);
}
struct Rel { static inline void go(T *object) {
    if (object) {
        --object->references;
        if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
class DW4VC_100_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(int); };
class DW4VC_128_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int vX(int); };
class DW4VC_128_4 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int vX(int, int, int, int); };
class DW4VC_132_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int vX(int); };
extern "C" void Gap__Sg__igPsx2EnvironmentMapShader__vfunc_49(void) {
    int temp_s0;
    int temp_s0_10;
    int temp_s0_11;
    int temp_s0_2;
    int temp_s0_3;
    int temp_s0_4;
    int temp_s0_5;
    int temp_s0_6;
    int temp_s0_7;
    int temp_s0_8;
    int temp_s0_9;

    FUN_001c1e10();
    if (DAT_00562a68[0] == 0) {
        temp_s0 = Memory_GetAllocatorBySelector(DAT_00587038[0]);
        Rel::go(DAT_00562a68[0]);
        DAT_00562a68[0] = (T *)(FUN_001359a0(temp_s0));
        ((DW4VC_128_1 *)DAT_00562a68[0])->vX(0);
        temp_s0_2 = Memory_GetAllocatorBySelector(DAT_00587038[0]);
        Rel::go(DAT_00562a80[0]);
        DAT_00562a80[0] = (T *)(FUN_001315d0(temp_s0_2));
        ((DW4VC_128_1 *)DAT_00562a80[0])->vX(0);
        ((DW4VC_100_1 *)DAT_00562a80[0])->vX(0);
    }
    if (DAT_00562b58[0] == 0) {
        temp_s0_3 = Memory_GetAllocatorBySelector(DAT_00587038[0]);
        Rel::go(DAT_00562b58[0]);
        DAT_00562b58[0] = (T *)(FUN_00139ed0(temp_s0_3));
        ((DW4VC_100_1 *)DAT_00562b58[0])->vX(1);
        ((DW4VC_128_1 *)DAT_00562b58[0])->vX(0);
        ((DW4VC_132_1 *)DAT_00562b58[0])->vX(4);
    }
    if (DAT_00562b40[0] == 0) {
        temp_s0_4 = Memory_GetAllocatorBySelector(DAT_00587038[0]);
        Rel::go(DAT_00562b40[0]);
        DAT_00562b40[0] = (T *)(FUN_00134b60(temp_s0_4));
        DAT_00562b40[0]->f12 = 3;
    }
    if (DAT_00562a98[0] == 0) {
        temp_s0_5 = Memory_GetAllocatorBySelector(DAT_00587038[0]);
        Rel::go(DAT_00562a98[0]);
        DAT_00562a98[0] = (T *)(FUN_00131390(temp_s0_5));
        ((DW4VC_128_1 *)DAT_00562a98[0])->vX(1);
        ((DW4VC_100_1 *)DAT_00562a98[0])->vX(1);
    }
    if (DAT_00562ab0[0] == 0) {
        temp_s0_6 = Memory_GetAllocatorBySelector(DAT_00587038[0]);
        Rel::go(DAT_00562ab0[0]);
        DAT_00562ab0[0] = (T *)(FUN_00131390(temp_s0_6));
        ((DW4VC_128_1 *)DAT_00562ab0[0])->vX(1);
        ((DW4VC_100_1 *)DAT_00562ab0[0])->vX(2);
    }
    if (DAT_00562ac8[0] == 0) {
        temp_s0_7 = Memory_GetAllocatorBySelector(DAT_00587038[0]);
        Rel::go(DAT_00562ac8[0]);
        DAT_00562ac8[0] = (T *)(FUN_00131390(temp_s0_7));
        ((DW4VC_128_1 *)DAT_00562ac8[0])->vX(0);
        ((DW4VC_100_1 *)DAT_00562ac8[0])->vX(1);
    }
    if (DAT_00562ae0[0] == 0) {
        temp_s0_8 = Memory_GetAllocatorBySelector(DAT_00587038[0]);
        Rel::go(DAT_00562ae0[0]);
        DAT_00562ae0[0] = (T *)(FUN_00131390(temp_s0_8));
        ((DW4VC_128_1 *)DAT_00562ae0[0])->vX(0);
        ((DW4VC_100_1 *)DAT_00562ae0[0])->vX(2);
    }
    if (DAT_00562af8[0] == 0) {
        temp_s0_9 = Memory_GetAllocatorBySelector(DAT_00587038[0]);
        Rel::go(DAT_00562af8[0]);
        DAT_00562af8[0] = (T *)(FUN_00139ed0(temp_s0_9));
        ((DW4VC_100_1 *)DAT_00562af8[0])->vX(1);
        ((DW4VC_128_1 *)DAT_00562af8[0])->vX(1);
        ((DW4VC_132_1 *)DAT_00562af8[0])->vX(1);
    }
    if (DAT_00562b10[0] == 0) {
        temp_s0_10 = Memory_GetAllocatorBySelector(DAT_00587038[0]);
        Rel::go(DAT_00562b10[0]);
        DAT_00562b10[0] = (T *)(FUN_00139ed0(temp_s0_10));
        ((DW4VC_100_1 *)DAT_00562b10[0])->vX(2);
        ((DW4VC_128_1 *)DAT_00562b10[0])->vX(1);
        ((DW4VC_132_1 *)DAT_00562b10[0])->vX(1);
    }
    if (DAT_00562b28[0] == 0) {
        temp_s0_11 = Memory_GetAllocatorBySelector(DAT_00587038[0]);
        Rel::go(DAT_00562b28[0]);
        DAT_00562b28[0] = (T *)(FUN_00138cb0(temp_s0_11));
        ((DW4VC_128_4 *)DAT_00562b28[0])->vX(0, 0, 0, 1);
    }
}
