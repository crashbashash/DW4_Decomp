void igProjectionMatrixAttr_apply(char * arg0, igPsx2VisualContext *arg1) {
    igPsx2VisualContext_SetMatrix(arg1, 0, (char *)(arg0 + 12));
}

void igProjectionMatrixAttr_SynchronizeDefault(igProjectionMatrixAttr *self, igObject *context)
{
    float m[16];

    igMatrix44f_SetIdentity(m);
    ((VisualContextMatrixSlots *)context)->getMatrix(0, m);
    ((MatrixAttrSlots *)self)->setMatrix(m);
}

void igProjectionMatrixAttr_SetMatrix(igProjectionMatrixAttr *self, const float *matrix) {
    igMatrix44f_Copy(self->_m, matrix);
}

