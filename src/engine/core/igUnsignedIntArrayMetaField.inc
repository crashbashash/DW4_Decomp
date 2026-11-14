void igUnsignedIntArrayMetaField_Create(int pool) {
    igUnsignedIntArrayMetaField_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585748), (igMemoryPoolView *)pool);
}

igMetaObject *igUnsignedIntArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedIntArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igUnsignedIntArrayMetaField_EnsureRegistered();
    return g_igUnsignedIntArrayMetaField_metaObject[0];
}

int igUnsignedIntArrayMetaField_GetVTable(void) {
    igUnsignedIntArrayMetaField field;
    int result;
    char *fieldName;
    int *name;
    int *header;
    int refs;

    igUnsignedIntMetaField_Init((igMetaField *)&field);
    field._vtable = (int)&g_igUnsignedIntArrayMetaField_vtable[0];
    result = *(int *)((char *)&field + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    field._vtable = (int)&g_igMetaField_vtable[0];
    fieldName = (char *)&field._fieldName;
    if (fieldName != 0) {
        name = *(int **)fieldName;
        if (name != 0) {
            header = name - 2;
            refs = name[-1] - 1;
            name[-1] = refs;
            if (refs == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (int)header);
            }
        }
    }
    return result;
}

void igUnsignedIntArrayMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igUnsignedIntArrayMetaField_Register);
}

void igUnsignedIntArrayMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igUnsignedIntArrayMetaField_metaObject,
        (igMetaObjectRegisterFunction)igUnsignedIntMetaField_Register,
        igUnsignedIntMetaField_GetPublishedMetaObject,
        igUnsignedIntArrayMetaField_GetMetaObjectFunction,
        igUnsignedIntArrayMetaField_className,
        0x38,
        igUnsignedIntArrayMetaField_GetVTable,
        igUnsignedIntArrayMetaField_InitFields,
        0,
        (igMetaObjectCallback *)g_igUnsignedIntArrayMetaField_callbackList
    );
}

void igUnsignedIntArrayMetaField_GetMetaObjectFunction(void) {
    igUnsignedIntArrayMetaField_GetMetaObject();
}

igMetaObject *igUnsignedIntMetaField_GetPublishedMetaObject(void) {
    return g_igUnsignedIntMetaField_metaObject[0];
}

void igUnsignedIntArrayMetaField_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_igUnsignedIntArrayMetaField_metaObject[0];
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igUnsignedIntArrayMetaField_ctorTable[0], 1);
    igIntMetaField_SetDefault((void **)(igMetaObject_GetFieldAt((igMetaObject *)meta, base)), 1);
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igUnsignedIntArrayMetaField_fieldTable[0], (igMetaField ***)&g_igUnsignedIntArrayMetaField_fieldDescriptors[0], &g_igUnsignedIntArrayMetaField_fieldOffsets[0], base);
}

void igUnsignedIntArrayMetaField_CreateDefaultDescriptor(void) {
    igUnsignedIntArrayMetaField *descriptor;
    igUnsignedIntArrayMetaField *p;

    if (g_igUnsignedIntArrayMetaField_descriptor[0] == 0) {
        g_igUnsignedIntArrayMetaField_descriptor[0] = ((igUnsignedIntArrayMetaField *)igMetaObject_CreateInstance((igMetaObject *)g_igUnsignedIntArrayMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
        descriptor = g_igUnsignedIntArrayMetaField_descriptor[0];
        if (descriptor != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)descriptor);
            p = g_igUnsignedIntArrayMetaField_descriptor[0];
            p->_refCount = p->_refCount - 1;
            if (((unsigned long long) ((long long)(int)p->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
            ((igMetaField *)g_igUnsignedIntArrayMetaField_descriptor[0])->_internalIndex = (short) (igMetaField_GetMetaFieldList()->_count - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)g_igUnsignedIntArrayMetaField_descriptor[0]);
        }
    }
}

