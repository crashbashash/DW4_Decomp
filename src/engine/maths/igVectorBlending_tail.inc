/* Each vertex is the sum of its weightCount bone transforms scaled by their weights; a weight at or below 0.0001
   is skipped. */
void igVectorBlending_BlendWeighted(const float *in, unsigned int count, const float *weights, const unsigned char *bones,
                  unsigned int weightCount, const float (*matrices)[16], float *out, int outStride) {
    unsigned int i;
    unsigned int j;
    float weight;
    float x, y, z, rx, ry, rz;
    const float *m;
    unsigned char bone;

    for (i = 0; i < count; i++) {
        out[0] = 0.0f;
        out[1] = 0.0f;
        out[2] = 0.0f;
        for (j = 0; j < weightCount; j++) {
            weight = *weights++;
            bone = *bones++;
            if (!(weight <= 0.0001f)) {
                m = matrices[bone];
                x = in[0];
                y = in[1];
                z = in[2];
                rx = m[12] + (x * m[0] + y * m[4] + z * m[8]);
                ry = m[13] + (x * m[1] + y * m[5] + z * m[9]);
                rz = m[14] + (x * m[2] + y * m[6] + z * m[10]);
                rx *= weight;
                ry *= weight;
                rz *= weight;
                out[0] += rx;
                out[1] += ry;
                out[2] += rz;
            }
        }
        out = (float *)((char *)out + outStride);
        in += 4;
    }
}

igVectorBlendFunction g_igVectorBlending_blendWeighted;
igVectorBlendFunction g_igVectorBlending_blendOneWeight;

/* One bone per vertex at full weight: the first of its weightCount bone indices (weights is not read). */
void igVectorBlending_BlendOneWeight(const float *in, unsigned int count, const float *weights, const unsigned char *bones,
                  unsigned int weightCount, const float (*matrices)[16], float *out, int outStride) {
    unsigned int i;
    const float *m;
    float x;
    float y;
    float z;
    float rx;
    float ry;
    float rz;

    for (i = 0; i < count; i++) {
        m = matrices[*bones];
        x = in[0];
        y = in[1];
        z = in[2];
        bones += weightCount;
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

void igVectorBlending_InstallFunctions(void) {
    g_igVectorBlending_blendWeighted = igVectorBlending_BlendWeighted;
    g_igVectorBlending_blendOneWeight = igVectorBlending_BlendOneWeight;
}

