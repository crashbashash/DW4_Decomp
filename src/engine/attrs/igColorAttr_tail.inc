void igColorAttr_InitDefaults(igColorAttr *self) {
    igObject_InitDefaults((igObject *)self);
    self->_colorPacked = igVec4f_PackColor((const float *)((char *)self + 0xC), 1);
}

void igColorAttr_UserPostLoad(igColorAttr *self) {
    igAttr_UserPostLoad(self);
    self->_colorPacked = igVec4f_PackColor((const float *)((char *)self + 0xC), 1);
}

void igColorAttr_apply(igColorAttr *self, igPsx2VisualContext *arg1) {
    igPsx2VisualContext_SetColorPacked(arg1, self->_colorPacked);
}

void igColorAttr_SynchronizeDefault(igColorAttr *self, void **arg1) {
    self->_colorPacked = ((DW4VC_272_0 *)(arg1))->vX();
}

void igColorAttr_SynchronizeColorPacked(igColorAttr *self) {
    self->_colorPacked = igVec4f_PackColor((const float *)((char *)self + 0xC), 1);
}

