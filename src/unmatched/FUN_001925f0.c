float sqrtf(float);
void FUN_001925f0(float *q, float *m) {
    float tr = m[10] + (m[0] + m[5]);
    if (!(tr < 0.0f)) {
        float s, r; s = sqrtf(1.0f + tr);
        q[3] = 0.5f * s;
        r = 0.5f / s;
        q[0] = r * (m[9] - m[6]);
        q[1] = r * (m[2] - m[8]);
        q[2] = r * (m[4] - m[1]);
        return;
    }
    {
        int i;
        i = 0;
        if (!(m[5] <= m[0])) i = 1;
        if (!(m[10] <= *(float*)((char*)m + i*16 + i*4))) i = 2;
        switch (i) {
        case 0: {
            float s, r; s = sqrtf(m[15] + (m[0] - (m[5] + m[10])));
            q[0] = 0.5f * s;
            r = 0.5f / s;
            q[1] = r * (m[1] + m[4]);
            q[2] = r * (m[8] + m[2]);
            q[3] = r * (m[9] - m[6]);
            break; }
        case 1: {
            float s, r; s = sqrtf(m[15] + (m[5] - (m[10] + m[0])));
            q[1] = 0.5f * s;
            r = 0.5f / s;
            q[2] = r * (m[6] + m[9]);
            q[0] = r * (m[1] + m[4]);
            q[3] = r * (m[2] - m[8]);
            break; }
        case 2: {
            float s, r; s = sqrtf(m[15] + (m[10] - (m[0] + m[5])));
            q[2] = 0.5f * s;
            r = 0.5f / s;
            q[0] = r * (m[8] + m[2]);
            q[1] = r * (m[6] + m[9]);
            q[3] = r * (m[4] - m[1]);
            break; }
        }
    }
}
