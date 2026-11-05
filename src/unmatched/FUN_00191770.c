float sqrtf(float);
void FUN_00191770(float *m, float *q) {
    float x = q[0], y = q[1], z = q[2], w = q[3];
    float n = 1.0f / sqrtf(z * z + (x * x + y * y) + w * w);
    y = y * n;
    z = z * n;
    w = w * n;
    x = x * n;
    m[0] = 1.0f - 2.0f * (y * y + z * z);
    m[1] = 2.0f * (x * y - z * w);
    m[2] = 2.0f * (z * x + y * w);
    m[4] = 2.0f * (x * y + z * w);
    m[5] = 1.0f - 2.0f * (z * z + x * x);
    m[6] = 2.0f * (y * z - x * w);
    m[8] = 2.0f * (z * x - y * w);
    m[9] = 2.0f * (y * z + x * w);
    m[10] = 1.0f - 2.0f * (y * y + x * x);
}
