int FUN_0018d0b0();

void FUN_0018d1d0(void *arg0, float *arg1) {
    float sp20[3];
    float temp_f2;

    temp_f2 = arg1[8];
    sp20[0] = arg1[2] + (temp_f2 * arg1[5]);
    sp20[1] = arg1[3] + (temp_f2 * arg1[6]);
    sp20[2] = arg1[4] + (temp_f2 * arg1[7]);
    FUN_0018d0b0(arg0, arg1 + 2);
    FUN_0018d0b0(arg0, sp20);
}
