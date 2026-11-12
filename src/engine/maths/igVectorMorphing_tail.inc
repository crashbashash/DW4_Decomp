/* matching construct: template sweep — products computed into locals before the adds */
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

void FUN_0018ec10(void) {
    DAT_00561108[0] = (int *)(&FUN_0018e9e0);
    DAT_00561110[0] = (int *)(&FUN_0018ea90);
}

