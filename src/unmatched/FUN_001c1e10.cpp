extern "C" {
void **FUN_00131390(...);
void **FUN_00139600(...);
void *FUN_0013b270(...);
int Memory_GetAllocatorBySelector(...);
int igObject_Destroy(...);
extern void ** DAT_00562730[4];
extern void ** DAT_00562738[4];
extern void ** DAT_00562740[4];
struct T { int w0; int refs; };
extern T * DAT_00562758[4];
extern int DAT_00587038[4];
void FUN_001c1e10(void);
}
class DW4VC_100_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(int); };
class DW4VC_128_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int vX(int); };
void FUN_001c1e10(void) {
    int temp_s0;

    if (DAT_00562730[0] == 0) {
        DAT_00562730[0] = (void **)(FUN_00131390(Memory_GetAllocatorBySelector(DAT_00587038[0])));
        ((DW4VC_128_1 *)(DAT_00562730[0]))->vX((int)(1));
        ((DW4VC_100_1 *)(DAT_00562730[0]))->vX((int)(0));
    }
    if (DAT_00562738[0] == 0) {
        DAT_00562738[0] = (void **)(FUN_00139600(Memory_GetAllocatorBySelector(DAT_00587038[0])));
        ((DW4VC_128_1 *)(DAT_00562738[0]))->vX((int)(1));
    }
    if (DAT_00562740[0] == 0) {
        DAT_00562740[0] = (void **)(FUN_00139600(Memory_GetAllocatorBySelector(DAT_00587038[0])));
        ((DW4VC_128_1 *)(DAT_00562740[0]))->vX((int)(0));
    }
    if (DAT_00562758[0] == 0) {
        T *p;
        temp_s0 = Memory_GetAllocatorBySelector(DAT_00587038[0]);
        p = DAT_00562758[0];
        if (p != 0) {
            p->refs = p->refs - 1;
            if (((unsigned long long) ((long long) p->refs << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
        }
        DAT_00562758[0] = (T *)(FUN_0013b270(temp_s0));
        ((DW4VC_128_1 *)(DAT_00562758[0]))->vX((int)(0));
    }
}
