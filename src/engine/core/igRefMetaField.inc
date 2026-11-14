igMetaObject *igRefMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igRefMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igRefMetaField_EnsureRegistered();
    return g_igRefMetaField_metaObject[0];
}

void igRefMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igRefMetaField_Register);
}

void igRefMetaField_Register(void) {
    igMetaObject_RegisterClass(
        1, /* abstract */
        ((char *)g_igRefMetaField_metaObject),
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        igRefMetaField_GetMetaObjectFunction,
        igRefMetaField_className,
        0x38, /* instance size */
        0,
        &igRefMetaField_InitFields,
        0, /* extra callback item */
        g_igRefMetaField_callbackList /* callback list */
    );
}

void igRefMetaField_GetMetaObjectFunction(void) {
    igRefMetaField_GetMetaObject();
}

void igRefMetaField_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igRefMetaField_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igRefMetaField_ctorTable[0], 2);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igRefMetaField_fieldTable[0], (igMetaField ***)&DAT_004bf970[0], &DAT_004bf978[0], temp_s1);
}

void igRefMetaField_CreateDefaultDescriptor(void) {
    void *temp_s0;
    igRefMetaField *o;
    int t;

    if (g_igRefMetaField_descriptor[0] == 0) {
        g_igRefMetaField_descriptor[0] = (void *)(((void *)igMetaObject_CreateInstance((igMetaObject *)g_igRefMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))))));
        temp_s0 = (void *)(g_igRefMetaField_descriptor[0]);
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)temp_s0);
            o = (igRefMetaField *)g_igRefMetaField_descriptor[0];
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
            t = ((__internalObjectList *)igMetaField_GetMetaFieldList())->_count - 1;
            ((igRefMetaField *)g_igRefMetaField_descriptor[0])->_internalIndex = (short) t;
            igMetaField_FinalizeDescriptor((igMetaField *)g_igRefMetaField_descriptor[0]);
        }
    }
}

