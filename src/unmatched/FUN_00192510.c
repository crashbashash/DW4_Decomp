typedef struct S { float f0; char p4[28]; float f32; float f36; float f40; char p44[12]; float f56; } S;
void FUN_00192510(S *a, float *arg1, float *arg2, float *arg3, float *arg4, float *arg5, float *arg6) {
    float t2;
    float t6;
    float t5;
    float tf2;
    float t3;
    float t1;
    float t0;
    t6 = a->f56 / 2.0f;
    tf2 = a->f40;
    t5 = 1.0f + tf2;
    t2 = 1.0f - tf2;
    if (t2 == 0.0f || t5 == 0.0f || a->f0 == 0.0f) return;
    *arg5 = -t6 * (1.0f + (t5 / t2));
    *arg6 = t6 * (1.0f + (t2 / t5));
    t3 = *arg5 / a->f0;
    *arg1 = -(t3 * (1.0f - a->f32));
    t1 = 2.0f * t3;
    *arg2 = t1 + *arg1;
    t0 = -(t3 * (1.0f - a->f36));
    *arg3 = t0;
    *arg4 = t1 + t0;
}
