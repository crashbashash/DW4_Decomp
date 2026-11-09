void FUN_0018e8f0(const float *in, unsigned int count, const float *weights, const unsigned char *bone,
                  int boneStride, const float (*matrices)[16], float *out, int outStride) {
    unsigned int i;
    const float *m;
    float x;
    float y;
    float z;
    float rx;
    float ry;
    float rz;

    for (i = 0; i < count; i++) {
        m = matrices[*bone];
        x = in[0];
        y = in[1];
        z = in[2];
        bone += boneStride;
        rx = m[12] + (x * m[0] + y * m[4] + z * m[8]);
        ry = m[13] + (x * m[1] + y * m[5] + z * m[9]);
        rz = m[14] + (x * m[2] + y * m[6] + z * m[10]);
        out[0] = rx;
        out[1] = ry;
        out[2] = rz;
        in += 4;
        out = (float *)((char *)out + outStride);
    }
}
