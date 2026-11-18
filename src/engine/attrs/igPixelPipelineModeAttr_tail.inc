void igPixelPipelineModeAttr_apply(int arg0, igPsx2VisualContext *arg1) {
    igPsx2VisualContext_SetPixelPipelineMode(arg1, *(int *)((char *)(arg0) + 12));
}

void igPixelPipelineModeAttr_SynchronizeDefault(void *arg0, void **arg1) {
    *(int *)((char *)(arg0) + 12) = ((DW4VC_588_0 *)(arg1))->vX();
}

/* Stores a float at +0x1c of the receiver. That offset lies past the 20 bytes the reflected
 * igPrimLengthArray1_1 describes, so the store stays an offset write. */
void igPointSpriteExt_SetSpriteSize(igPrimLengthArray1_1 *self, float value) {
    *(float *)((char *)self + 28) = value;
}

