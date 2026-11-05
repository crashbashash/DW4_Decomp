void FUN_00192e10(float *arg0, float *arg1) {
    float b0; float a0; float b1; float a2; float b2; float a1;
    b2 = arg1[2]; a1 = arg0[1]; a0 = arg0[0]; b1 = arg1[1]; a2 = arg0[2]; b0 = arg1[0];
    arg0[0] = a1 * b2 - a2 * b1;
    arg0[1] = a2 * b0 - a0 * b2;
    arg0[2] = a0 * b1 - a1 * b0;
}
