igMetaObject *igCompoundMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igCompoundMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002cbd40();
    return g_igCompoundMetaField_metaObject[0];
}

void FUN_002cbd40(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igCompoundMetaField_Register);
}

void igCompoundMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1, /* abstract */
        ((char *)g_igCompoundMetaField_metaObject),
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igCompoundMetaField_GetMetaObject,
        igCompoundMetaField_className,
        0x38, /* instance size */
        0,
        &igCompoundMetaField_InitFields,
        0, /* extra callback item */
        g_igCompoundMetaField_callbackList /* callback list */
    );
}

void thunk_igCompoundMetaField_GetMetaObject(void) {
    igCompoundMetaField_GetMetaObject();
}

void igCompoundMetaField_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igCompoundMetaField_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igCompoundMetaField_ctorTable[0], 1);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_002c8b30();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igCompoundMetaField_fieldTable[0], (igMetaField ***)&DAT_004c14d8[0], &DAT_004c14e0[0], temp_s2);
}

void FUN_002cbe70(void) {
    void *temp_s0;
    igCompoundMetaField *o;
    int t;

    if (DAT_00586920[0] == 0) {
        DAT_00586920[0] = (void *)(((void *)igMetaObject_CreateInstance((igMetaObject *)g_igCompoundMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))))));
        temp_s0 = (void *)(DAT_00586920[0]);
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(FUN_002fc250(), (igObject *)temp_s0);
            o = (igCompoundMetaField *)DAT_00586920[0];
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
            t = *(int *)((char *)(((void *)FUN_002fc250())) + 12) - 1;
            ((igCompoundMetaField *)DAT_00586920[0])->_internalIndex = (short) t;
            igMetaField_FinalizeDescriptor((igMetaField *)DAT_00586920[0]);
        }
    }
}

int FUN_002cbf40(void) {
    return 1;
}

void FUN_002cbf50(igCompoundMetaField *self)
{
    FUN_002cbf60(self->_fieldList);
}

void FUN_002cbf60(int value)
{
}

