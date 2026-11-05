/* 0x0013c540
 * Empty override of igAttr slot 26 (+0x68): does nothing.  Other attributes use this
 * slot for a per-attribute step (igLightAttr resets its light id, igTimeAttr copies
 * a time from a source object); the blend-matrix palette has none. */
void Gap__Core__igBlendMatrixPaletteAttr__vfunc_26(void) {

}
