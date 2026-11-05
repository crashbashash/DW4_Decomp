typedef struct S { int pad[2]; float f[6]; } S;
void FUN_0018aaa0(S *arg0, float *arg1) {
    float z, y, x;
    arg1[0] = arg0->f[0];
    arg1[1] = arg0->f[1];
    arg1[2] = arg0->f[2];
    z = arg0->f[5]; y = arg0->f[1]; x = arg0->f[0];
    arg1[3] = x; arg1[4] = y; arg1[5] = z;
    z = arg0->f[2]; y = arg0->f[4]; x = arg0->f[0];
    arg1[6] = x; arg1[7] = y; arg1[8] = z;
    z = arg0->f[5]; y = arg0->f[4]; x = arg0->f[0];
    arg1[9] = x; arg1[10] = y; arg1[11] = z;
    z = arg0->f[2]; y = arg0->f[1]; x = arg0->f[3];
    arg1[12] = x; arg1[13] = y; arg1[14] = z;
    z = arg0->f[5]; y = arg0->f[1]; x = arg0->f[3];
    arg1[15] = x; arg1[16] = y; arg1[17] = z;
    z = arg0->f[2]; y = arg0->f[4]; x = arg0->f[3];
    arg1[18] = x; arg1[19] = y; arg1[20] = z;
    arg1[21] = arg0->f[3];
    arg1[22] = arg0->f[4];
    arg1[23] = arg0->f[5];
}
