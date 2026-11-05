typedef struct X { char pad[4]; int f4; int f8; } X;
extern X *DAT_0055f508[4];
extern int DAT_00587028[4];
extern int DAT_005870f8[4];
extern unsigned char GPR_00554c14;
X *FUN_001356b0();
int Memory_GetAllocatorBySelector();
int igObject_Destroy();
X *FUN_0013f680(void) { int s0, r1, r2; X *t;
    if (DAT_0055f508[0] == 0) {
        if (GPR_00554c14 != 0) { r1 = Memory_GetAllocatorBySelector(DAT_00587028[0]); s0 = r1; } else { r2 = Memory_GetAllocatorBySelector(DAT_005870f8[0]); s0 = r2; }
        t = DAT_0055f508[0];
        if (t != 0) {
            t->f4 = t->f4 - 1;
            if (((unsigned long long) ((long long) t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
        DAT_0055f508[0] = FUN_001356b0(s0);
    }
    return DAT_0055f508[0];
}
