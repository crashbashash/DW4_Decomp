void Gap__Attrs__igCullFaceAttr__vfunc_26(igCullFaceAttr *self, igCullFaceAttr *source) {
    ((DW4VC_132_1_13ca60 *)(self))->vX((int)(((DW4VC_920_0 *)(source))->vX()));
    ((DW4VC_128_1 *)(self))->vX((int)(((DW4VC_928_0 *)(source))->vX()));
}

/* Setter for the cull mode (`_mode`, +16); slot 33 is the matching `_enabled` setter. */

void Gap__Attrs__igCullFaceAttr__vfunc_32(igCullFaceAttr *self, int mode) {
    self->_mode = mode;
}

/* Setter: stores the cull-face enable flag (`_enabled`, an igBoolMetaField of the reflected
 * igCullFaceAttr). */
void Gap__Attrs__igCullFaceAttr__vfunc_33(igCullFaceAttr *self, char enabled) {
    self->_enabled = enabled;
}

void Gap__Attrs__igCullFaceAttr__vfunc_24(char *arg0, int arg1) {
    Gap__Gfx__igPsx2VisualContext__vfunc_229(arg1, *(unsigned char *)(arg0 + 12));
    Gap__Gfx__igPsx2VisualContext__vfunc_231(arg1, *(int *)(arg0 + 16));
}

