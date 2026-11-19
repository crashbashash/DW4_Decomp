void igCullFaceAttr_SynchronizeDefault(igCullFaceAttr *self, igCullFaceAttr *source) {
    ((DW4VC_132_1_13ca60 *)(self))->vX((int)(((DW4VC_920_0 *)(source))->vX()));
    ((DW4VC_128_1 *)(self))->vX((int)(((DW4VC_928_0 *)(source))->vX()));
}

/* Setter for the cull mode (`_mode`, +16); slot 33 is the matching `_enabled` setter. */

void igCullFaceAttr_SetMode(igCullFaceAttr *self, int mode) {
    self->_mode = mode;
}

/* Setter: stores the cull-face enable flag (`_enabled`, an igBoolMetaField of the reflected
 * igCullFaceAttr). */
void igCullFaceAttr_SetState(igCullFaceAttr *self, char enabled) {
    self->_enabled = enabled;
}

void igCullFaceAttr_apply(igCullFaceAttr *self, igPsx2VisualContext *arg1) {
    igPsx2VisualContext_SetCullFaceState(arg1, *(bool *)&self->_enabled);
    igPsx2VisualContext_SetCullFaceMode(arg1, self->_mode);
}

