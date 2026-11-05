/* 0x0018b990 - 76 bytes. Midpoint of two vec3 at +8 and +20; the compiler emits mula.s/madd.s itself for a*c + b*c. */
void FUN_0018b990(float *arg0, float *arg1) {
    arg1[0] = arg0[2] * 0.5f + arg0[5] * 0.5f;
    arg1[1] = arg0[3] * 0.5f + arg0[6] * 0.5f;
    arg1[2] = arg0[4] * 0.5f + arg0[7] * 0.5f;
}
