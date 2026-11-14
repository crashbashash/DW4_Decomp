void *igExternalInfoEntry_Create(int pool) {
    igExternalInfoEntry_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x5863F8), (igMemoryPoolView *)pool));
}

igMetaObject *igExternalInfoEntry_GetMetaObject(void)
{
    igMetaObject *g = g_igExternalInfoEntry_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igExternalInfoEntry_EnsureRegistered();
    return g_igExternalInfoEntry_metaObject[0];
}

int igExternalInfoEntry_GetVTable(void) {
    igExternalInfoEntry entry;
    int vtable;
    int *p;
    int *q;

    igObject_InitHeader((igObject *)&entry);
    entry._name = 0;
    entry._vtable = (int)&g_igExternalInfoEntry_vtable[0];
    p = &entry._key;
    q = &entry._infoName;
    *p = 0;
    *q = 0;
    vtable = *(int *)((char *)&entry + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    entry._vtable = (int)&g_igExternalInfoEntry_vtable[0];
    igStringRef_Destruct(q, -1);
    igStringRef_Destruct(p, -1);
    igDirEntry_Destroy(&entry, 0);
    return vtable;
}

void igExternalInfoEntry_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igExternalInfoEntry_Register);
}

void igExternalInfoEntry_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igExternalInfoEntry_metaObject,
        (igMetaObjectRegisterFunction)igDirEntry_Register,
        igDirEntry_GetPublishedMetaObject,
        igExternalInfoEntry_GetMetaObjectFunction,
        igExternalInfoEntry_className,
        0x28,
        igExternalInfoEntry_GetVTable,
        igExternalInfoEntry_InitFields,
        0,
        0
    );
}

void igExternalInfoEntry_GetMetaObjectFunction(void) {
    igExternalInfoEntry_GetMetaObject();
}

void igExternalInfoEntry_InitFields(void) {
    int first;
    void *meta;

    meta = (void *)g_igExternalInfoEntry_metaObject[0];
    first = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igExternalInfoEntry_ctorTable[0], 3);
    igStringMetaField_SetDefaultText((int *)(igMetaObject_GetFieldAt((igMetaObject *)meta, first)), 0);
    igIntMetaField_SetDefault((void **)(igMetaObject_GetFieldAt((igMetaObject *)meta, first + 1)), -1);
    igStringMetaField_SetDefaultText((int *)(igMetaObject_GetFieldAt((igMetaObject *)meta, first + 2)), 0);
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igExternalInfoEntry_fieldTable[0], (igMetaField ***)&g_igExternalInfoEntry_fieldDescriptors[0], &g_igExternalInfoEntry_fieldOffsets[0], first);
}

