void igClearAttr_apply(void *arg0, igPsx2VisualContext *arg1) {
    int temp_a1;

    igPsx2VisualContext_SetClearDepth(arg1, *(float *)((char *)(arg0) + 64));
    igPsx2VisualContext_SetClearColorPacked(arg1, *(int *)((char *)(arg0) + 60));
    igPsx2VisualContext_SetClearStencil(arg1, *(int *)((char *)(arg0) + 56));
    temp_a1 = *(int *)((char *)(arg0) + 12);
    if (temp_a1 != 0) {
        igPsx2VisualContext_ClearRenderDestination(arg1, temp_a1);
    }
}

void igClearAttr_SynchronizeDefault(void *arg0, void **arg1) {
    float temp_f0;

    *(int *)((char *)(arg0) + 56) = ((DW4VC_736_0 *)(arg1))->vX();
    temp_f0 = ((DW4VC_728_0 *)(arg1))->vX();
    *(double *)((char *)(arg0) + 48) = fptodp(temp_f0);
    *(float *)((char *)(arg0) + 64) = temp_f0;
    *(int *)((char *)(arg0) + 60) = ((DW4VC_720_0 *)(arg1))->vX();
}

void igClearAttr_InitDefaults(void *arg0) {
    igObject_InitDefaults((igObject *)arg0);
    *(int *)((char *)(arg0) + 60) = igVec4f_PackColor((const float *)((char *)arg0 + 0x10), 1);
    *(float *)((char *)(arg0) + 64) = dptofp(*(double *)((char *)(arg0) + 48));
}

void igClearAttr_UserPostLoad(void *arg0) {
    igAttr_UserPostLoad(arg0);
    *(int *)((char *)(arg0) + 60) = igVec4f_PackColor((const float *)((char *)arg0 + 0x10), 1);
    *(float *)((char *)(arg0) + 64) = dptofp(*(double *)((char *)(arg0) + 48));
}

