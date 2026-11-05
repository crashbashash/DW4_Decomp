extern "C" {
float FUN_003a8140(int, int *);
extern int DAT_0050f0b8[4];
void FUN_003951e0(int a0, int a1, float *a2);
}
void FUN_003951e0(int a0, int a1, float *a2) {
    float f = a2[31];
    if (!(f <= 0.0f)) {
        float v = f - FUN_003a8140(a1, &DAT_0050f0b8[0]);
        if (v < 0.0f) v = 0.0f;
        a2[31] = v;
    }
}
