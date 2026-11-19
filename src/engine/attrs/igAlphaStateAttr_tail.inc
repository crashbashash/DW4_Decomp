void igAlphaStateAttr_apply(igAlphaStateAttr *self, igPsx2VisualContext *arg1) {
    igPsx2VisualContext_SetAlphaTestState(arg1, self->_enabled);
}

void igAlphaStateAttr_SynchronizeDefault(void **arg0, void **arg1) {
    ((DW4VC_128_1 *)(arg0))->vX((int)(((DW4VC_872_0 *)(arg1))->vX()));
}

void igAlphaStateAttr_SetState(igAlphaStateAttr *self, char arg1) {
    self->_enabled = arg1;
}

void FUN_0013b800(void)
{
}

void igAttr_SetUnitID(int a0, int a1)
{
    *(short *)((char *)a0 + 10) = a1;
}

void igAttr_UserPostLoad(void *a) {
    igObject_UserPostLoad();
    ((short *)a)[5] = 0;
    ((short *)a)[4] = (((VC *)a)->vX())[2];
}

void igAttr_resetFields(void *p, int flags)
{
    Gap__Core__igObject__resetFields((igObject *)p, flags);
    int t = ((A *)p)->v20()->f;
    ((short *)p)[4] = (short)t;
}

void igAttr_RegisterClass(igMetaObject *meta) {
    short temp_a0;

    if ((igMetaObject_IsOfType(meta, igAttr_GetMetaObject()) != 0) && (meta->_abstractState == 0)) {
        temp_a0 = g_igAttr_nextAttrIndex;
        g_igAttr_nextAttrIndex = temp_a0 + 1;
        meta->_id = (int)((int) temp_a0);
    }
}

