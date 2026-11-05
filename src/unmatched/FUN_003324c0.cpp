extern "C" {
typedef struct R { char pad4[4]; int f4; } R;
void *FUN_002b9500(int);
int Memory_GetAllocatorByName(int *);
int igObject_Destroy(R *);
extern int DAT_004ffe68[4];
extern R * DAT_005875e0[4];
void FUN_003324c0(void) {
    int temp_s0;
    R *old;

    temp_s0 = Memory_GetAllocatorByName(&DAT_004ffe68[0]);
    old = DAT_005875e0[0];
    if (old != 0) {
        old->f4 = old->f4 - 1;
        if ((old->f4 & 0x7FFFFF) == 0) {
            igObject_Destroy(old);
        }
    }
    DAT_005875e0[0] = (R *)FUN_002b9500(temp_s0);
}
}
