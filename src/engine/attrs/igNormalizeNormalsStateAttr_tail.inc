void igNormalizeNormalsStateAttr_apply(int arg0, igPsx2VisualContext *arg1) {
    igPsx2VisualContext_SetNormalizeNormalsState(arg1, *(unsigned char *)((char *)(arg0) + 12));
}

void igNormalizeNormalsStateAttr_SynchronizeDefault(void *arg0, void **arg1) {
    *(unsigned char *)((char *)(arg0) + 12) = ((DW4VC_456_0 *)(arg1))->vX();
}

