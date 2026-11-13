void *igStringObj_Create();
int FUN_002e3280();
int FUN_00306770();
int Memory_GetAllocatorBySelector();
int igObject_Destroy();
extern int DAT_004c2128[4];
extern int DAT_004c22f0[4];
extern int DAT_004f9a58[4];
extern void * DAT_00586dc8[4];
extern int DAT_00587048[4];

typedef struct R { int w0; int refs; int f8; } R;
typedef struct G { char pad[56]; int f56; } G;
extern G * DAT_00586dc8b[4];

void FUN_002e33d0(void) {
    R *sp3C;
    int temp_s1;
    int temp_s0;
    int var_a0;
    R *temp_a0;

    temp_s1 = DAT_004c2128[0];
    temp_s0 = *(int *)((char *)(DAT_00586dc8[0]) + 56);
    if (temp_s0 != 0) {
        sp3C = (R *)igStringObj_Create(Memory_GetAllocatorBySelector(DAT_00587048[0]));
        FUN_00306770(temp_s0, 2, &DAT_004f9a58[0], &sp3C, temp_s1, 0);
        var_a0 = sp3C->f8;
        if (var_a0 == 0) {
            var_a0 = DAT_004c22f0[0];
        }
        FUN_002e3280(var_a0);
        temp_a0 = sp3C;
        if (temp_a0 != 0) {
            temp_a0->refs = temp_a0->refs - 1;
            if (((unsigned long long)((long long)temp_a0->refs << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
    }
}
