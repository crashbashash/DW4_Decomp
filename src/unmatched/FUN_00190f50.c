/* Axis-angle rotation matrix (Rodrigues); the sign bit is cleared through a byte bit-field union,
 * and partial products are split so the adds keep their operand order. */
typedef union U { float f; struct { unsigned char p0, p1, p2; unsigned char lo : 7; unsigned char sign : 1; } b; } U;
extern float GPR_0055495c;
float FUN_00123138(float);
float FUN_001233d8(float);
void FUN_00190f50(float *arg0, float *arg1, float fparg0) {
    U u;
    float p1;
    float p6;
    float p8;
    float s;
    float c;
    float f7;
    float f6;
    float f5;
    float f3;
    float f2;
    float f2b;
    float f4;
    float f2c;
    float one;
    u.f = fparg0;
    u.b.sign = 0;
    if (u.f < GPR_0055495c) {
        arg0[10] = 1.0f;
        arg0[5] = 1.0f;
        arg0[0] = 1.0f;
        arg0[9] = 0.0f;
        arg0[8] = 0.0f;
        arg0[6] = 0.0f;
        arg0[4] = 0.0f;
        arg0[2] = 0.0f;
        arg0[1] = 0.0f;
        return;
    }
    s = FUN_001233d8(fparg0);
    c = FUN_00123138(fparg0);
    f4 = arg1[0];
    one = 1.0f;
    f5 = s * arg1[1];
    f3 = s * arg1[2];
    f7 = one - c;
    f2 = f7 * f4;
    arg0[0] = c + f2 * f4;
    f6 = s * f4;
    p1 = f2 * arg1[1];
    arg0[1] = p1 + f3;
    arg0[2] = f2 * arg1[2] - f5;
    f2b = f7 * arg1[1];
    arg0[4] = f2b * arg1[0] - f3;
    arg0[5] = c + f2b * arg1[1];
    p6 = f2b * arg1[2];
    arg0[6] = p6 + f6;
    f2c = f7 * arg1[2];
    p8 = f2c * arg1[0];
    arg0[8] = p8 + f5;
    arg0[9] = f2c * arg1[1] - f6;
    arg0[10] = c + f2c * arg1[2];
}
