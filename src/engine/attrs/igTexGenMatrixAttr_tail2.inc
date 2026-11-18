int igTexGenMatrixAttr_GetMeta(void) {
    return (int)g_igTexGenMatrixAttr_metaObject;
}

void igTexGenMatrixAttr_SetMatrix(igTexGenMatrixAttr *self, const float *matrix) {
    igMatrix44f_Copy(self->m, matrix);
}

