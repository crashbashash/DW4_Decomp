void Gap__Attrs__igGeometryMaskAttr__vfunc_24(void *arg0, int arg1) {
    int sp1C;

    sp1C = *(int *)((char *)arg0 + 12);
    Gap__Gfx__igPsx2VisualContext__vfunc_69(arg1, &sp1C);
}

void Gap__Attrs__igGeometryMaskAttr__vfunc_26(igGeometryMaskAttr *self, void **source) {
    MaskValue mask;

    mask = ((MaskSourceVtable *)(source))->getMask();
    self->_mask = mask.word;
}

