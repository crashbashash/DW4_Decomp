int FUN_001ee600();
int p2SubmitDmaPacket();
extern int DAT_0048dcc0[4];
extern int DAT_0048dcc4[4];
extern int DAT_0048dcc8[4];
extern int DAT_0048dccc[4];
extern int DAT_0048dcd0[4];
extern int DAT_0048dcd8[4];
extern int DAT_00491478[4];
extern int DAT_00562cb0[4];
extern int DAT_00562d08[4];
extern int DAT_00568e50[4];
extern void * DAT_00568f04[4];
int FUN_001e8be0(int arg0, void *arg1) {
    void *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (void *)(*(int *)((char *)(DAT_00568f04[0]) + 48));
        *(int *)((char *)(temp_a0) + 0) = (int)((int) DAT_0048dcc0[0]);
        *(int *)((char *)(temp_a0) + 4) = (int)((int) DAT_0048dcc4[0]);
        *(int *)((char *)(temp_a0) + 8) = (int)((int) DAT_0048dcc8[0]);
        *(int *)((char *)(temp_a0) + 12) = (int)((int) DAT_0048dccc[0]);
        *(int *)((char *)(temp_a0) + 16) = (int)((int) DAT_0048dcd0[0]);
        *(int *)((char *)(temp_a0) + 20) = (int)((int) DAT_00562d08[0]);
        *(int *)((char *)(temp_a0) + 24) = (int)((int) DAT_00562d08[0]);
        *(int *)((char *)(temp_a0) + 28) = (int)((int) DAT_0048dcd8[0]);
        *(float *)((char *)(temp_a0) + 32) = (float) *(float *)((char *)(arg1) + 0);
        *(float *)((char *)(temp_a0) + 36) = (float) *(float *)((char *)(arg1) + 4);
        *(float *)((char *)(temp_a0) + 40) = (float) *(float *)((char *)(arg1) + 8);
        *(float *)((char *)(temp_a0) + 44) = (float) *(float *)((char *)(arg1) + 12);
        *(int *)((char *)(DAT_00568f04[0]) + 48) = (int)((int) ((char *)temp_a0 + 0x30));
        if ((unsigned int) *(int *)((char *)(DAT_00568f04[0]) + 48) < (unsigned int) *(int *)((char *)(DAT_00568f04[0]) + 40)) {
        } else {
            if (DAT_00568e50[0] != 0) {
                FUN_001ee600();
            } else {
                p2SubmitDmaPacket(1);
            }
        }
    }
    DAT_00562cb0[0] = arg0;
    DAT_00491478[0] |= 0x11;
    return 1;
}
