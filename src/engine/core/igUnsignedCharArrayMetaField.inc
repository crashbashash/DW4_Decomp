void igUnsignedCharArrayMetaField_Create(int pool) {
    igUnsignedCharArrayMetaField_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585770), (igMemoryPoolView *)pool);
}

igMetaObject *igUnsignedCharArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedCharArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igUnsignedCharArrayMetaField_EnsureRegistered();
    return g_igUnsignedCharArrayMetaField_metaObject[0];
}

int igUnsignedCharArrayMetaField_GetVTable(void) {
    igUnsignedCharArrayMetaField field;
    int *header;
    int vtable;
    int references;
    void *text;

    igMetaField_Init((igMetaField *)&field);
    field._vtable = (int)&g_igUnsignedCharArrayMetaField_vtable[0];
    vtable = *(int *)((char *)&field + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    field._vtable = (int)&g_igMetaField_vtable[0];
    if (&field._fieldName != 0) {
        text = (void *)((char *)field._fieldName);
        if (text != 0) {
            header = (int *)((char *)text - 8);
            references = *(int *)((char *)(text) - 4) - 1;
            *(int *)((char *)(text) - 4) = references;
            if (references == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (int)header);
            }
        }
    }
    return vtable;
}

void igUnsignedCharArrayMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igUnsignedCharArrayMetaField_Register);
}

void igUnsignedCharArrayMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igUnsignedCharArrayMetaField_metaObject,
        (igMetaObjectRegisterFunction)igUnsignedCharMetaField_Register,
        igUnsignedCharMetaField_GetPublishedMetaObject,
        igUnsignedCharArrayMetaField_GetMetaObjectFunction,
        igUnsignedCharArrayMetaField_className,
        0x38,
        igUnsignedCharArrayMetaField_GetVTable,
        igUnsignedCharArrayMetaField_InitFields,
        0,
        (igMetaObjectCallback *)g_igUnsignedCharArrayMetaField_callbackList
    );
}

void igUnsignedCharArrayMetaField_GetMetaObjectFunction(void) {
    igUnsignedCharArrayMetaField_GetMetaObject();
}

igMetaObject *igUnsignedCharMetaField_GetPublishedMetaObject(void) {
    return g_igUnsignedCharMetaField_metaObject[0];
}

void igUnsignedCharArrayMetaField_InitFields(void) {
    int first;
    void *meta;

    meta = (void *)g_igUnsignedCharArrayMetaField_metaObject[0];
    first = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igUnsignedCharArrayMetaField_ctorTable[0], 1);
    igIntMetaField_SetDefault((void **)(igMetaObject_GetFieldAt((igMetaObject *)meta, first)), 1);
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igUnsignedCharArrayMetaField_fieldTable[0], (igMetaField ***)&g_igUnsignedCharArrayMetaField_fieldDescriptors[0], &g_igUnsignedCharArrayMetaField_fieldOffsets[0], first);
}

void igUnsignedCharArrayMetaField_CreateDefaultDescriptor(void) {
    igUnsignedCharArrayMetaField *descriptor;
    igUnsignedCharArrayMetaField *held;

    if (g_igUnsignedCharArrayMetaField_descriptor[0] == 0) {
        g_igUnsignedCharArrayMetaField_descriptor[0] = (igUnsignedCharArrayMetaField *)(((void *)igMetaObject_CreateInstance((igMetaObject *)g_igUnsignedCharArrayMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))))));
        descriptor = g_igUnsignedCharArrayMetaField_descriptor[0];
        if (descriptor != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)descriptor);
            held = g_igUnsignedCharArrayMetaField_descriptor[0];
            held->_refCount = held->_refCount - 1;
            if ((held->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(held);
            }
            g_igUnsignedCharArrayMetaField_descriptor[0]->_internalIndex = igMetaField_GetMetaFieldList()->_count - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)g_igUnsignedCharArrayMetaField_descriptor[0]);
        }
    }
}

