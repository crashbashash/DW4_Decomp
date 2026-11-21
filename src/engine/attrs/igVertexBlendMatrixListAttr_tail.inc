void FUN_001419f0(igVertexBlendMatrixListAttr *self, const float *m, const float *inverse) {
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
        self->_isSkeletonTransformIdentity = 1;
    } else {
        self->_isSkeletonTransformIdentity = 0;
    }
    igMatrix44f_Copy(self->_skeletonTransform, m);
    igMatrix44f_Copy(self->_skeletonInverseTransform, inverse);
    self->_isSkeletonTransformSet = 1;
}

void igVertexBlendMatrixListAttr_apply(struct S_141e10 *arg0, igPsx2VisualContext *arg1) {
    int i;
    int n;
    n = arg0->f24->n;
    if (arg0->f13 == 0) {
        FUN_001419f0((igVertexBlendMatrixListAttr *)arg0, (const float *)((char *)arg0 + 0x1C), (const float *)((char *)arg0 + 0x5C));
    }
    if (arg0->f16 == 0 && n > 0) {
        arg0->f16 = (int)((Gap::Core::igObject *)arg0)->mallocAligned(n << 6, 0x10);
        arg0->f20 = n;
    }
    if (arg0->f12 == 0) {
        for (i = 0; i < n; i++) {
            int o = arg0->f24->d[i];
            igMatrix44f_Multiply((float *)(arg0->f16 + (i << 6)), (const float *)((char *)arg0 + 0x1C), (const float *)(o + g_igMatrixObject_mMetaField->_offset));
        }
    } else {
        for (i = 0; i < n; i++) {
            int o = arg0->f24->d[i];
            igMatrix44f_Copy((float *)(arg0->f16 + (i << 6)), (const float *)(o + g_igMatrixObject_mMetaField->_offset));
        }
    }
    igPsx2VisualContext_SetBlendingMatrices(arg1, n, (igMatrix44f *)arg0->f16);
}

/* Empty default virtual (slot 26): does nothing and leaves the receiver untouched. */
void igVertexBlendMatrixListAttr_SynchronizeDefault(void) {
}

void igVertexBlendMatrixListAttr_ReleaseDefaults(igVertexBlendMatrixListAttr *self) {
    ((Gap::Core::igObject *)self)->free((void *)(self->_matrixCache));
    igObject_ReleaseDefaults((igObject *)self);
}

