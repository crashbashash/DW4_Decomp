void Gap__Attrs__igLightingStateAttr__vfunc_24(int arg0, int arg1) {
    Gap__Gfx__igPsx2VisualContext__vfunc_75(arg1, *(unsigned char *)((char *)(arg0) + 12));
}

void Gap__Attrs__igLightingStateAttr__vfunc_26(void **arg0, void **arg1) {
    ((DW4VC_128_1 *)(arg0))->vX((int)(((DW4VC_304_0 *)(arg1))->vX()));
}

/* Setter for the attribute's reflected _enabled flag; lighting off means unlit geometry. */
void Gap__Attrs__igLightingStateAttr__vfunc_32(igLightingStateAttr *self, char enabled) {
    self->_enabled = enabled;
}

