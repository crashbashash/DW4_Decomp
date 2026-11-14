void igCharArrayMetaField_Create(int allocator) {
    igCharArrayMetaField_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x586940), (igMemoryPoolView *)allocator);
}

igMetaObject *igCharArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igCharArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igCharArrayMetaField_EnsureRegistered();
    return g_igCharArrayMetaField_metaObject[0];
}

int igCharArrayMetaField_GetVTable(void) {
    igCharArrayMetaField o;
    int r;
    int *header;
    int count;
    void *text;

    igCharMetaField_Init((int **)&o);
    o._vtable = (int)&g_igCharArrayMetaField_vtable[0];
    r = *(int *)((char *)&o + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    o._vtable = (int)&g_igMetaField_vtable[0];
    if (&o._fieldName != 0) {
        text = (char *)o._fieldName;
        if (text != 0) {
            header = (int *)((char *)text - 8);
            count = *(int *)((char *)(text) - 4) - 1;
            *(int *)((char *)(text) - 4) = count;
            if (count == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (int)header);
            }
        }
    }
    return r;
}

void igCharArrayMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igCharArrayMetaField_Register);
}

void igCharArrayMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igCharArrayMetaField_metaObject,
        (igMetaObjectRegisterFunction)igCharMetaField_Register,
        igCharMetaField_GetPublishedMetaObject,
        igCharArrayMetaField_GetMetaObjectFunction,
        igCharArrayMetaField_className,
        0x38,
        igCharArrayMetaField_GetVTable,
        igCharArrayMetaField_InitFields,
        0,
        (igMetaObjectCallback *)g_igCharArrayMetaField_callbackList
    );
}

void igCharArrayMetaField_GetMetaObjectFunction(void) {
    igCharArrayMetaField_GetMetaObject();
}

igMetaObject *igCharMetaField_GetPublishedMetaObject(void) {
    return g_igCharMetaField_metaObject[0];
}

void igCharArrayMetaField_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_igCharArrayMetaField_metaObject[0];
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igCharArrayMetaField_ctorTable[0], 1);
    igIntMetaField_SetDefault((void **)(igMetaObject_GetFieldAt((igMetaObject *)meta, base)), 1);
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igCharArrayMetaField_fieldTable[0], (igMetaField ***)&g_igCharArrayMetaField_fieldDescriptors[0], &g_igCharArrayMetaField_fieldOffsets[0], base);
}

void igCharArrayMetaField_CreateDefaultDescriptor(void) {
    igCharArrayMetaField *descriptor;
    igCharArrayMetaField *held;

    if (g_igCharArrayMetaField_descriptor[0] == 0) {
        g_igCharArrayMetaField_descriptor[0] = ((igCharArrayMetaField *)igMetaObject_CreateInstance((igMetaObject *)g_igCharArrayMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
        descriptor = g_igCharArrayMetaField_descriptor[0];
        if (descriptor != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)descriptor);
            held = g_igCharArrayMetaField_descriptor[0];
            held->_refCount -= 1;
            if ((held->_refCount & 0x7fffff) == 0) {
                igObject_Destroy(held);
            }
            g_igCharArrayMetaField_descriptor[0]->_internalIndex = igMetaField_GetMetaFieldList()->_count - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)g_igCharArrayMetaField_descriptor[0]);
        }
    }
}

