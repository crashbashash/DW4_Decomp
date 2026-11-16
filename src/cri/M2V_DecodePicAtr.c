int M2VERR_SetCode();
int FUN_00285b10();
int m2vhdec_ParseSj();
int M2VLIB_CheckHn();

int M2V_DecodePicAtr(int arg0, int arg1) {
    int temp_v0;

    if (M2VLIB_CheckHn() != 0) {
        return M2VERR_SetCode(0, 0xFF03020C);
    }
    temp_v0 = m2vhdec_ParseSj(arg0, arg1);
    if (temp_v0 == 0) {
        FUN_00285b10(arg0);
    }
    return temp_v0;
}
