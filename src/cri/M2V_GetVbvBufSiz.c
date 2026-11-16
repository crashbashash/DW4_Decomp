int M2VERR_SetCode();
int M2VLIB_CheckHn();

void M2V_GetVbvBufSiz(int arg0, int *arg1, int *arg2, int *arg3) {
    void *temp_s0;

    temp_s0 = (void *)(arg0 + 0x160);
    if (M2VLIB_CheckHn() != 0) {
        M2VERR_SetCode(0, 0xFF03020F);
        return;
    }
    *arg1 = *(int *)((char *)(temp_s0) + 728) << 0xB;
    *arg2 = *(int *)((char *)(temp_s0) + 228);
    *arg3 = -1;
}
