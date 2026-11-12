void Gap__Attrs__igBlendStateAttr__vfunc_24(int arg0, int arg1) {
    Gap__Gfx__igPsx2VisualContext__vfunc_152(arg1, *(unsigned char *)((char *)(arg0) + 12));
}

void Gap__Attrs__igBlendStateAttr__vfunc_26(void **arg0, void **arg1) {
    ((DW4VC_128_1 *)(arg0))->vX((int)(((DW4VC_612_0 *)(arg1))->vX()));
}

/* Setter: stores the blend-state enable flag (`_enabled`, an igBoolMetaField of the reflected
 * igBlendStateAttr). */
void Gap__Attrs__igBlendStateAttr__vfunc_32(igBlendStateAttr *self, char enabled) {
    self->_enabled = enabled;
}

