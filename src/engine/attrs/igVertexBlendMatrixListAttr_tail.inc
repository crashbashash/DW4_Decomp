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
    igMatrix44f_Copy((char *)arg0 + 28, m);
    igMatrix44f_Copy((char *)arg0 + 92, arg2);
    arg0->f13 = 1;
}

void Gap__Attrs__igVertexBlendMatrixListAttr__vfunc_24(struct S_141e10 *arg0, int arg1) {
    int i;
    int n;
    n = arg0->f24->n;
    if (arg0->f13 == 0) {
        FUN_001419f0((TransformPairView *)arg0, (float *)((char *)arg0 + 0x1C), (void *)((char *)arg0 + 0x5C));
    }
    if (arg0->f16 == 0 && n > 0) {
        arg0->f16 = igObject_MallocAligned(arg0, n << 6, 0x10);
        arg0->f20 = n;
    }
    if (arg0->f12 == 0) {
        for (i = 0; i < n; i++) {
            int o = arg0->f24->d[i];
            FUN_001904f0(arg0->f16 + (i << 6), (char *)arg0 + 0x1C, o + DAT_00562bc8[0]->f8);
        }
    } else {
        for (i = 0; i < n; i++) {
            int o = arg0->f24->d[i];
            igMatrix44f_Copy(arg0->f16 + (i << 6), o + DAT_00562bc8[0]->f8);
        }
    }
    Gap__Gfx__igPsx2VisualContext__vfunc_197(arg1, n, arg0->f16);
}

/* Empty default virtual (slot 26): does nothing and leaves the receiver untouched. */
void Gap__Attrs__igVertexBlendMatrixListAttr__vfunc_26(void) {
}

void Gap__Attrs__igVertexBlendMatrixListAttr__vfunc_12(void *arg0) {
    igObject_FreeMemory(arg0, *(int *)((char *)arg0 + 16));
    igObject_ReleaseDefaults(arg0);
}

