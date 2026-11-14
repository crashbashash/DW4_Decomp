void igUnsignedShortArrayMetaField_Create(int allocator) {
    igUnsignedShortArrayMetaField_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x5856F8), (igMemoryPoolView *)allocator);
}

igMetaObject *igUnsignedShortArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedShortArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igUnsignedShortArrayMetaField_EnsureRegistered();
    return g_igUnsignedShortArrayMetaField_metaObject[0];
}

int igUnsignedShortArrayMetaField_GetVTable(void) {
    igUnsignedShortArrayMetaField o;
    int r;
    int *header;
    int count;
    void *name;

    igUnsignedShortMetaField_Init((int **)&o);
    o._vtable = (int)&g_igUnsignedShortArrayMetaField_vtable[0];
    r = *(int *)((char *)&o + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    o._vtable = (int)&g_igMetaField_vtable[0];
    if (&o._fieldName != 0) {
        name = (char *)o._fieldName;
        if (name != 0) {
            header = (int *)((char *)name - 8);
            count = *(int *)((char *)(name) - 4) - 1;
            *(int *)((char *)(name) - 4) = count;
            if (count == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (int)header);
            }
        }
    }
    return r;
}

void igUnsignedShortArrayMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igUnsignedShortArrayMetaField_Register);
}

void igUnsignedShortArrayMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igUnsignedShortArrayMetaField_metaObject,
        (igMetaObjectRegisterFunction)igUnsignedShortMetaField_Register,
        igUnsignedShortMetaField_GetPublishedMetaObject,
        igUnsignedShortArrayMetaField_GetMetaObjectFunction,
        igUnsignedShortArrayMetaField_className,
        0x38,
        igUnsignedShortArrayMetaField_GetVTable,
        igUnsignedShortArrayMetaField_InitFields,
        0,
        (igMetaObjectCallback *)g_igUnsignedShortArrayMetaField_callbackList
    );
}

void igUnsignedShortArrayMetaField_GetMetaObjectFunction(void) {
    igUnsignedShortArrayMetaField_GetMetaObject();
}

igMetaObject *igUnsignedShortMetaField_GetPublishedMetaObject(void) {
    return g_igUnsignedShortMetaField_metaObject[0];
}

void igUnsignedShortArrayMetaField_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_igUnsignedShortArrayMetaField_metaObject[0];
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igUnsignedShortArrayMetaField_ctorTable[0], 1);
    igIntMetaField_SetDefault((void **)(igMetaObject_GetFieldAt((igMetaObject *)meta, base)), 1);
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igUnsignedShortArrayMetaField_fieldTable[0], (igMetaField ***)&g_igUnsignedShortArrayMetaField_fieldDescriptors[0], &g_igUnsignedShortArrayMetaField_fieldOffsets[0], base);
}

void igUnsignedShortArrayMetaField_CreateDefaultDescriptor(void) {
    igUnsignedShortArrayMetaField *descriptor;
    igUnsignedShortArrayMetaField *p;

    if (g_igUnsignedShortArrayMetaField_descriptor[0] == 0) {
        g_igUnsignedShortArrayMetaField_descriptor[0] = ((igUnsignedShortArrayMetaField *)igMetaObject_CreateInstance((igMetaObject *)g_igUnsignedShortArrayMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
        descriptor = g_igUnsignedShortArrayMetaField_descriptor[0];
        if (descriptor != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)descriptor);
            p = g_igUnsignedShortArrayMetaField_descriptor[0];
            p->_refCount = p->_refCount - 1;
            if (((unsigned long long)(long long)p->_refCount & 0x7fffffULL) == 0) {
                igObject_Destroy(p);
            }
            g_igUnsignedShortArrayMetaField_descriptor[0]->_internalIndex = igMetaField_GetMetaFieldList()->_count - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)g_igUnsignedShortArrayMetaField_descriptor[0]);
        }
    }
}

