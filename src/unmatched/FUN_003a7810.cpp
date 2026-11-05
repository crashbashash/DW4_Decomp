extern "C" {
extern float DAT_004c8fc0[];
extern float DAT_004c90b0[];
float FUN_003a7810(float *arg0);
}
float FUN_003a7810(float *arg0) {
    float t;
    if (arg0[5] < arg0[6]) {
        t = arg0[4] + arg0[7];
        arg0[4] = t;
        return DAT_004c8fc0[(int)t];
    }
    t = arg0[4] + arg0[7];
    arg0[4] = t;
    return DAT_004c90b0[(int)t];
}
