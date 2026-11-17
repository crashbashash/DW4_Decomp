int Gap__Attrs__igTexGenMatrixAttr__vfunc_22(void) {
    return (int)g_igTexGenMatrixAttr_metaObject;
}

void Gap__Attrs__igTexGenMatrixAttr__vfunc_32(igTexGenMatrixAttr *self, const float *matrix) {
    igMatrix44f_Copy(self->m, matrix);
}

