igMetaObject *igExternalIndexedEntry_GetMetaObject(void)
{
    igMetaObject *g = g_igExternalIndexedEntry_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igExternalIndexedEntry_EnsureRegistered();
    return g_igExternalIndexedEntry_metaObject[0];
}

int igExternalIndexedEntry_GetVTable(void) {
    igExternalIndexedEntry entry;
    int vtable;

    igObject_InitHeader((igObject *)&entry);
    entry._name = 0;
    entry._vtable = (int)(&g_igExternalIndexedEntry_vtable[0]);
    entry._entryType = 0;
    entry._objectType = 0;
    vtable = *(int *)((char *)&entry + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    entry._vtable = (int)(&g_igExternalIndexedEntry_vtable[0]);
    igSmartPointer_igMetaObject_Destruct(&entry._objectType, -1);
    igSmartPointer_igMetaObject_Destruct(&entry._entryType, -1);
    igDirEntry_Destroy(&entry, 0);
    return vtable;
}

void igExternalIndexedEntry_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igExternalIndexedEntry_Register);
}

void igExternalIndexedEntry_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igExternalIndexedEntry_metaObject,
        (igMetaObjectRegisterFunction)igDirEntry_Register,
        igDirEntry_GetPublishedMetaObject,
        igExternalIndexedEntry_GetMetaObjectFunction,
        igExternalIndexedEntry_className,
        0x34,
        igExternalIndexedEntry_GetVTable,
        igExternalIndexedEntry_InitFields,
        0,
        (igMetaObjectCallback *)g_igExternalIndexedEntry_callbackList
    );
}

void igExternalIndexedEntry_GetMetaObjectFunction(void) {
    igExternalIndexedEntry_GetMetaObject();
}

void igExternalIndexedEntry_InitFields(void) {
    int first;
    void *objectTypeField;
    void *entryTypeField;
    void *meta;

    meta = (void *)g_igExternalIndexedEntry_metaObject[0];
    first = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igExternalIndexedEntry_ctorTable[0], 6);
    entryTypeField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 2)));
    ((igObjectRefMetaField *)entryTypeField)->_metaObject = (int)igMetaObject_GetOrCreateMetaObject();
    ((igMetaField *)entryTypeField)->_persistent = 0;
    igIntMetaField_SetDefault((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 3))), -1);
    objectTypeField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 4)));
    ((igObjectRefMetaField *)objectTypeField)->_metaObject = (int)igMetaObject_GetOrCreateMetaObject();
    ((igMetaField *)objectTypeField)->_persistent = 0;
    igIntMetaField_SetDefault((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 5))), -1);
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igExternalIndexedEntry_fieldTable[0], (igMetaField ***)&g_igExternalIndexedEntry_fieldDescriptors[0], &g_igExternalIndexedEntry_fieldOffsets[0], first);
}

