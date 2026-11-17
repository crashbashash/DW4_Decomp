void Gap__Attrs__igProjectionMatrixAttr__vfunc_24(char * arg0, igPsx2VisualContext *arg1) {
    Gap__Gfx__igPsx2VisualContext__vfunc_203(arg1, 0, (char *)(arg0 + 12));
}

void Gap__Attrs__igProjectionMatrixAttr__vfunc_26(igProjectionMatrixAttr *self, igObject *context)
{
    float m[16];

    igMatrix44f_SetIdentity(m);
    ((VisualContextMatrixSlots *)context)->getMatrix(0, m);
    ((MatrixAttrSlots *)self)->setMatrix(m);
}

void Gap__Attrs__igProjectionMatrixAttr__vfunc_32(igProjectionMatrixAttr *self, const float *matrix) {
    igMatrix44f_Copy(self->_m, matrix);
}

