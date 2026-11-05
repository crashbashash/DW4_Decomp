void FUN_00191910(float *m, float l, float r, float b, float t, float n, float f) {
    float rw, n2, rh, rd;
    rw = 1.0f / (r - l);
    n2 = 2.0f * n;
    m[0] = n2 * rw;
    m[4] = 0;
    rh = 1.0f / (t - b);
    m[8] = rw * (r + l);
    m[12] = 0;
    m[1] = 0;
    m[5] = n2 * rh;
    m[9] = rh * (t + b);
    m[13] = 0;
    m[2] = 0;
    m[6] = 0;
    rd = 1.0f / (f - n);
    m[10] = rd * -(f + n);
    m[14] = rd * (-2.0f * f * n);
    m[3] = 0;
    m[7] = 0;
    m[11] = -1.0f;
    m[15] = 0;
}
