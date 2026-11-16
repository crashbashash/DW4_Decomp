int M2VERR_SetCode();
int M2VLIB_CheckHn();

void M2V_GetLinkFlg(int arg0, int *arg1, int *arg2) {
    void *temp_s0;

    temp_s0 = (void *)(arg0 + 0x160);
    if (M2VLIB_CheckHn() != 0) {
        M2VERR_SetCode(0, 0xFF03020E);
        return;
    }
    *arg1 = *(int *)((char *)(temp_s0) + 208);
    *arg2 = *(int *)((char *)(temp_s0) + 212);
}
