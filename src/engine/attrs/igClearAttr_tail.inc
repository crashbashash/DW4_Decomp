void igClearAttr_apply(igClearAttr *self, igPsx2VisualContext *arg1) {
    int temp_a1;

    igPsx2VisualContext_SetClearDepth(arg1, self->_depthF);
    igPsx2VisualContext_SetClearColorPacked(arg1, self->_colorPacked);
    igPsx2VisualContext_SetClearStencil(arg1, self->_stencil);
    temp_a1 = self->_clearMode;
    if (temp_a1 != 0) {
        igPsx2VisualContext_ClearRenderDestination(arg1, temp_a1);
    }
}

void igClearAttr_SynchronizeDefault(igClearAttr *self, void **arg1) {
    float temp_f0;

    self->_stencil = ((DW4VC_736_0 *)(arg1))->vX();
    temp_f0 = ((DW4VC_728_0 *)(arg1))->vX();
    self->_depth = fptodp(temp_f0);
    self->_depthF = temp_f0;
    self->_colorPacked = ((DW4VC_720_0 *)(arg1))->vX();
}

void igClearAttr_InitDefaults(igClearAttr *self) {
    igObject_InitDefaults((igObject *)self);
    self->_colorPacked = igVec4f_PackColor((const float *)((char *)self + 0x10), 1);
    self->_depthF = dptofp(self->_depth);
}

void igClearAttr_UserPostLoad(igClearAttr *self) {
    igAttr_UserPostLoad(self);
    self->_colorPacked = igVec4f_PackColor((const float *)((char *)self + 0x10), 1);
    self->_depthF = dptofp(self->_depth);
}

