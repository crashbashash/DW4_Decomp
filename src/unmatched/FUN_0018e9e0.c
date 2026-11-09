/* matching construct: template sweep — products computed into locals before the adds */
static inline void addScaled(float *out, float weight, const float *v) {
    float x = weight * v[0];
    float y = weight * v[1];
    float z = weight * v[2];
    out[0] += x;
    out[1] += y;
    out[2] += z;
}

void FUN_0018e9e0(const float *base, const float **targets, const float *weights, unsigned int count,
                  unsigned int targetCount, float *out, int stride) {
    unsigned int i;
    unsigned int j;
    float weight;

    for (i = 0; i < count; i++) {
        out[0] = base[i * 3 + 0];
        out[1] = base[i * 3 + 1];
        out[2] = base[i * 3 + 2];
        for (j = 0; j < targetCount; j++) {
            weight = weights[j];
            addScaled(out, weight, &targets[j][i * 3]);
        }
        out = (float *)((char *)out + stride);
    }
}
