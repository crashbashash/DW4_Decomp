igMetaObject *igCompoundMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igCompoundMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igCompoundMetaField_EnsureRegistered();
    return g_igCompoundMetaField_metaObject[0];
}

void igCompoundMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igCompoundMetaField_Register);
}

void igCompoundMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        ((char *)g_igCompoundMetaField_metaObject),
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        igCompoundMetaField_GetMetaObjectFunction,
        igCompoundMetaField_className,
        0x38, /* instance size */
        0,
        &igCompoundMetaField_InitFields,
        0, /* extra callback item */
        g_igCompoundMetaField_callbackList /* callback list */
    );
}

void igCompoundMetaField_GetMetaObjectFunction(void) {
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
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igMetaFieldList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igCompoundMetaField_fieldTable[0], (igMetaField ***)&DAT_004c14d8[0], &DAT_004c14e0[0], temp_s2);
}

void igCompoundMetaField_CreateDefaultDescriptor(void) {
    void *temp_s0;
    igCompoundMetaField *o;
    int t;

    if (DAT_00586920[0] == 0) {
        DAT_00586920[0] = (void *)(((void *)igMetaObject_CreateInstance((igMetaObject *)g_igCompoundMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))))));
        temp_s0 = (void *)(DAT_00586920[0]);
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)temp_s0);
            o = (igCompoundMetaField *)DAT_00586920[0];
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
            t = *(int *)((char *)(((void *)igMetaField_GetMetaFieldList())) + 12) - 1;
            ((igCompoundMetaField *)DAT_00586920[0])->_internalIndex = (short) t;
            igMetaField_FinalizeDescriptor((igMetaField *)DAT_00586920[0]);
        }
    }
}

int igCompoundMetaField_GetSize(void) {
    return 1;
}

void igCompoundMetaField_InitDefaults(igCompoundMetaField *self)
{
    igCompoundMetaField_AddSubFields(self->_fieldList);
}

void igCompoundMetaField_AddSubFields(int value)
{
}

