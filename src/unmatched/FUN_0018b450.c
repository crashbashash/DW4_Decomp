int FUN_0018afa0();
int FUN_0018b450(float *a, float *b) {
    float r, d0, d1, d2, d3, d4, d5;
    if (FUN_0018afa0(a, b) == 0) return 0;
    d0 = b[2] - a[2];
    d1 = b[3] - a[3];
    d2 = b[4] - a[4];
    d3 = b[2] - a[5];
    d4 = b[3] - a[6];
    d5 = b[4] - a[7];
    r = b[5] * b[5];
    d0 = d0 * d0; d1 = d1 * d1; d2 = d2 * d2; d3 = d3 * d3; d4 = d4 * d4; d5 = d5 * d5;
    if (!(r <= d0 && r <= d1 && r <= d2 && r <= d3 && r <= d4 && r <= d5)) return 1;
    return 2;
}
