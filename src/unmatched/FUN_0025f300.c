float sqrtf(float);
float cosf(float);
void FUN_0025f300(int arg0, int arg1, short *arg2, short *arg3) {
    float a, b, r, s, c;
s = sqrtf(2.0f);
c = cosf(((float) arg0 * 6.2831851f) / (float) arg1);
a = s - c;
b = sqrtf(2.0f) - 1.0f;
    r = (a - sqrtf((a + b) * (a - b))) / b;
    *arg2 = (short) (int) (2.0f * r * 4096.0f);
    *arg3 = (short) (int) (-r * r * 4096.0f);
}
