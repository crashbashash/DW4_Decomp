igVectorMorphFunction g_igVectorMorphing_morph;
igVectorMorphFunction g_igVectorMorphing_morphVu0;

/* out[v] = base[v] + sum over the targets of weights[t] * targets[t][v], for count packed vec3 vertices; out
   advances by stride bytes per vertex. */
/* matching construct: template sweep — products computed into locals before the adds */
void igVectorMorphing_Morph(const float *base, const float **targets, const float *weights, unsigned int count,
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

/* The VU0 form of the morph: while four vertices remain they are three quadwords (base, every target and out all
   16-byte aligned and packed), summed in VU0 registers; the rest go one by one and out takes the stride. */
void igVectorMorphing_MorphVu0(const float *base, const float **targets, const float *weights, unsigned int count,
                  unsigned int targetCount, float *out, int stride) {
    unsigned int i;
    unsigned int j;
    unsigned int quadwordCount = (count >> 2) * 3;
    unsigned int offset = 0;

    for (unsigned int quadword = 0; quadword < quadwordCount; quadword += 3) {
        asm volatile {
            lqc2 vf1, 0(base)
            lqc2 vf2, 16(base)
            lqc2 vf3, 32(base)
        }
        base += 12;
        /* qmtc2 moves a general register, so the weight is read as its bit pattern. */
        const int *weightBits = (const int *)weights;
        for (unsigned int t = 0; t < targetCount; t++) {
            int weight = *weightBits;
            const float *target = (const float *)((const char *)targets[t] + offset);
            asm volatile {
                qmtc2 weight, vf7
                lqc2 vf4, 0(target)
                lqc2 vf5, 16(target)
                lqc2 vf6, 32(target)
                vmulx.xyzw vf4, vf4, vf7x
                vmulx.xyzw vf5, vf5, vf7x
                vmulx.xyzw vf6, vf6, vf7x
                vadd.xyzw vf1, vf1, vf4
                vadd.xyzw vf2, vf2, vf5
                vadd.xyzw vf3, vf3, vf6
            }
            weightBits++;
        }
        asm volatile {
            sqc2 vf1, 0(out)
            sqc2 vf2, 16(out)
            sqc2 vf3, 32(out)
        }
        offset += 48;
        out += 12;
    }
    /* A function holding a volatile asm statement keeps this triple in its stack slot (retail's 0..8(sp)). */
    for (i = (count >> 2) * 4; i < count; i++) {
        out[0] = base[0];
        out[1] = base[1];
        out[2] = base[2];
        base += 3;
        for (j = 0; j < targetCount; j++) {
            float scaled[3];
            float weight = weights[j];
            const float *target = &targets[j][i * 3];
            scaled[0] = weight * target[0];
            scaled[1] = weight * target[1];
            scaled[2] = weight * target[2];
            out[0] += scaled[0];
            out[1] += scaled[1];
            out[2] += scaled[2];
        }
        out = (float *)((char *)out + stride);
    }
}

void igVectorMorphing_InstallFunctions(void) {
    g_igVectorMorphing_morph = igVectorMorphing_Morph;
    g_igVectorMorphing_morphVu0 = igVectorMorphing_MorphVu0;
}
