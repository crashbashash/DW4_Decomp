/* Gap__Sg__igEnbayaContextPool__vfunc_13 */
int sscanf();
int FUN_001c1a80();
void *FUN_002b9500();
int FUN_003064b0();
int FUN_00306510();
int FUN_003065f0();
int Gap__Core__igObject__vfunc_11();
int Memory_GetAllocatorBySelector();
int igObject_Destroy();
int igObject_GetAllocator();
extern int DAT_004c22f0[4];
extern int DAT_004e45e0[4];
extern void * DAT_00586dc8[4];
extern int DAT_00587060[4];
extern unsigned char GPR_00554c14;

void Gap__Sg__igEnbayaContextPool__vfunc_13(int arg0) {
    void *sp5C;
    int var_a0;
    int temp_s2;
    int var_s1;
    int sp58;
    int var_a2;
    int temp_s0;
    int sp54;
    int var_v0;

    Gap__Core__igObject__vfunc_11();
    temp_s2 = *(int *)((char *)(DAT_00586dc8[0]) + 56);
    var_v0 = igObject_GetAllocator(arg0);
    var_v0 = GPR_00554c14 != 0 ? var_v0 : Memory_GetAllocatorBySelector(DAT_00587060[0]);
    sp5C = (void *)(FUN_002b9500(var_v0));
    temp_s0 = FUN_003064b0(temp_s2, 7);
    var_s1 = 0;
    while (var_s1 < temp_s0) {
        if (FUN_00306510(temp_s2, 7, var_s1, &sp5C) != 0) {
            sp58 = 0;
            var_a2 = *(int *)((char *)(sp5C) + 8);
            var_a2 = (var_a2 == 0) ? DAT_004c22f0[0] : var_a2;
            if (FUN_003065f0(temp_s2, 7, var_a2, &sp58, 0, 0) != 0) {
                sp54 = 0;
                var_a0 = *(int *)((char *)(sp5C) + 8);
                var_a0 = (var_a0 == 0) ? DAT_004c22f0[0] : var_a0;
                if ((sscanf(var_a0, &DAT_004e45e0[0], &sp54) == 1) && (sp54 >= 0) && (sp58 >= 0)) {
                    FUN_001c1a80(arg0, sp54, sp58);
                }
            }
        }
        var_s1 += 1;
    }
    var_v0 = (int)sp5C;
    if (var_v0 != 0) {
        *(int *)((char *)(var_v0) + 4) = (int)((int) (*(int *)((char *)(var_v0) + 4) - 1));
        if (((unsigned long long) ((long long) *(int *)((char *)(var_v0) + 4) << 0x29) >> 0x29) == 0) {
            igObject_Destroy(var_v0);
        }
    }
}
