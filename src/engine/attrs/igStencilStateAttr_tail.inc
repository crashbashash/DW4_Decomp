void igStencilStateAttr_apply(int arg0, igPsx2VisualContext *arg1) {
    igPsx2VisualContext_SetStencilState(arg1, *(bool *)((char *)(arg0) + 12));
}

void igStencilStateAttr_SynchronizeDefault(void **arg0, void **arg1) {
    ((DW4VC_128_1 *)(arg0))->vX((int)(((DW4VC_640_0 *)(arg1))->vX()));
}

void igStencilStateAttr_SetState(void *arg0, char arg1) {
    *(char *)((char *)(arg0) + 12) = arg1;
}

