void igColorAttr_InitDefaults(void *arg0) {
    igObject_InitDefaults((igObject *)arg0);
    *(int *)((char *)(arg0) + 28) = igVec4f_PackColor((const float *)((char *)arg0 + 0xC), 1);
}

void igColorAttr_UserPostLoad(void *arg0) {
    igAttr_UserPostLoad(arg0);
    *(int *)((char *)(arg0) + 28) = igVec4f_PackColor((const float *)((char *)arg0 + 0xC), 1);
}

void igColorAttr_apply(int arg0, igPsx2VisualContext *arg1) {
    igPsx2VisualContext_SetColorPacked(arg1, *(unsigned int *)((char *)(arg0) + 28));
}

void igColorAttr_SynchronizeDefault(void *arg0, void **arg1) {
    *(int *)((char *)(arg0) + 28) = ((DW4VC_272_0 *)(arg1))->vX();
}

void igColorAttr_SynchronizeColorPacked(void *arg0) {
    *(int *)((char *)(arg0) + 28) = igVec4f_PackColor((const float *)((char *)arg0 + 0xC), 1);
}

