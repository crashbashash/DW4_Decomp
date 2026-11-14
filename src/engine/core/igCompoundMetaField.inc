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
        1,
        g_igCompoundMetaField_metaObject,
        (igMetaObjectRegisterFunction)igMetaField_Register,
        (igMetaObjectGetFunction)igMetaField_GetPublishedMetaObject,
        igCompoundMetaField_GetMetaObjectFunction,
        igCompoundMetaField_className,
        0x38,
        0,
        igCompoundMetaField_InitFields,
        0,
        (igMetaObjectCallback *)g_igCompoundMetaField_callbackList
    );
}

void igCompoundMetaField_GetMetaObjectFunction(void) {
    igCompoundMetaField_GetMetaObject();
}

void igCompoundMetaField_InitFields(void) {
    int first;
    void *field;
    void *meta;

    meta = (void *)g_igCompoundMetaField_metaObject[0];
    first = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igCompoundMetaField_ctorTable[0], 1);
    field = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first)));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igMetaFieldList_GetOrCreateMetaObject();
    ((igRefMetaField *)field)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igCompoundMetaField_fieldTable[0], (igMetaField ***)&g_igCompoundMetaField_fieldDescriptors[0], &g_igCompoundMetaField_fieldOffsets[0], first);
}

void igCompoundMetaField_CreateDefaultDescriptor(void) {
    void *descriptor;
    igCompoundMetaField *o;
    int t;

    if (g_igCompoundMetaField_descriptor[0] == 0) {
        g_igCompoundMetaField_descriptor[0] = (void *)(((void *)igMetaObject_CreateInstance((igMetaObject *)g_igCompoundMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))))));
        descriptor = (void *)(g_igCompoundMetaField_descriptor[0]);
        if (descriptor != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)descriptor);
            o = (igCompoundMetaField *)g_igCompoundMetaField_descriptor[0];
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
            t = igMetaField_GetMetaFieldList()->_count - 1;
            ((igCompoundMetaField *)g_igCompoundMetaField_descriptor[0])->_internalIndex = (short) t;
            igMetaField_FinalizeDescriptor((igMetaField *)g_igCompoundMetaField_descriptor[0]);
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

