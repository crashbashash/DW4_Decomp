void igGeometryMaskAttr_apply(igGeometryMaskAttr *self, igPsx2VisualContext *arg1) {
    int sp1C;

    sp1C = self->_mask;
    igPsx2VisualContext_SetVertexMask(arg1, &sp1C);
}

void igGeometryMaskAttr_SynchronizeDefault(igGeometryMaskAttr *self, void **source) {
    MaskValue mask;

    mask = ((MaskSourceVtable *)(source))->getMask();
    self->_mask = mask.word;
}

