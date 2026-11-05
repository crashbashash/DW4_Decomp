/* 0x00192dd0 - FUN_00192dd0. cross product; the compiler emits mula/msub itself; locals declared in register order, loads in the winning order Verified byte-identical by tools/verify.py. */
void FUN_00192dd0(float *arg0, float *arg1, float *arg2) {
    float a1; float b2; float a2; float b1; float a0; float b0;
    a0 = arg1[0];
    b0 = arg2[0];
    b2 = arg2[2];
    a2 = arg1[2];
    b1 = arg2[1];
    a1 = arg1[1];
    arg0[0] = a1 * b2 - a2 * b1;
    arg0[1] = a2 * b0 - a0 * b2;
    arg0[2] = a0 * b1 - a1 * b0;
}
