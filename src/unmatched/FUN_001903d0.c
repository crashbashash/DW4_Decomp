/* 0x001903d0 - FUN_001903d0. transpose into a stack matrix then Matrix44_Copy(arg0, tmp): the draft dropped the leading argument. Verified byte-identical by tools/verify.py. */
int Matrix44_Copy(float *, float *);
void FUN_001903d0(float *a) {
    float m[16];
    m[0] = a[0];
    m[1] = a[4];
    m[2] = a[8];
    m[3] = a[12];
    m[4] = a[1];
    m[5] = a[5];
    m[6] = a[9];
    m[7] = a[13];
    m[8] = a[2];
    m[9] = a[6];
    m[10] = a[10];
    m[11] = a[14];
    m[12] = a[3];
    m[13] = a[7];
    m[14] = a[11];
    m[15] = a[15];
    Matrix44_Copy(a, m);
}
