void FUN_001419f0(struct TransformPairView *arg0, float *m, void *arg2) {
    if (InRange(m[0], 0.999999f, 1.000001f) &&
        InRange(m[1], -0.000001f, 0.000001f) &&
        InRange(m[2], -0.000001f, 0.000001f) &&
        InRange(m[3], -0.000001f, 0.000001f) &&
        InRange(m[4], -0.000001f, 0.000001f) &&
        InRange(m[5], 0.999999f, 1.000001f) &&
        InRange(m[6], -0.000001f, 0.000001f) &&
        InRange(m[7], -0.000001f, 0.000001f) &&
        InRange(m[8], -0.000001f, 0.000001f) &&
        InRange(m[9], -0.000001f, 0.000001f) &&
        InRange(m[10], 0.999999f, 1.000001f) &&
        InRange(m[11], -0.000001f, 0.000001f) &&
        InRange(m[12], -0.000001f, 0.000001f) &&
        InRange(m[13], -0.000001f, 0.000001f) &&
        InRange(m[14], -0.000001f, 0.000001f) &&
        InRange(m[15], 0.999999f, 1.000001f)) {
        arg0->f12 = 1;
    } else {
        arg0->f12 = 0;
    }
    igMatrix44f_Copy((float *)((char *)arg0 + 28), (const float *)m);
    igMatrix44f_Copy((float *)((char *)arg0 + 92), (const float *)arg2);
    arg0->f13 = 1;
}

void igVertexBlendMatrixListAttr_apply(struct S_141e10 *arg0, igPsx2VisualContext *arg1) {
    int i;
    int n;
    n = arg0->f24->n;
    if (arg0->f13 == 0) {
        FUN_001419f0((TransformPairView *)arg0, (float *)((char *)arg0 + 0x1C), (void *)((char *)arg0 + 0x5C));
    }
    if (arg0->f16 == 0 && n > 0) {
        arg0->f16 = (int)igObject_MallocAligned((igObject *)arg0, n << 6, 0x10);
        arg0->f20 = n;
    }
    if (arg0->f12 == 0) {
        for (i = 0; i < n; i++) {
            int o = arg0->f24->d[i];
            igMatrix44f_Multiply((float *)(arg0->f16 + (i << 6)), (const float *)((char *)arg0 + 0x1C), (const float *)(o + DAT_00562bc8[0]->f8));
        }
    } else {
        for (i = 0; i < n; i++) {
            int o = arg0->f24->d[i];
            igMatrix44f_Copy((float *)(arg0->f16 + (i << 6)), (const float *)(o + DAT_00562bc8[0]->f8));
        }
    }
    igPsx2VisualContext_SetBlendingMatrices(arg1, n, arg0->f16);
}

/* Empty default virtual (slot 26): does nothing and leaves the receiver untouched. */
void igVertexBlendMatrixListAttr_SynchronizeDefault(void) {
}

void igVertexBlendMatrixListAttr_ReleaseDefaults(void *arg0) {
    igObject_FreeMemory((igObject *)arg0, (void *)(*(int *)((char *)arg0 + 16)));
    igObject_ReleaseDefaults((igObject *)arg0);
}

