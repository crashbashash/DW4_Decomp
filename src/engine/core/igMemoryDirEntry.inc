int igMemoryDirEntry_Create(int allocator) {
    igMemoryDirEntry_EnsureRegistered();
    return igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585F60), (igMemoryPoolView *)allocator);
}

igMetaObject *igMemoryDirEntry_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryDirEntry_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igMemoryDirEntry_EnsureRegistered();
    return g_igMemoryDirEntry_metaObject[0];
}

int igMemoryDirEntry_GetVTable(void) {
    igMemoryDirEntry entry;
    int vtable;
    char *nameSlot;
    int *text, *header;
    int count;
    
    
    igObject_InitHeader((igObject *)&entry);
    entry._vtable = (int)(&g_igNamedObject_vtable[0]);
    nameSlot = (char *)&entry._name;
    *(int *)nameSlot = 0;
    entry._vtable = (int)(&g_igMemoryDirEntry_vtable[0]);
    vtable = *(int *)((char *)&entry + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    entry._vtable = (int)(&g_igNamedObject_vtable[0]);
    if (nameSlot != 0) {
        text = *(int **)nameSlot;
        if (text != 0) {
            header = text - 2;
            count = text[-1] - 1;
            text[-1] = count;
            if (count == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (int)header);
            }
        }
    }
    return vtable;
}

void igMemoryDirEntry_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMemoryDirEntry_Register);
}

void igMemoryDirEntry_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igMemoryDirEntry_metaObject,
        (igMetaObjectRegisterFunction)igDirEntry_Register,
        igDirEntry_GetPublishedMetaObject,
        igMemoryDirEntry_GetMetaObjectFunction,
        igMemoryDirEntry_className,
        0x38,
        igMemoryDirEntry_GetVTable,
        igMemoryDirEntry_InitFields,
        0,
        (igMetaObjectCallback *)g_igMemoryDirEntry_callbackList
    );
}

void igMemoryDirEntry_GetMetaObjectFunction(void) {
    igMemoryDirEntry_GetMetaObject();
}

void igMemoryDirEntry_InitFields(void) {
    int base;
    void *memTypeSizeField;
    void *memTypeField;
    void *meta;

    meta = (void *)g_igMemoryDirEntry_metaObject[0];
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igMemoryDirEntry_ctorTable[0], 7);
    memTypeSizeField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    igIntMetaField_SetDefault((void **)memTypeSizeField, -1);
    ((igMetaField *)memTypeSizeField)->_persistent = 0;
    memTypeField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2)));
    ((igObjectRefMetaField *)memTypeField)->_metaObject = (int)igMetaField_GetOrCreateMetaObject();
    igObjectRefMetaField_SetDefault((igObjectRefMetaField *)memTypeField, (igObject *)(igCharMetaField_GetDefaultDescriptor()));
    ((igObjectRefMetaField *)memTypeField)->_refCounted = 0;
    ((igObjectRefMetaField *)memTypeField)->_persistent = 0;
    igIntMetaField_SetDefault((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3))), -1);
    igBoolMetaField_SetDefaultValue((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 4))), 1);
    igIntMetaField_SetDefault((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 5))), -1);
    igIntMetaField_SetDefault((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 6))), -1);
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igMemoryDirEntry_fieldTable[0], (igMetaField ***)&g_igMemoryDirEntry_fieldDescriptors[0], &g_igMemoryDirEntry_fieldOffsets[0], base);
}

