float cosf(float);
float sinf(float);

void FUN_001910c0(float *m, float x, float y, float z) {
    float sx;
    float sxy;
    float sy;
    float sz;
    float cx;
    float cz;
    float t3;
    float t2;
    float cy;
    sx = 0.0f;
    if (x != 0.0f) {
        sx = sinf(x);
        cx = cosf(x);
    } else {
        cx = 1.0f;
    }
    sy = 0.0f;
    if (y != 0.0f) {
        sy = sinf(y);
        cy = cosf(y);
        sxy = sx * sy;
    } else {
        cy = 1.0f;
        sxy = sy;
    }
    sz = 0.0f;
    if (z != 0.0f) {
        sz = sinf(z);
        cz = cosf(z);
        t3 = cx * sz;
    } else {
        cz = 1.0f;
        t3 = sz;
    }
    m[0] = cy * cz;
    m[1] = cy * sz;
    m[2] = -sy;
    m[4] = sxy * cz - t3;
    m[5] = sxy * sz + cx * cz;
    m[6] = sx * cy;
    t2 = cx * cz;
    m[8] = t2 * sy + sx * sz;
    m[9] = t3 * sy - sx * cz;
    m[10] = cx * cy;
}
