int FUN_001ee600();
int p2SubmitDmaPacket();
extern float DAT_0048dc88[4];
extern float DAT_0048dc8c[4];
extern float DAT_0048dc90[4];
extern int DAT_0048dca0[4];
extern int DAT_0048dca4[4];
extern int DAT_0048dca8[4];
extern int DAT_0048dcac[4];
extern int DAT_0048dcb0[4];
extern int DAT_0048dcb8[4];
extern int DAT_00562d00[4];
extern int DAT_00568e50[4];
extern void * DAT_00568f04[4];
void FUN_001e8990(void) {
    void *temp_a1;

    temp_a1 = (void *)(*(int *)((char *)(DAT_00568f04[0]) + 48));
    *(int *)((char *)(temp_a1) + 0) = (int)((int) DAT_0048dca0[0]);
    *(int *)((char *)(temp_a1) + 4) = (int)((int) DAT_0048dca4[0]);
    *(int *)((char *)(temp_a1) + 8) = (int)((int) DAT_0048dca8[0]);
    *(int *)((char *)(temp_a1) + 12) = (int)((int) DAT_0048dcac[0]);
    *(int *)((char *)(temp_a1) + 16) = (int)((int) DAT_0048dcb8[0]);
    *(int *)((char *)(temp_a1) + 20) = (int)((int) DAT_00562d00[0]);
    *(int *)((char *)(temp_a1) + 24) = (int)((int) DAT_00562d00[0]);
    *(int *)((char *)(temp_a1) + 28) = (int)((int) DAT_00562d00[0]);
    *(int *)((char *)(temp_a1) + 32) = (int)((int) DAT_0048dcb0[0]);
    *(float *)((char *)(temp_a1) + 36) = (float) DAT_0048dc88[0];
    *(float *)((char *)(temp_a1) + 40) = (float) DAT_0048dc8c[0];
    *(float *)((char *)(temp_a1) + 44) = (float) DAT_0048dc90[0];
    *(int *)((char *)(DAT_00568f04[0]) + 48) = (int)((int) ((char *)temp_a1 + 0x30));
    if ((unsigned int) *(int *)((char *)(DAT_00568f04[0]) + 48) >= (unsigned int) *(int *)((char *)(DAT_00568f04[0]) + 40)) {
        if (DAT_00568e50[0] != 0) {
            FUN_001ee600();
        } else {
            p2SubmitDmaPacket(1);
        }
    }
}
