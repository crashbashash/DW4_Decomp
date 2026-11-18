void igBlendMatrixPaletteAttr_apply(struct S_13c520 *arg0, igPsx2VisualContext *arg1) {
    igPsx2VisualContext_SetBlendingMatrices(arg1, arg0->b, arg0->a);
}

/* Empty override of igAttr slot 26 (+0x68). Other attributes use this slot for a per-attribute
 * step (igLightAttr resets its light id, igTimeAttr copies a time from a source object); the
 * blend-matrix palette has none. */
void igBlendMatrixPaletteAttr_SynchronizeDefault(void) {

}

