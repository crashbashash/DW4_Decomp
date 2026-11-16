int M2VERR_SetCode();
int M2VLIB_CheckHn();

void M2V_Destroy(int *arg0) {
    if (M2VLIB_CheckHn() != 0) {
        M2VERR_SetCode(0, 0xFF030201);
        return;
    }
    *arg0 = 1;
}
